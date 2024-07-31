#include "transformations.h"

void move_vertices(dot_obj_data* dod, int delta, int move) {
  for (size_t i = 0; i < dod->v_count * 3; i += 3) {
    dod->vertices[i + move] += (double)delta / (double)40;
  }
}

void scale_vertices(dot_obj_data* dod, int scale) {
  for (size_t i = 0; i < dod->v_count * 3; i++) {
    dod->vertices[i] *=
        ((double)1 + (double)1 / ((double)100 / ((double)scale)));
  }
}

void rotate_x(dot_obj_data* dod, double c) {
  c = c * M_PI / 180;
  for (size_t i = 0; i < dod->v_count * 3; i += 3) {
    double y = dod->vertices[i + 1];
    double z = dod->vertices[i + 2];
    dod->vertices[i + 1] = y * cos(c) + z * sin(c);
    dod->vertices[i + 2] = -y * sin(c) + z * cos(c);
  }
}

void rotate_y(dot_obj_data* dod, double c) {
  c = c * M_PI / 180;
  for (size_t i = 0; i < dod->v_count * 3; i += 3) {
    double x = dod->vertices[i];
    double z = dod->vertices[i + 2];
    dod->vertices[i] = x * cos(c) + z * sin(c);
    dod->vertices[i + 2] = -x * sin(c) + z * cos(c);
  }
}

void rotate_z(dot_obj_data* dod, double c) {
  c = c * M_PI / 180;
  for (size_t i = 0; i < dod->v_count * 3; i += 3) {
    double x = dod->vertices[i];
    double y = dod->vertices[i + 1];
    dod->vertices[i] = x * cos(c) + y * sin(c);
    dod->vertices[i + 1] = -x * sin(c) + y * cos(c);
  }
}
