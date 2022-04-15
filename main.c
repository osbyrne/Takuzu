#include <stdio.h>
#include <stdlib.h>

void display_grid(int grid, int size){
  for(int i=0; i<size; i++){
    printf("\n");
    for(int j=0; j<size; j++){
      printf("%d", grid[i][j]);
    }
  }
}

int choose_size(){
  printf("\nchoose your takuzu grid size:\nfor a 4x4 grid: write 4\nfor a 8x8 grid: write 8\n\n> ");
  int size;
  int choice_initiated = 0;
  while(size!=4 || size!=8){
    if(choice_initiated==1){printf("your input was incorrect\n");}
    scanf("%d", &size);
    choice_initiated = 1;
  }
  printf("you chose a grid of length %d!\n", size);
  return size;
}

int main(){
  int size = choose_size();
  
  int grid[size][size];
  for(int i=0; i<size; i++){
    for(int j=0; j<size; j++){
      grid[i][j] = 0;
    }  
  }
  display_grid(grid, size);
  return 0;
}
