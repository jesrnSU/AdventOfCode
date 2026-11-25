#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* 
  Part 1.
  Reads character by character and matches pattern[]. If index is at '(' or ',' it expects to read an integer. 
  Any diverations from the pattern results in the index reseting to 0 and expecting 'm'.
  If the index reaches 5 ')', it means that the mul sequence was read successfully and the product is calculated. 

  Part 2.
*/

static const char path[] = "data.txt";
static const char pattern[] = "mul(,)";

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


int main(void){
  int result = solvePart1();
  printf("%d\n", result);
}
