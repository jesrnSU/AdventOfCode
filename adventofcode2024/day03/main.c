#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* 
  Part 1.
  Reads character by character and matches pattern[]. If index is at '(' or ',' it expects to read an integer. 
  Any diverations from the pattern results in the index reseting to 0 and expecting 'm'.
  If the index reaches 5 ')', it means that the mul sequence was read successfully and the product is calculated. 

  Part 2.
  Reads character by character and matches pattern, enablePattern or disablePattern. Works as part1 but toggles saving the product if enable or disable pattern
  is matched.
*/

static const char path[] = "data.txt";
static const char testPath[] = "dataTest.txt";
static const char testPath2[] = "dataTest2.txt";
static const char pattern[] = "mul(,)";

static const char enablePattern[] = "do()";
static const char disablePattern[] = "don't()";
static bool isEnabled = true;

static int solvePart1(){
  FILE *fp = fopen(path, "r");
  char ch;
  int index = 0;
  int factorX = 0, factorY = 0;
  int total = 0;

  if(fp == NULL){
    perror(path);
  }

  while((ch = fgetc(fp)) != EOF){

    while(isdigit(ch)){
      int digit = ch - '0';
      if(index == 3){
        factorX = factorX * 10 + digit;
      }else if(index == 4){
        factorY = factorY * 10 + digit;
      }else{
        index = 0;
        break;
      }
      ch = fgetc(fp);
    }

    index++;

    if(ch != pattern[index]){
      index = 0;
      factorX = 0;
      factorY = 0;
    }else if(index == 5){
      total += (factorX * factorY);
      index = 0;
      factorX = 0;
      factorY = 0;
    }
  }
  return total;
}

static int solvePart2(){
  FILE *fp = fopen(path, "r");
  char ch;
  int index = 0;
  int enableIndex = 0;
  int disableIndex = 0;
  int factorX = 0, factorY = 0;
  int total = 0;

  if(fp == NULL){
    perror(path);
  }

  while((ch = fgetc(fp)) != EOF){

    while(isdigit(ch)){
      int digit = ch - '0';
      if(index == 3){
        factorX = factorX * 10 + digit;
      }else if(index == 4){
        factorY = factorY * 10 + digit;
      }else{
        index = 0;
        break;
      }
      ch = fgetc(fp);
    }

    if(ch == enablePattern[enableIndex]){
      enableIndex++;
      if(enableIndex == 4){
        isEnabled = true; 
        enableIndex = 0;
        disableIndex = 0;
      }
    }
    
    if(ch == disablePattern[disableIndex]){
      disableIndex++;
      if(disableIndex == 7){
        isEnabled = false;
        disableIndex = 0;
        enableIndex = 0;
      }else if(disableIndex == 3){
        enableIndex = 0;
      }
    }

    index++;

    if(ch != pattern[index]){
      index = 0;
      factorX = 0;
      factorY = 0;
    }else if(index == 5){
      if(isEnabled){
        total += (factorX * factorY);
      }
      index = 0;
      factorX = 0;
      factorY = 0;
    }
  }
  return total;
}
int main(void){
  int result = solvePart2();
  printf("%d\n", result);
}
