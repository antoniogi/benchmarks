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
// ParallelOptimizer.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PARALLELOPTIMIZER_H
#define PARALLELOPTIMIZER_H

#include "Sample.h"
#include "Timer.h"
#include <map>
using namespace std;

typedef map<string,Timer> TimerMap;

class ParallelOptimizer {
  private:

  Sample& s_;
  int niter_, nitscf_, nite_;
  vector<vector<double> > fion;
  valarray<double> sigma_eks, sigma_kin, sigma_ext, sigma;
  
  // Do not allow construction of ParallelOptimizer unrelated to a Sample
  ParallelOptimizer(void);

  public:

  mutable TimerMap tmap;
  
  void optimize(int niter, int nitscf, int nite);
  //double runtime(bool print_timing);
  double runtime(int nrowmax, int npark, int nspin, bool reshape, bool print_timing);
  list<int> factorize(int n);
  list<int> factorize(int n1, int n2);
  ParallelOptimizer(Sample& s);
  ~ParallelOptimizer();
};
#endif
