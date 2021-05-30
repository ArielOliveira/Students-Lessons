#include <stdio.h>
#include <stdlib.h>

#define IMAGE_SIZE 10

int** vis;
int hasChanged = 0;

enum CELL_STATE {
    UNVISITED,
    GROUP,
    VISITED
};

// this function prints the array
void printImgArray(int** array) {
  
    printf("------ Image Contents -------\n");
    for (int i=0; i<IMAGE_SIZE; i++)
    {
    for (int j=0; j<IMAGE_SIZE; j++)
        printf("%02d, ",array[i][j]);
    printf("\n");
    }
    printf("-----------------------------\n");
}

int isValid(int** image, int size, int label, int x, int y) {
    if (x < 0 || x > size-1 || y < 0 || y > size-1)
        return 0;
    
    if (vis[x][y] == VISITED || image[x][y] == 0)
        return 0;

    return 1;
}

void dfs(int** image, int size, int label, int x, int y) {
    if (x < 0 || x > size-1 || y < 0 || y > size-1) {
        puts("Invalid array access! Aborting");
        exit(-1);
    }

    if (image[x][y] == 1 && vis[x][y] != VISITED) {
        image[x][y] = label;
        hasChanged = 1;
    }

    vis[x][y] = VISITED;
    
    // LEFT
    if (isValid(image, size, label, x-1, y))
        dfs(image, size, label, x-1, y);

    // RIGHT
    if (isValid(image, size, label, x+1, y))
        dfs(image, size, label, x+1, y);

    // UP
    if (isValid(image, size, label, x, y-1))
        dfs(image, size, label, x, y-1);

    // DOWN
    if (isValid(image, size, label, x, y+1))
        dfs(image, size, label, x, y+1);

    // TOP-LEFT
    if (isValid(image, size, label, x-1, y-1))
        dfs(image, size, label, x-1, y-1);

    // TOP-RIGHT
    if (isValid(image, size, label, x+1, y-1))
        dfs(image, size, label, x+1, y-1);
    
    // BOTTOM-LEFT
    if (isValid(image, size, label, x-1, y+1))
        dfs(image, size, label, x-1, y+1); 

    // BOTTOM-RIGHT
    if (isValid(image, size, label, x+1, y+1))
        dfs(image, size, label, x+1, y+1);
}


int search(int** image, int size) {
    int x = 0, y = 0;
    int label = 1;

    while ((x < IMAGE_SIZE && y < IMAGE_SIZE)) {
        dfs(image, size, label, x, y);
        
        if (hasChanged)
            label++;
        
        y++;
        if (y > IMAGE_SIZE-1) {
            y = 0;
            x++;
        } 
        hasChanged = 0;
    }
}


int main (void) {

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

    int i = 0;
    int j = 0;
    int** image = (int**)malloc(sizeof(int*) * IMAGE_SIZE);
    for (i = 0; i < IMAGE_SIZE; i++)
        image[i] = (int*)malloc(sizeof(int) * IMAGE_SIZE);

    for (i = 0; i < IMAGE_SIZE; i++)
        for (j = 0; j < IMAGE_SIZE; j++)
            image[i][j] = cellImg[i][j];


    vis = (int**)malloc(sizeof(int*) * IMAGE_SIZE);
    for (i = 0; i < IMAGE_SIZE; i++)
        vis[i] = (int*)malloc(sizeof(int) * IMAGE_SIZE);

    for (i = 0; i < IMAGE_SIZE; i++)
        for (j = 0; j < IMAGE_SIZE; j++)
            vis[i][j] = 0;

    search(image, IMAGE_SIZE);
    puts("Printing Image");
    printImgArray(image);

    puts("Printing Visited Cells");
    printImgArray(vis);

    return 0;
}