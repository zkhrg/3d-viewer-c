#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include "types.h"

enum MOVEMENT { MOVE_X, MOVE_Y, MOVE_Z };
void move_vertices(dot_obj_data* dod, int delta, int move);
void scale_vertices(dot_obj_data* dod, int scale);

#endif  // TRANSFORMATIONS_H
