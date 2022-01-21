/*
 * ppval.h
 *
 * Code generation for function 'ppval'
 *
 */

#ifndef PPVAL_H
#define PPVAL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "interp1_f_types.h"

/* Function Declarations */
extern double ppval(const double pp_breaks[500], const double pp_coefs[1996],
                    double x);

#endif

/* End of code generation (ppval.h) */
