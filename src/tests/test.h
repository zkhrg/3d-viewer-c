#ifndef _S21_3D_VIEWER_C_
#define _S21_3D_VIEWER_C_

#include <check.h>
#include <math.h>
#define EPSILON 1e-6
#include "../c_core/dot_obj_parser.h"
#include "../c_core/transformations.h"

Suite *transformations_suite(void);
Suite *dot_obj_parser_suite(void);

#endif
