#include <stdio.h>
#include <stdlib.h>

char* row_coordinates = {"abcdefgh"};
char* column_coordinates = {"12345678"};
unsigned** grid;
unsigned size;
unsigned lives = 80;

unsigned verify_grid_integrity() {
  unsigned row_zeroes, row_ones = 0;
  unsigned column_zeroes, column_ones = 0;
  unsigned row_streak, column_streak = 0;
  unsigned last_row_number, last_column_number = 0;

  for (unsigned row = 0; row < size; row++) {
    for (unsigned column = 0; column < size; column++) {

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
          printf("there's");
          lives -= 1;
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

unsigned **generate_the_grid() {
  unsigned **grid = malloc(sizeof(unsigned *) * size);

  for (unsigned i = 0; i < size; i++) {
    grid[i] = malloc(sizeof(unsigned *) * size);
  }
  return grid;
}

void fill_the_grid(){
  if(not verify_grid_integrity){
    printf("a")
  }
}

unsigned get_grid_size() {
  unsigned size;
  while (size != 4 && size != 8) {
    printf("gottta choose a grid size of either 4 or 8!\n\n> ");
    scanf("%d", &size);
  }
  printf("you chose a grid of length %d!\n", size);
  return size;
}

void display_the_grid() {
  printf("\n        ");
  for (unsigned i = 0; i < size; i++) {
    printf("%c  ", column_coordinates[i]);
  } printf("\n");

  for (unsigned i = 0; i < size; i++) {
    printf("\n  %c     ", row_coordinates[i]);
    for (unsigned j = 0; j < size; j++) {printf("%d  ", grid[i][j]);}
  } printf("\n\n");
}

unsigned from_row_index_to_grid_latitude(char row_index) {
  for (unsigned i=0; i<size; i++) {
    if (row_index == row_coordinates[i]) {
      return i;
    }
  }
}

unsigned from_column_index_to_grid_longitude(char column_index) {
  for (unsigned i=0; i<size; i++) {
    if (column_index == column_coordinates[i]) {
      return i;
    }
  }
}

void swap(unsigned x, unsigned y) {
  if (grid[x][y] == 2) {
    grid[x][y] = 0;
  } else {
    grid[x][y]++;
  }
}

unsigned main() {
  size = get_grid_size();
  grid = generate_the_grid();
  fill_the_grid();
  while(1) {
    display_the_grid();
    if (verify_grid_integrity() == 1) {
      printf("you did it! BRAVO\n\n");
      break;
    }
    
    char row_index;
    printf("\ngive a row > ");
    scanf("%s", &row_index);
    unsigned x = from_row_index_to_grid_latitude(row_index);

    char column_index;
    printf("\ngive a column > ");
    scanf("%s", &column_index);
    unsigned y = from_column_index_to_grid_longitude(column_index);
    
    swap(x, y);
    display_the_grid();
    printf("__end of test__\n\n");
    break;
  }
  for (unsigned i = 0; i < size; i++) {
    free(grid[i]);
    grid[i] = NULL;
  }
  free(grid);
  return 0;
}
