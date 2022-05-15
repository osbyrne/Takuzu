#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* row_coordinates = {"abcdefgh"};
char* column_coordinates = {"12345678"};
unsigned **grid, **mask, size, i, j;

unsigned get_random_value(unsigned range) {
  unsigned k = time(NULL);
  unsigned l = getpid();
  srand(k + l);
  printf("\n%d\n%d\n", k, l);
  unsigned val = rand() % range;
  return val;
}

unsigned verify_no_grouping_of_three() {
  unsigned row_streak, column_streak = 0;
  unsigned last_row_number, last_column_number = 0;
  
  for (unsigned row = 0; row < size; row++) {
    for (unsigned column = 0; column < size; column++) {
      
      if (last_row_number == grid[row][column]){
        row_streak++;
        if (row_streak == 3){
          return 0;
        }
      } 
      else {
        last_row_number = grid[row][column];
      }

      if (last_column_number == grid[column][row]){
        column_streak++;
        if (column_streak == 3){
          return 0;
        }
      } 
      else {
        last_column_number = grid[column][row];
      }
    }
  }
  return 1;
}

unsigned array_of_unique_values(unsigned* array) {
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      if (i!=j && j>i){
        if (array[i] == array[j]) {
          return 0;
        }
      }
    }
  }
  return 1;
}

unsigned verify_no_twins() {
  
  unsigned *rows_decimal = malloc(sizeof(unsigned *) * size);
  for (i = 0; i < size; i++) {
    rows_decimal[i] = 0;
  } 
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      rows_decimal[i] += 2^grid[i][j];
    }
  }
  if (array_of_unique_values(rows_decimal) == 0) {
    return 0;
  }
  
  unsigned *column_decimal = malloc(sizeof(unsigned *) * size);
  for (i = 0; i < size; i++) {
    column_decimal[i] = 0;
  }  
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      column_decimal[i] += 2^grid[j][i];
    }
  }
  if (array_of_unique_values(column_decimal) == 0) {
    return 0;
  }
  return 1;
}

unsigned verify_no_imbalance() {
  unsigned row_zeroes, row_ones = 0;
  unsigned column_zeroes, column_ones = 0;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      if (grid[i][j] == 0) {
        row_zeroes++;
      } else {
        row_ones++;
      }
      if (grid[j][i] == 0) {
        column_zeroes++;
      } else {
        column_ones++;
      }
    }
  }
  if (row_zeroes != row_ones || column_zeroes != column_ones) {
    return 0;
  }
  return 1;
}

unsigned verify_grid_vailidity() {
  if (
    verify_no_grouping_of_three() == 0 ||
    verify_no_twins() == 0 ||
    verify_no_imbalance() == 0
  ) {
    return 0;
  } else {
    return 1;
  }  
}

void fill_grid() {
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      grid[i][j] = get_random_value(2);
    }
  }
}

void generate_the_grid() {
  grid = malloc(sizeof(unsigned *) * size);
  for (i = 0; i < size; i++) {
    grid[i] = malloc(sizeof(unsigned *) * size);
    for (j = 0; j < size; j++) {
      grid[i][j] = get_random_value(2);
    }
  }
  fill_grid();
}

void get_grid_size() {
  printf("Ready to go! how large do you want your grid to be?\n");
  while (size != 4 && size != 8) {
    printf("gottta choose either 4 or 8!\n\n> ");
    scanf("%d", &size);
  }
  printf("you chose a grid of length %d!\n", size);
}

void display_the_grid() {
  printf("\n        ");
  for (i = 0; i < size; i++) {
    printf("%c  ", column_coordinates[i]);
  } printf("\n");

  for (i = 0; i < size; i++) {
    printf("\n  %c     ", row_coordinates[i]);
    for (j = 0; j < size; j++) {printf("%d  ", grid[i][j]);}
  } printf("\n\n");
}

unsigned from_row_index_to_grid_latitude(char row_index) {
  for (i = 0; i<size; i++) {
    if (row_index == row_coordinates[i]) {
      return i;
    }
  }
  return 0;
}

unsigned from_column_index_to_grid_longitude(char column_index) {
  for (i = 0; i<size; i++) {
    if (column_index == column_coordinates[i]) {
      return i;
    }
  }
  return 0;
}

unsigned cell_is_free(unsigned x, unsigned y) {
  unsigned cell_locked = 1;
  
  for (i = 0; i<size; i++) {
    for (j = 0; j<size; j++) {
      if (i == x && j == y) {
        if (mask[i][j] == 1){
          return 0;
        }
      }
    }
  }
  return 1;
}

void do_swap(unsigned x, unsigned y) {
 
  
  if (grid[x][y] == 2) {
    grid[x][y] = 0;
  } else {
    grid[x][y]++;
  }
}

void manual_cell_swap() {
  char row_index;
  printf("\ngive a row > ");
  scanf("%s", &row_index);
  unsigned x = from_row_index_to_grid_latitude(row_index);

  char column_index;
  printf("\ngive a column > ");
  scanf("%s", &column_index);
  unsigned y = from_column_index_to_grid_longitude(column_index);
  
  if (cell_is_free(x, y) == 1) {
    do_swap(x, y);
  }
}

unsigned grid_is_complete() {
  for (int i = 0; i<size; i++) {
    for (int j = 0; j<size; j++) {
      if (grid[i][j] != 0 && grid[i][j] != 1) {
        return 0;
      }
    }
  }
  return 1;
}

void generate_correct_grid() {
  get_grid_size();
  generate_the_grid();
  while (verify_grid_vailidity() == 0) {
    display_the_grid();
    unsigned x = get_random_value(size);
    unsigned y = get_random_value(size);
    grid[x][y] = get_random_value(2);
  }
  printf("There it is! a working grid:\n\n");
  display_the_grid();
}

void solve_grid_manually() {
  unsigned lives = 8;
  while(1){
    
    printf("\nlives: ");
    for (i = 0; i<lives; i++) {
      printf("#");
    }
    display_the_grid();
    
    printf("press 0 to quit\n");
    printf("\n> ");
    unsigned choice;
    scanf("%d", &choice);
    if (choice == 0) {break;}
    
    if (verify_grid_vailidity() == 1) {
      printf("you did it! BRAVO\n\n");
      break;
    }
  }
}

void solve_grid_automaticaly() {
  printf("\n\n---unfinished work area---\n\n");
}
 
void game_time() {
  while(1){
    printf("press 0 to quit\n");
    printf("press 1 to solve a grid manually\n");
    printf("press 2 to automaticaly solve a grid\n");
    printf("\n> ");
    unsigned choice;
    scanf("%d", &choice);
    
    if (choice == 0) {break;}    
    if (choice == 1) {solve_grid_manually();}
    if (choice == 2) {solve_grid_automaticaly();}
  }
}


int main() {
  unsigned k = get_random_value(5);
  printf("\n%d\n\n", k);
  unsigned v = get_random_value(5);
  printf("\n%d\n\n", v);
  generate_correct_grid();
  while(1) {
    
    printf("press 0 to quit\n");
    printf("press 1 to start a game!\n");
    printf("\n> ");
    
    unsigned choice;
    scanf("%d", &choice);
    
    if (choice == 0) {break;}
    if (choice == 1) {   
      game_time();
    } 
  }
}
