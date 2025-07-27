#include <fftw3.h>
#include <stdio.h>

#define ELEMENTS_SIZE 256

int read_input(const char *filename, fftw_complex *in) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    return -1;
  }

  for (int i = 0; i < ELEMENTS_SIZE; i++) {
    if (fscanf(f, "%lf %lf", &in[i][0], &in[i][1]) != 2) {
      fclose(f);
      return -2;
    }
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

  int result = read_input("input_3.txt", in);
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

  fprintf(stdout, "Вывод элементов:\n");
  for (int i = 0; i < ELEMENTS_SIZE; i++) {
    printf("%d) %.10f %.10f\n", i + 1, out[i][0], out[i][1]);
  }

  fftw_destroy_plan(plan);
  fftw_free(in);
  fftw_free(out);

  return 0;
}
