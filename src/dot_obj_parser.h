#ifndef DOT_OBJ_PARSER_H
#define DOT_OBJ_PARSER_H
#include "types.h"

int parse_dot_obj_file(const char* filename, dot_obj_data* dod);
void count_v_and_f(FILE* f, dot_obj_data* dod);
int parse_v_and_f(FILE* f, dot_obj_data* dod);
int dodalloc(dot_obj_data* dod);
void print_dod(dot_obj_data* dod);
void free_dod(dot_obj_data* dod);

#endif  // DOT_OBJ_PARSER_H
