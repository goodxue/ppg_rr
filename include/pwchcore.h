/*
 * pwchcore.h
 *
 * Code generation for function 'pwchcore'
 *
 */

#ifndef PWCHCORE_H
#define PWCHCORE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
//#include "interp1_f_types.h"

/* Function Declarations */
extern void pwchcore(const double x[500], const double y[500], const double s
                     [500], const double dx[499], const double divdif[499],
                     double pp_breaks[500], double pp_coefs[1996]);

#endif

/* End of code generation (pwchcore.h) */
