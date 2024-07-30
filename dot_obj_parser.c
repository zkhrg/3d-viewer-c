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
  int parse_status = OK;
  char* line = NULL;
  size_t len = 0;
  size_t i = 0;
  size_t v_counter = 0;
  size_t f_counter = 0;

  while (getline(&line, &len, f) != -1) {
    if (strncmp(line, "v ", 2) == 0) {
      double x, y, z;
      sscanf(line, "v %lf %lf %lf", &x, &y, &z);
      dod->vertices[i++] = x;
      dod->vertices[i++] = y;
      dod->vertices[i++] = z;
      v_counter++;
    } else if (strncmp(line, "f ", 2) == 0) {
      char* token = strtok(line + 2, " ");
      int vertex_index;
      int first_index = -1;

      while (token != NULL) {
        if (sscanf(token, "%d/%*d/%*d", &vertex_index) == 1) {
          if (vertex_index < 0) {
            vertex_index += v_counter + 1;
          }
          if (first_index == -1) {
            first_index = vertex_index - 1;
          }
          dod->faces[f_counter++] = vertex_index - 1;
        }

        token = strtok(NULL, " ");
      }

      if (first_index != -1 && f_counter > 0 && f_counter % 2 == 0) {
        dod->faces[f_counter++] = first_index;
      }
    }
  }

  if (line) {
    free(line);
  }

  return parse_status;
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
