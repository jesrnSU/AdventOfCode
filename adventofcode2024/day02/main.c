#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int solvePuzzlePart1(const char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    perror(path);
    return -1;
  }

  int safeCount = 0;
  // 0 = unset mode, 1 = increasing, 2 = decreasing
  int mode = 0;
  int val;
  int prevVal;
  char term;
  bool isNewRow = true;
  bool isInvalid = false;

  while (fscanf(fp, "%d%c", &val, &term) == 2) {
    //printf("%d\n", val);
    if(isNewRow){
      prevVal = val;
      isInvalid = false;
      mode = 0;
      isNewRow = false;
      continue;
    }else if(!isInvalid){
      //printf("%d", abs(prevVal - val));
      //printf("\n");
      if(abs(prevVal - val) > 3 || abs(prevVal-val) < 1){
        //printf("Too big dif\n");
        isInvalid = true;
      }
      else if((prevVal - val) < 0 && ((mode == 0) || (mode == 1))){
        //printf("setting m1\n");
        prevVal = val;
        mode = 1;
      }else if((prevVal - val) > 0 && ((mode == 0) || (mode == 2))){
        //printf("setting m2\n");
        prevVal = val;
        mode = 2;
      }else{
        isInvalid = true;
      }
    }

    if(term == '\n'){
      //printf("reached newline\n");
      isNewRow = true;
      if(!isInvalid){
        //printf("adding count\n");
        safeCount++;
      }
    }

  }    

  if (ferror(fp)) {
    perror(path);
    fclose(fp);
    return -1;
  }

  fclose(fp);
  return safeCount;
}

static int solvePuzzlePart2(const char *path){
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    perror(path);
    return -1;
  }

  int safeCount = 0;
  // 0 = unset mode, 1 = increasing, 2 = decreasing
  int mode = 0;
  int val;
  int prevVal;
  char term;
  bool isNewRow = true;
  bool isInvalid = false;

  while (fscanf(fp, "%d%c", &val, &term) == 2) {
    //printf("%d\n", val);
    if(isNewRow){
      prevVal = val;
      isInvalid = false;
      mode = 0;
      isNewRow = false;
      continue;
    }else if(!isInvalid){
      //printf("%d", abs(prevVal - val));
      //printf("\n");
      if(abs(prevVal - val) > 3 || abs(prevVal-val) < 1){
        //printf("Too big dif\n");
        isInvalid = true;
      }
      else if((prevVal - val) < 0 && ((mode == 0) || (mode == 1))){
        //printf("setting m1\n");
        prevVal = val;
        mode = 1;
      }else if((prevVal - val) > 0 && ((mode == 0) || (mode == 2))){
        //printf("setting m2\n");
        prevVal = val;
        mode = 2;
      }else{
        isInvalid = true;
      }
    }

    if(term == '\n'){
      //printf("reached newline\n");
      isNewRow = true;
      if(!isInvalid){
        //printf("adding count\n");
        safeCount++;
      }
    }

  }    

  if (ferror(fp)) {
    perror(path);
    fclose(fp);
    return -1;
  }

  fclose(fp);
  return safeCount; 
}

int main(void){
  int result = solvePuzzlePart1("data.txt");
  printf("Resutlt : %d", result);
}