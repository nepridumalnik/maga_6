#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ELEMENTS_SIZE 2048

int read_input(const char *filename, fftw_complex *in) {
  FILE *f = fopen(filename, "r");
  if (!f)
    return -1;

  char *line = NULL;
  size_t len = 0;
  if (getline(&line, &len, f) == -1) {
    fclose(f);
    return -2;
  }

  char *token = strtok(line, ",");
  for (int i = 0; i < ELEMENTS_SIZE; i++) {
    if (!token || sscanf(token, "%lf %lf", &in[i][0], &in[i][1]) != 2) {
      free(line);
      fclose(f);
      return -3;
    }
    token = strtok(NULL, ",");
  }

  free(line);
  fclose(f);
  return 0;
}

int write_output(const char *filename, fftw_complex *out) {
  FILE *f = fopen(filename, "w");
  if (!f)
    return -1;

  for (int i = 0; i < ELEMENTS_SIZE; i++) {
    fprintf(f, "%.10f %.10f\n", out[i][0], out[i][1]);
  }

  fclose(f);
  return 0;
}

int main() {
  fftw_complex *in = fftw_malloc(sizeof(fftw_complex) * ELEMENTS_SIZE);
  fftw_complex *out = fftw_malloc(sizeof(fftw_complex) * ELEMENTS_SIZE);

  if (!in || !out) {
    fprintf(stderr, "Ошибка выделения памяти\n");
    return -1;
  }

  fprintf(stdout, "Память выделена\n");

  int result = read_input("input_2.txt", in);
  if (result != 0) {
    fftw_free(in);
    fftw_free(out);
    fprintf(stderr, "Ошибка чтения из файла: %d\n", result);
    return -1;
  }

  fprintf(stdout, "Данные прочитаны\n");

  fftw_plan plan =
      fftw_plan_dft_1d(ELEMENTS_SIZE, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan);

  result = write_output("output_2.txt", out);
  if (result != 0) {
    fprintf(stderr, "Ошибка записи в файл: %d\n", result);
  }

  fprintf(stdout, "Задача успешно выполнена, очистка данные\n");
  fftw_destroy_plan(plan);
  fftw_free(in);
  fftw_free(out);

  return 0;
}
