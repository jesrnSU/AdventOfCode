#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Pos{
  long x, y;
};

static const char path[] = "data.txt";
static const char pathTest[] = "dataTest.txt";

// Since grid is symmetrical so we only read one row to get the nr of cols. 
// Then we calculate the amount of rows by nr of cols + file size.
static void initGridSize(const char *path, long *rows, long *cols){
  FILE *fp = fopen(path, "rb");
  if (fp == NULL) {
      perror(path);
      return;
  }

  int c;
  while ((c = fgetc(fp)) != '\n' && c != EOF) {}

  long rowBytes = ftell(fp);
  if (ferror(fp) || rowBytes <= 0 || fseek(fp, 0, SEEK_END) != 0) {
      fclose(fp);
      return;
  }

  long fileBytes = ftell(fp);
  if (fileBytes < 0 || fseek(fp, 0, SEEK_SET) != 0) {
      fclose(fp);
      return;
  }

  *cols = rowBytes - (c == '\n' ? 1 : 0);
  *rows = fileBytes / rowBytes + (fileBytes % rowBytes != 0);
  fclose(fp);
}

static void insertGridData(const char *path, long rows, long cols, char grid[rows][cols]){
  FILE *fp = fopen(path, "r");

  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      grid[i][j] = fgetc(fp);
    }
    fgetc(fp);
  }
}

static void printGrid(long rows, long cols, char grid[rows][cols]){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
}

static bool checkWord(long cols, char grid[][cols], struct Pos xPos, struct Pos mPos, struct Pos aPos, struct Pos sPos){
  return  grid[xPos.y][xPos.x] == 'X' &&
          grid[mPos.y][mPos.x] == 'M' &&
          grid[aPos.y][aPos.x] == 'A' &&
          grid[sPos.y][sPos.x] == 'S';
}

static int wordSearch(long rows, long cols, char grid[rows][cols], struct Pos xPos){
  long x = xPos.x;
  long y = xPos.y;
  int foundWords = 0;

  // Up
  if(y >= 3){
    foundWords += checkWord(cols, grid, xPos, (struct Pos){x, y - 1}, (struct Pos){x, y - 2}, (struct Pos){x, y - 3});
  }
  // Up-right
  if(x + 3 < cols && y >= 3){
    foundWords += checkWord(cols, grid, xPos, (struct Pos){x + 1, y - 1}, (struct Pos){x + 2, y - 2}, (struct Pos){x + 3, y - 3});
  }
  // Right
  if(x + 3 < cols){
    foundWords += checkWord(cols, grid, xPos, (struct Pos){x + 1, y}, (struct Pos){x + 2, y}, (struct Pos){x + 3, y});
  }
  // Down-right
  if(x + 3 < cols && y + 3 < rows){
    foundWords += checkWord(cols, grid, xPos, (struct Pos){x + 1, y + 1}, (struct Pos){x + 2, y + 2}, (struct Pos){x + 3, y + 3});
  }
  // Down
  if(y + 3 < rows){
    foundWords += checkWord(cols, grid, xPos, (struct Pos){x, y + 1}, (struct Pos){x, y + 2}, (struct Pos){x, y + 3});
  }
  // Down-left
  if(x >= 3 && y + 3 < rows){
    foundWords += checkWord(cols, grid, xPos, (struct Pos){x - 1, y + 1}, (struct Pos){x - 2, y + 2}, (struct Pos){x - 3, y + 3});
  }
  // Left
  if(x >= 3){
    foundWords += checkWord(cols, grid, xPos, (struct Pos){x - 1, y}, (struct Pos){x - 2, y}, (struct Pos){x - 3, y});
  }
  // Up-left
  if(x >= 3 && y >= 3){
    foundWords += checkWord(cols, grid, xPos, (struct Pos){x - 1, y - 1}, (struct Pos){x - 2, y - 2}, (struct Pos){x - 3, y - 3});
  }
  return foundWords;
}

static bool wordSearchPart2(long rows, long cols, char grid[rows][cols], struct Pos aPos){
  long x = aPos.x;
  long y = aPos.y;
  if(x == 0 || x == cols - 1 || y == 0 || y == rows - 1){
    return false;
  }

  char topLeft = grid[y - 1][x - 1];
  char topRight = grid[y - 1][x + 1];
  char bottomLeft = grid[y + 1][x - 1];
  char bottomRight = grid[y + 1][x + 1];

  bool firstDiagonal = (topLeft == 'M' && bottomRight == 'S') ||
                       (topLeft == 'S' && bottomRight == 'M');
  bool secondDiagonal = (topRight == 'M' && bottomLeft == 'S') ||
                        (topRight == 'S' && bottomLeft == 'M');
  return firstDiagonal && secondDiagonal;
}

static int solvePart1(long rows, long cols, char grid[rows][cols]){
  int result = 0;

  for(long i = 0; i < rows; i++){
    for(long j = 0; j < cols; j++){
      if(grid[i][j] == 'X'){
        struct Pos xPos = {j, i};
        result += wordSearch(rows, cols, grid, xPos);
      }
    }
  }
  return result;
}

static int solvePart2(long rows, long cols, char grid[rows][cols]){
  int result = 0;

  for(long i = 0; i < rows; i++){
    for(long j = 0; j < cols; j++){
      if(grid[i][j] == 'A' && wordSearchPart2(rows, cols, grid, (struct Pos){j, i})){
        result++;
      }
    }
  }
  return result;
}

int main(void){
  long rows = 0;
  long cols = 0;
  const char *currPath = path;

  initGridSize(currPath, &rows, &cols);
  printf("%ld , %ld\n", rows, cols);

  if(rows <= 0 || cols <= 0){
    return EXIT_FAILURE;
  }

  char grid[rows][cols];
  insertGridData(currPath, rows, cols, grid);

  printGrid(rows, cols, grid);
  printf("Part 1: %d\n", solvePart1(rows, cols, grid));
  printf("Part 2: %d\n", solvePart2(rows, cols, grid));
}

