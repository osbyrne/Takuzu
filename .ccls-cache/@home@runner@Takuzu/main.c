#include <stdio.h>
#include <stdlib.h>

int *get_row_data(char **grid, int size, int row) {
  int *row_data = malloc(sizeof(int *) * size);
  for (int i = 0; i < size; i++) {
    row_data[i] = grid[i][row];
  }
  return row_data;
}

int *get_column_data(char **grid, int size, int column) {
  int *column_data = malloc(sizeof(int *) * size);
  for (int i = 0; i < size; i++) {
    column_data[i] = grid[i][column];
  }
  return column_data;
}

int verify_grid_integrity(char **grid, int size) {
  printf("grid is complete!\n");
  return 1;
}

int randomly_fill_some_parts_of_the_grid(char **grid, int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; i < size; i++) {
      if (rand() % 4) {
        if (rand() % 2) {
          grid[i][j] = "0";
        } else {
          grid[i][j] = "1";
        }
      } else {
        grid[i][j] = "x";
      }
    }
  }
  return 0;
}

char **generate_the_grid(int size) {
  char **grid = malloc(sizeof(char *) * size);

  for (int i = 0; i < size; i++) {
    grid[i] = malloc(sizeof(char *) * size);
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

int display_the_grid(char **grid, int size) {
  for (int i = 0; i < size; i++) {
    printf("\n");
    for (int j = 0; j < size; j++) {
      printf("%c", grid[i][j]);
    }
  }
  printf("\n\n");
  return 0;
}

int main() {
  int size = get_grid_size();
  char **grid = generate_the_grid(size);
  randomly_fill_some_parts_of_the_grid(grid, size);

  while (1) {
    display_the_grid(grid, size);

    if (verify_grid_integrity(grid, size) == 1) {
      printf("you did it! BRAVO\n\n");
      break;
    }
  }

  // free de grid memory
  for (int i = 0; i < size; i++) {
    free(grid[i]);
    grid[i] = NULL;
  }
  free(grid);
  return 0;
}
