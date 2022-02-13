/*
 * interp1.cpp
 *
 * Code generation for function 'interp1'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
//#include "interp1_f.h"
#include "interp1.h"
#include "ppval.h"
#include "spline.h"

/* Type Definitions */
typedef struct {
  double breaks[500];
  double coefs[1996];
} struct_T;

/* Function Definitions */
void interp1SplineOrPCHIP(const double y[500], const double xi[49901], double
  yi[49901], const double x[500])
{
  struct_T pp;
  int k;
  spline(x, y, pp.breaks, pp.coefs);

#pragma omp parallel for \
 num_threads(omp_get_max_threads())

  for (k = 0; k < 49901; k++) {
    if (rtIsNaN(xi[k])) {
      yi[k] = rtNaN;
    } else {
      yi[k] = ppval(pp.breaks, pp.coefs, xi[k]);
    }
  }
}

/* End of code generation (interp1.cpp) */
