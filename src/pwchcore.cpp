/*
 * pwchcore.cpp
 *
 * Code generation for function 'pwchcore'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "interp1_f2.h"
#include "pwchcore.h"

/* Function Definitions */
void pwchcore(const double x[500], const double y[500], const double s[500],
              const double dx[499], const double divdif[499], double pp_breaks
              [500], double pp_coefs[1996])
{
  int j;
  double dzzdx;
  double dzdxdx;
  memcpy(&pp_breaks[0], &x[0], 500U * sizeof(double));
  for (j = 0; j < 499; j++) {
    dzzdx = (divdif[j] - s[j]) / dx[j];
    dzdxdx = (s[j + 1] - divdif[j]) / dx[j];
    pp_coefs[j] = (dzdxdx - dzzdx) / dx[j];
    pp_coefs[j + 499] = 2.0 * dzzdx - dzdxdx;
    pp_coefs[j + 998] = s[j];
    pp_coefs[j + 1497] = y[j];
  }
}

/* End of code generation (pwchcore.cpp) */
