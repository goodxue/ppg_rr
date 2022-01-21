/*
 * spline.h
 *
 * Code generation for function 'spline'
 *
 */

#ifndef SPLINE_H
#define SPLINE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
//#include "rtwtypes.h"
#include "omp.h"
//#include "interp1_f_types.h"

/* Function Declarations */
extern void spline(const double x[500], const double y[500], double
                   output_breaks[500], double output_coefs[1996]);

#endif

/* End of code generation (spline.h) */
