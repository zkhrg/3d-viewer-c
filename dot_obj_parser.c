#include "dot_obj_parser.h"

int parse_dot_obj_file(char* filename, dot_obj_data* dod) {
  if (!filename || !dod) {
    return ERROR;
  }
  int status = OK;
  FILE* f = fopen(filename, "r");
  if (f) {
    count_v_and_f(f, dod);
    status = dodalloc(dod);
    if (status != ERROR) {
      fseek(f, 0, SEEK_SET);
      status = parse_v_and_f(f, dod);
    }
    fclose(f);
  } else {
    status = ERROR;
  }

  return status;
}

int parse_v_and_f(FILE* f, dot_obj_data* dod) {
  ;
  ;
}

int dodalloc(dot_obj_data* dod) {
  int status = OK;
  dod->vertices = (double*)malloc(dod->v_count * 3 * sizeof(double));
  dod->faces = (int*)malloc(dod->f_count * 3 * sizeof(int));

  if (!dod->vertices || !dod->faces) {
    status = ERROR;
  }
  if (status == ERROR) {
    if (dod->vertices) free(dod->vertices);
    if (dod->faces) free(dod->faces);
  }
  return status;
}

void count_v_and_f(FILE* f, dot_obj_data* dod) {
  size_t vertex_count = 0;
  size_t face_count = 0;

  char* line = NULL;
  size_t len = 0;

  while (getline(&line, &len, f) != -1) {
    line[strcspn(line, "\n")] = '\0';

    if (line[0] == '#' || line[0] == '\0') {
      continue;
    }

    if (line[0] == 'v') {
      if (line[1] == ' ') {
        vertex_count++;
      }
    } else if (line[0] == 'f' && line[1] == ' ') {
      face_count++;
    }
  }
  free(line);

  dod->v_count = vertex_count;
  dod->f_count = face_count;
}
