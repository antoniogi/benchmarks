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
#ifndef SPHERICALINTEGRATION_H
#define SPHERICALINTEGRATION_H
#include <vector>
using namespace std;

class SphericalIntegration {

  private:

  public:

  SphericalIntegration(void);
  ~SphericalIntegration(void);

  double clebsch_gordan(int j1, int m1, int j2, int m2, int j3, int m3);
  double clebsch_gordan_real(int j1, int m1, int j2, int m2, int j3, int m3);
  int ifactorial(int v);
  double dfactorial(int v);
  double ylm_real(int l, int m, double gx, double gy, double gz);
  void init_ll74grid(vector<double> &llsph_r, vector<double> &llsph_wt);
  void llsph_gen_oh(int code, double a, double b, double v, vector<double>& r, vector<double>& wt);

};
#endif
