#include <stdbool.h>

void solveSudoku(char** board, int boardRowSize, int boardColSize);
bool validAnsExist(char** board, int row, int col);
bool isValid(char** board, char testAns, int row, int col);
