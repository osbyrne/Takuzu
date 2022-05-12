#include <stdio.h>
#include <stdlib.h>

char* row_coordinates = {"abcdefgh"};
char* column_coordinates = {"12345678"};

int verify_grid_integrity(int **grid, int size) {
  int row_zeroes, row_ones = 0;
  int column_zeroes, column_ones = 0;
  int row_streak, column_streak = 0;
  int last_row_number, last_column_number = 0;

  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {

      if (grid[row][column] == 0){
        row_zeroes++;
      } else {
        row_ones++;
      }
      if (grid[column][row] == 0){
        column_zeroes++;
      } else {
        column_ones++;
      }

      if (last_row_number == grid[row][column]){
        row_streak++;
        if (row_streak == 3){
          return 0;
        }
      } else {
        last_row_number = grid[row][column];
      }

      if (last_column_number == grid[column][row]){
        column_streak++;
        if (column_streak == 3){
          return 0;
        }
      } else {
        last_column_number = grid[column][row];
      }
    }
  }
  if (row_zeroes != row_ones || column_zeroes != column_ones){
    return 0;
  }
  //there cannot be two identical rows/columns in a grid
  //don't know how to do this one right now but perhaps later
  return 1;
}

int **generate_the_grid(int size) {
  int **grid = malloc(sizeof(int *) * size);

  for (int i = 0; i < size; i++) {
    grid[i] = malloc(sizeof(int *) * size);
  }
  return grid;
}

int get_grid_size() {
  int size;
  while (size != 4 && size != 8) {
    printf("gottta choose a grid size of either 4 or 8!\n\n> ");
    scanf("%d", &size);
  }
  printf("you chose a grid of length %d!\n", size);
  return size;
}

void display_the_grid(int **grid, int size) {

  printf("\n        ");
  for (int i = 0; i < size; i++) {
    printf("%c  ", column_coordinates[i]);
  } printf("\n");

  for (int i = 0; i < size; i++) {
    printf("\n  %c     ", row_coordinates[i]);
    for (int j = 0; j < size; j++) {printf("%d  ", grid[i][j]);}
  } printf("\n\n");
}

void free_memory(int** grid, int size) {
  for (int i = 0; i < size; i++) {
    free(grid[i]);
    grid[i] = NULL;
  }
  free(grid);
}

void swap_cell(int** grid, int size, char* cell_index) {
  char x = cell_index[0];
  char y = cell_index[1];
  if (grid[x][y] == 2) {
    grid[x][y] = 0;
  } else {
    grid[x][y]++;
  }
}

int main() {
  int size = get_grid_size();
  int **grid = generate_the_grid(size);
  while(1) {
    display_the_grid(grid, size);
    if (verify_grid_integrity(grid, size) == 1) {
      printf("you did it! BRAVO\n\n");
      break;
    }

    char row_index;
    printf("\ngive a row > ");
    scanf("%s", &row_index);

    char column_index;
    printf("\ngive a column > ");
    scanf("%s", &column_index);


    swap_cell(grid, size, cell_index);

    printf("__end of test__\n\n");
    break;
  }
  free_memory(grid, size);
  return 0;
}
