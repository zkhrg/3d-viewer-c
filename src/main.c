#include "dot_obj_parser.h"

int main(void) {
  dot_obj_data dod;
  parse_dot_obj_file("/Users/diamondp/Desktop/plant.obj", &dod);
  print_dod(&dod);

  return 0;
}
