#include <stdio.h>
#include <stdlib.h>

static int readPuzzleDataSize(const char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    perror(path);
    return -1;
  }

  int count = 1;
  int c;
  while ((c = getc(fp)) != EOF) {
    if (c == '\n') {
      count++;
    }
  }

  if (ferror(fp)) {
    perror(path);
    fclose(fp);
    return -1;
  }

  fclose(fp);
  return count;
}

static void readPuzzleDataValues(const char *path, int *left, int *right, int size){
  FILE *fp = fopen(path, "r");
  int leftVal;
  int rightVal;

  for(int i = 0; i < size; i++){
    fscanf(fp, "%d %d", &leftVal, &rightVal);
    left[i] = leftVal;
    right[i] = rightVal;
  }
  fclose(fp);
}

static int compareInts(const void *a, const void *b){
  int left = *(const int *)a;
  int right = *(const int *)b;
  return (left > right) - (left < right);
}

static int solvePuzzle(int *left, int *right, int size){
  int dist = 0;
  int result = 0;
  qsort(left, size, sizeof *left, compareInts);
  qsort(right, size, sizeof *right, compareInts);

  for(int i = 0; i < size; i++){
    dist = left[i] - right[i];
    result += abs(dist);
  }

  return result;
}



int main(void)
{
  int count = readPuzzleDataSize("data.txt");
  if (count < 0) {
    return EXIT_FAILURE;
  }

  int left[count];
  int right[count];
  int result;

  readPuzzleDataValues("data.txt", left, right, count);
  result = solvePuzzle(left, right, count);

  printf("%d\n", result);
  return EXIT_SUCCESS;
}
