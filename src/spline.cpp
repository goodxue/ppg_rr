/*
 * spline.cpp
 *
 * Code generation for function 'spline'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
//#include "interp1_f.h"
#include "spline.h"
#include "pwchcore.h"

/* Function Definitions */
void spline(const double x[500], const double y[500], double output_breaks[500],
            double output_coefs[1996])
{
  int k;
  double d31;
  double r;
  double dnnm2;
  double dx[499];
  double s[500];
  double dvdf[499];
  double md[500];
  for (k = 0; k < 499; k++) {
    r = x[k + 1] - x[k];
    dx[k] = r;
    dvdf[k] = (y[k + 1] - y[k]) / r;
  }

  d31 = x[2] - x[0];
  dnnm2 = x[499] - x[497];
  s[0] = ((dx[0] + 2.0 * d31) * dx[1] * dvdf[0] + dx[0] * dx[0] * dvdf[1]) / d31;
  s[499] = ((dx[498] + 2.0 * dnnm2) * dx[497] * dvdf[498] + dx[498] * dx[498] *
            dvdf[497]) / dnnm2;
  md[0] = dx[1];
  md[499] = dx[497];
  for (k = 0; k < 498; k++) {
    r = dx[k + 1];
    s[k + 1] = 3.0 * (r * dvdf[k] + dx[k] * dvdf[k + 1]);
    md[k + 1] = 2.0 * (r + dx[k]);
  }

  r = dx[1] / md[0];
  md[1] -= r * d31;
  s[1] -= r * s[0];
  for (k = 0; k < 497; k++) {
    r = dx[k + 2] / md[k + 1];
    md[k + 2] -= r * dx[k];
    s[k + 2] -= r * s[k + 1];
  }

  r = dnnm2 / md[498];
  md[499] -= r * dx[497];
  s[499] -= r * s[498];
  s[499] /= md[499];
  for (k = 497; k >= 0; k--) {
    s[k + 1] = (s[k + 1] - dx[k] * s[k + 2]) / md[k + 1];
  }

  s[0] = (s[0] - d31 * s[1]) / md[0];
  pwchcore(x, y, s, dx, dvdf, output_breaks, output_coefs);
}

/* End of code generation (spline.cpp) */
