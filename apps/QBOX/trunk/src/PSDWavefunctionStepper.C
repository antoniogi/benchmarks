////////////////////////////////////////////////////////////////////////////////  
// Copyright (c) 2013, Lawrence Livermore National Security, LLC. 
// qb@ll:  Qbox at Lawrence Livermore
//
// This file is part of qb@ll.
//
// Produced at the Lawrence Livermore National Laboratory. 
// Written by Erik Draeger (draeger1@llnl.gov) and Francois Gygi (fgygi@ucdavis.edu).
// Based on the Qbox code by Francois Gygi Copyright (c) 2008 
// LLNL-CODE-635376. All rights reserved. 
//
// qb@ll is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details, in the file COPYING in the
// root directory of this distribution or <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////
//
// PSDWavefunctionStepper.C
//
////////////////////////////////////////////////////////////////////////////////

#include "PSDWavefunctionStepper.h"
#include "Wavefunction.h"
#include "SlaterDet.h"
#include "Preconditioner.h"
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
PSDWavefunctionStepper::PSDWavefunctionStepper(Wavefunction& wf, 
  Preconditioner& p, TimerMap& tmap) : 
  WavefunctionStepper(wf,tmap), prec_(p)
{}

////////////////////////////////////////////////////////////////////////////////
void PSDWavefunctionStepper::update(Wavefunction& dwf) {
  for ( int ispin = 0; ispin < wf_.nspin(); ispin++ ) {
    if (wf_.spinactive(ispin)) {
      for ( int ikp=0; ikp<wf_.nkp(); ikp++) {
        if (wf_.kptactive(ikp)) {
          assert(wf_.sd(ispin,ikp) != 0);
          // compute A = V^T H V  and descent direction HV - VA
 
          tmap_["psd_residual"].start();
          if ( wf_.sd(ispin,ikp)->basis().real() ) {
            // proxy real matrices c, cp
            DoubleMatrix c(wf_.sd(ispin,ikp)->c());
            DoubleMatrix cp(dwf.sd(ispin,ikp)->c());
          
            DoubleMatrix a(c.context(),c.n(),c.n(),c.nb(),c.nb());
 
            // factor 2.0 in next line: G and -G
            a.gemm('t','n',2.0,c,cp,0.0);
            // rank-1 update correction
            a.ger(-1.0,c,0,cp,0);
            // cp = cp - c * a
            if (wf_.ultrasoft()) {
              // cp = cp - spsi * a
              DoubleMatrix spsi(wf_.sd(ispin,ikp)->spsi());
              cp.gemm('n','n',-1.0,spsi,a,1.0);
            }
            else {
              // cp = cp - c * a
              cp.gemm('n','n',-1.0,c,a,1.0);
            }
          }
          else {
            ComplexMatrix &c = wf_.sd(ispin,ikp)->c();
            ComplexMatrix &cp = dwf.sd(ispin,ikp)->c();
            ComplexMatrix a(c.context(),c.n(),c.n(),c.nb(),c.nb());

            a.gemm('c','n',1.0,c,cp,0.0);

            if (wf_.ultrasoft()) {
              // cp = cp - spsi * a
              ComplexMatrix &spsi = wf_.sd(ispin,ikp)->spsi();
              cp.gemm('n','n',-1.0,spsi,a,1.0);
            }
            else {
              // cp = cp - c * a
              cp.gemm('n','n',-1.0,c,a,1.0);
            }
          }
          tmap_["psd_residual"].stop();
        
          // dwf.sd->c() now contains the descent direction (HV-VA)
        
          tmap_["psd_update_wf"].start();
          const valarray<double>& diag = prec_.diag(ispin,ikp);

          double* coeff = (double*) wf_.sd(ispin,ikp)->c().valptr();
          const double* dcoeff =
              (const double*) dwf.sd(ispin,ikp)->c().cvalptr();
          const int mloc = wf_.sd(ispin,ikp)->c().mloc();
          const int ngwl = wf_.sd(ispin,ikp)->basis().localsize();
          const int nloc = wf_.sd(ispin,ikp)->c().nloc();

          for ( int n = 0; n < nloc; n++ ) {
            // note: double mloc length for complex<double> indices
            double* c = &coeff[2*mloc*n];
            const double* dc = &dcoeff[2*mloc*n];

            // loop to ngwl only since diag[i] is not defined on [0:mloc-1]
            for ( int i = 0; i < ngwl; i++ ) {
              const double fac = diag[i];
              const double delta_re = fac * dc[2*i];
              const double delta_im = fac * dc[2*i+1];
              c[2*i]   -= delta_re;
              c[2*i+1] -= delta_im;
            }
          }
          tmap_["psd_update_wf"].stop();
        }
      }
    }
  }
}
