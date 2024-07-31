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
