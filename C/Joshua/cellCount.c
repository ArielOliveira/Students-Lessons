#include<stdio.h>
#include<stdlib.h>
#define IMAGE_SIZE 10
#define VISITED 1
#define WALL 0

int vis[IMAGE_SIZE][IMAGE_SIZE] = {0};

int hasChanged = 0;

void clearArray(int size, int array[size][size]) {
    int i = 0, j = 0;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            array[i][j] = 0;
}

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



int isValid(int image[IMAGE_SIZE][IMAGE_SIZE], int visited[IMAGE_SIZE][IMAGE_SIZE], int size, int wall, int x, int y) {
    if (x < 0 || x > size-1 || y < 0 || y > size-1)
        return 0;
    
    if (visited[x][y] == VISITED || image[x][y] == wall) {
        visited[x][y] = VISITED;
        return 0;
    }
    return 1;
}

void dfs(int image[IMAGE_SIZE][IMAGE_SIZE], int size, int label, int wall, int x, int y) {
    if (x < 0 || x > size-1 || y < 0 || y > size-1) {
        puts("Invalid array access! Aborting");
        exit(-1);
    }

    if (image[x][y] != wall && vis[x][y] != VISITED) {
        image[x][y] = label;
        hasChanged = 1;
    }

    vis[x][y] = VISITED;

    int xDir[] = {-1, 1,  0, 0, -1, -1, 1,  1};
    int yDir[] = { 0, 0, -1, 1,  1, -1, 1, -1};
    int i;
    
    for (i = 0; i < 8; i++) {
        int nextX = x + xDir[i];
        int nextY = y + yDir[i];

        if (isValid(image, vis, size, wall, nextX, nextY))
            dfs(image, size, label, wall, nextX, nextY);
    }
}

/**
 * This function counts the number of distinct 
 * number (i.e. the number of cells)
 **/

int cellCount(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task1.1 here
    // you may want to change the return value. 
    int x = 0, y = 0;
    int count = 0;

    clearArray(IMAGE_SIZE, vis);

    while ((x < IMAGE_SIZE && y < IMAGE_SIZE)) {
        dfs(image, IMAGE_SIZE, 1, WALL, x, y);
        
        if (hasChanged)
            count++;
        
        y++;
        if (y > IMAGE_SIZE-1) {
            y = 0;
            x++;
        } 
        hasChanged = 0;
    }
    
    return count;
}
/**
 * This function colors each cell with a unique color
 * (i.e. unique number)
 **/
void color(int image[IMAGE_SIZE][IMAGE_SIZE]) {
    // insert your code for task 1.2 here
    int x = 0, y = 0;
    int count = 1;

    clearArray(IMAGE_SIZE, vis);

    while ((x < IMAGE_SIZE && y < IMAGE_SIZE)) {
        dfs(image, IMAGE_SIZE, count, WALL, x, y);
        
        if (hasChanged)
            count++;
        
        y++;
        if (y > IMAGE_SIZE-1) {
            y = 0;
            x++;
        } 
        hasChanged = 0;
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
int anotherVisited[IMAGE_SIZE][IMAGE_SIZE] = {0};

int colorRecursively(int image[IMAGE_SIZE][IMAGE_SIZE], int currentRow, int currentCol, int currentIndex, int color) {
    // insert your code for task 2.1 here, in case you decided to complete this task
    // you may want to change the return value
    if (currentRow < 0 || currentRow > IMAGE_SIZE-1 || currentCol < 0 || currentCol > IMAGE_SIZE-1) {
        puts("Invalid array access! Aborting");
        return -1;
    }

    if (image[currentRow][currentCol] != 0 && anotherVisited[currentRow][currentCol] != VISITED) {
        image[currentRow][currentCol] = color;
    }

    anotherVisited[currentRow][currentCol] = VISITED;

    int xDir[] = {-1, 1,  0, 0, -1, -1, 1,  1};
    int yDir[] = { 0, 0, -1, 1,  1, -1, 1, -1};
    int i;
    
    for (i = 0; i < 8; i++) {       
        int nextX = currentRow + xDir[i];
        int nextY = currentCol + yDir[i];
        
        if (isValid(image, anotherVisited, IMAGE_SIZE, 0, nextX, nextY))
            colorRecursively(image, nextX, nextY, currentIndex+1, color);
    }
    
    if (currentIndex == 1) {
        if (currentRow < IMAGE_SIZE) {
            currentCol++;
            if (currentCol > IMAGE_SIZE-1) {
                currentCol = 0;
                currentRow++;
            }
            // Ensures we are still inside the map (fixes out of bounds, not a big deal though)
            if (currentRow < IMAGE_SIZE) {
                int increaseColor = 0;

                // For the next "first case" recursion (currentIndex = 1 with new position), 
                // checks all neighbours for a valid path  
                for (i = 0; i < 8; i++) {       
                    int nextX = currentRow + xDir[i];
                    int nextY = currentCol + yDir[i];
                    
                    // If there is a valid path, we can increase color
                    if (isValid(image, anotherVisited, IMAGE_SIZE, 0, nextX, nextY)) 
                        increaseColor = 1;
                }

                if (increaseColor)
                    color++;

                // The result is the next recursion will only be assigned
                // with a new color if it knows there is a cluster nearby
                // before hand
                colorRecursively(image, currentRow, currentCol, currentIndex, color);
            }
        }
    }

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
    //printImgArray(cellImg__);
    colorRecursively(cellImg__, 0, 0, 1, 1);
    printImgArray(cellImg__);
    printImgArray(anotherVisited);
    count=cellCount(cellImg__);
    printf("Total number of cells in the image: %d\n",count);
    return 0;
}
#endif