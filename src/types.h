#ifndef TYPES_H
#define TYPES_H

#define _GNU_SOURCE
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  size_t v_count;
  double *vertices;
  size_t f_count;
  int *faces;
} dot_obj_data;

enum Result { OK, ERROR };

#endif  // TYPES_H
