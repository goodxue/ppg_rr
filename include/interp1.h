/*
 * interp1.h
 *
 * Code generation for function 'interp1'
 *
 */

#ifndef INTERP1_H
#define INTERP1_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
//#include "interp1_f2_types.h"

/* Function Declarations */
extern void interp1SplineOrPCHIP(const double y[500], const double xi[500],
  double yi[500], const double x[500]);

#endif

/* End of code generation (interp1.h) */
