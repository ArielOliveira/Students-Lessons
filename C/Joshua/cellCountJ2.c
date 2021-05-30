#include<stdio.h>
#include<stdlib.h>
#define IMAGE_SIZE 10


// tried to initialize my DFS method in the header
int DFS(int array[IMAGE_SIZE][IMAGE_SIZE], int row, int column, int uniqueCell, int visited[IMAGE_SIZE][IMAGE_SIZE]);

// this function prints the array
void printImgArray(int array[IMAGE_SIZE][IMAGE_SIZE])
{
  
    printf("------ Image Contents -------\n");
    for (int i=0; i<IMAGE_SIZE; i++)
    {
    for (int j=0; j<IMAGE_SIZE; j++)
        printf("%02d, ",array[i][j]);
    printf("\n");
    }
    printf("-----------------------------\n");
}

/**
 * This function counts the number of distinct 
 * number (i.e. the number of cells)
 **/

int cellCount(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task1.1 here
    // you may want to change the return value. 


    int visited[IMAGE_SIZE][IMAGE_SIZE] = {0};

    // Int to count unique cells found
    int uniqueCells = 0;
    
    for (int i = 0; i < IMAGE_SIZE; i++) {
      for (int j = 0; j < IMAGE_SIZE; j++){
        // Calls Depth-First Search on a value of 1 found within the array
        if (image[i][j] == 1 && visited[i][j] != 1) {
          DFS(image, i, j, uniqueCells, visited);
          // Increments unique cell count to determine amount of cell clusters in 2d array
          uniqueCells++;
        }

      }
    }
    return uniqueCells;
}


int DFS(int array[IMAGE_SIZE][IMAGE_SIZE], int row, int column, int uniqueCell, int visited[IMAGE_SIZE][IMAGE_SIZE]) {

  // Boundry Check
  if (row < 0 || column < 0 || row >= IMAGE_SIZE || column >= IMAGE_SIZE) {
    return 0;
  }
  if (array[row][column] == 0) {
    return 0;
  }

  // if the value is 0 we know cellCount is calling the method, so we dont change array
  // if the value is 1, then we know color is being called so we change the array point to a new value

  // arrays to store all 8 neighbor positions
  // for example, when called in a for loop i = 0 would give (-1, 1) or the top left neighbor position
  int rowIndex[] = {-1, 0, 1, -1, 1, -1, 0 ,1};
  int colIndex[] = {1, 1, 1, 0, 0, -1, -1, -1};

  // Change value of vertex to 2 so it wont be revisited
  array[row][column] = uniqueCell + 1;

  // Sets coords of copy array to 1 to indicate the point has been visited
  visited[row][column] = 1;

  // for loop goes through all neighbors of the vertex and performs Depth-First Searches on them until they're no 1's left
  for (int i = 0; i < 8; i++) {
    if (array[row + rowIndex[i]] [column + colIndex[i]] == 1 && visited[row + rowIndex[i]] [column + colIndex[i]] == 0) {
      DFS(array, row + rowIndex[i], column + colIndex[i], uniqueCell, visited);
    }
  }
  return 0;
}

/**
 * This function colors each cell with a unique color
 * (i.e. unique number)
 **/
void color(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task 1.2 here

  int visited[IMAGE_SIZE][IMAGE_SIZE] = {0};

  int clusterID = 0;

    for (int i = 0; i < IMAGE_SIZE; i++) {
      for (int j = 0; j < IMAGE_SIZE; j++){
        // Calls Depth-First Search on a value of 1 found within the array
        if (image[i][j] == 1 && visited[i][j] != 1) {
          DFS(image, i, j, clusterID, visited);
          // Increments unique cell count to determine amount of cell clusters in 2d array
          clusterID++;
        }

      }
    }

  
}

/**
 * This function colors each cell with a unique color
 * (i.e., unique number). This function works with 
 * pointers
 * currentRow: shows the current row that is processed
 * currentCol: shows the current column that is process
 * currentIndex: show the index that is processed
 * color: is an integer that represents a color
 **/

int colorRecursively(int image[IMAGE_SIZE][IMAGE_SIZE], int currentRow, int currentCol, int currentIndex, int color) {
    // insert your code for task 2.1 here, in case you decided to complete this task
    // you may want to change the return value
    return 0;
 
}
void colorPtr(int* image){
    // insert your code for task 2.2 here

}
 

#ifndef __testing
int main(){

    // DO not change anything in main(), it will confuse the
    // auto-checker.  
    puts("testing the code with color() function");
    int count = 0;
    int cellImg[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};

    printImgArray(cellImg);
    color(cellImg);
    printImgArray(cellImg);
    count=cellCount(cellImg);
    printf("Total number of cells in the image: %d\n",count);
 

    puts("Testing the code with colorPtr");
    int cellImg_[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};

    int* ptr = cellImg_;
    printImgArray(ptr);
    colorPtr(ptr);
    printImgArray(ptr);
    count=cellCount(ptr);
    printf("Total number of cells in the image: %d\n",count); 
    puts("Testing the code with colorRecursively");
    int cellImg__[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};
    printImgArray(cellImg__);
    colorRecursively(cellImg__, 0, 0, 1, 0);
    printImgArray(cellImg__);
    count=cellCount(cellImg__);
    printf("Total number of cells in the image: %d\n",count);
    return 0;
}
#endif