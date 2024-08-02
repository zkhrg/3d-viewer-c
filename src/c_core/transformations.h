#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include "../common/types.h"

enum MOVEMENT { MOVE_X, MOVE_Y, MOVE_Z };
void move_vertices(dot_obj_data* dod, int delta, int move);
void scale_vertices(dot_obj_data* dod, int scale);
void rotate_x(dot_obj_data* dod, double c);
void rotate_y(dot_obj_data* dod, double c);
void rotate_z(dot_obj_data* dod, double c);

#endif  // TRANSFORMATIONS_H
