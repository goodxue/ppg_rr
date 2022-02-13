/*
 * interp1_f2.cpp
 *
 * Code generation for function 'interp1_f2'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "interp1_f2.h"
#include "interp1.h"

/* Function Definitions */
void interp1_f2(const double t[500], const double ppg[500], const double tc[500],
                double ppg1[500])
{
  double y[500];
  double x[500];
  int k;
  int exitg1;
  double xtmp;
  memcpy(&y[0], &ppg[0], 500U * sizeof(double));
  memcpy(&x[0], &t[0], 500U * sizeof(double));
  k = 0;
  do {
    exitg1 = 0;
    if (k < 500) {
      if (rtIsNaN(t[k])) {
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      if (t[1] < t[0]) {
        for (k = 0; k < 250; k++) {
          xtmp = x[k];
          x[k] = x[499 - k];
          x[499 - k] = xtmp;
          xtmp = y[k];
          y[k] = y[499 - k];
          y[499 - k] = xtmp;
        }
      }

      memset(&ppg1[0], 0, 500U * sizeof(double));
      interp1SplineOrPCHIP(y, tc, ppg1, x);
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/* End of code generation (interp1_f2.cpp) */
