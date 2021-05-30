// Slide
// slide.c
//
// This program was written by Su Myat Khine Win (z5179124)
// on 22 March 2021
// Version 1.0.0 (2021-03-08): Initial Assignment Release

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define SIZE 15
#define EMPTY 0
#define STONE 1

#define MOVE_LASER_COMMAND 1
#define MOVE_LASER_DOWNWARDS 1
#define MOVE_LASER_UPWARDS -1
#define FIRE_LASER_COMMAND 2
#define SHIFT_EVERYTHING_LEFT 3 

#define GAME_LOST 0
#define GAME_WON 1

#define ROTATE_MAP_COMMAND 4 
#define ROTATE_MAP_CLOCKWISE_90 1
#define ROTATE_MAP_COUNTER_CLOCKWISE_90 2

// Functions Prototypes
void place_stones(int map[SIZE][SIZE]);
void print_map(int map[SIZE][SIZE], int laser_y);
void play_the_game(int map[SIZE][SIZE], int *laser_y);
int has_won_game(int map[SIZE][SIZE], int *laser_y);
void fire_laser(int map[SIZE][SIZE], int *laser_y);
int has_lost_game(int map[SIZE][SIZE], int *laser_y);
void shift_everything_left(int map[SIZE][SIZE], int *laser_y);
void rotate_map_clockwise_90(int map[SIZE][SIZE], int *laser_y);
void rotate_map_counter_clockwise_90(int map[SIZE][SIZE], int *laser_y);


int main (void) {
    // This line creates our 2D array called "map" and sets all
    // of the blocks in the map to EMPTY.
    int map[SIZE][SIZE] = {EMPTY};
    // creates our laser_y variable. The laser starts in the
    // middle of the map, at position 7.
    int laser_y = SIZE / 2;
    place_stones(map);
    print_map(map, laser_y);
    while (getchar() != EOF ) {
        play_the_game(map, &laser_y); 
        // printf("laser y %d", laser_y); // debugging   
    }
    return 0;
}

/*
=========================================================
Stage 1
=========================================================
*/

/*
    Function    : place_stones 
    parameters  : int map[SIZE][SIZE]
    Description : This function will place stones on the map. 
    The user will need to enter the number of blocks and 
    the position of the stone on the map.The map will be 
    updated accordingly as per the stone values.
    return      : void 
*/
void place_stones(int map[SIZE][SIZE]) {
    int blocks_num;
    int block_row_value;
    int block_col_value;
    int block_value_stone;

    // user input 
    printf("How many blocks? ");
    scanf("%d", &blocks_num);
    printf("Enter blocks:\n");
    while (blocks_num != 0) {
        scanf("%d %d %d", &block_row_value, &block_col_value, &block_value_stone);
        if ((block_row_value >= 0) && (block_row_value < SIZE) 
        && (block_col_value >= 0) && (block_col_value < SIZE)) {
            map[block_row_value][block_col_value] = block_value_stone;
        } 
        blocks_num--;
    }    
}

/*
    Function    : play_the_game
    parameters  : int map[SIZE][SIZE], int *laser_y
    Description : This function will move the laser command 
    > upwards(-1) or downwards(1) on the map. 
    The map will be updated accordingly as per destoried stone values.
    fire_laser function is called inside this function. 
    Please refer to fire_laser function for description.
    return      : void 
*/
void play_the_game(int map[SIZE][SIZE], int *laser_y) {
    int command = 0;
    int laser_direction = 0;
    int rotation_count = 0;

    scanf("%d ", &command);
    if (command == MOVE_LASER_COMMAND ) {
        scanf("%d", &laser_direction);
        switch (laser_direction)
        {
        case MOVE_LASER_DOWNWARDS:
            if ((*laser_y < SIZE)) {
            *laser_y = *laser_y + 1;
            }
            print_map(map, *laser_y); 
            break;   
        case MOVE_LASER_UPWARDS:
            if ((*laser_y > 0)) {
           *laser_y = *laser_y -1;
            }
            print_map(map, *laser_y); 
            break;

        } 
    } else if (command == FIRE_LASER_COMMAND) {
        fire_laser(map, laser_y);
        if ((has_won_game(map, laser_y) == GAME_WON)) {
            print_map(map, *laser_y); 
            printf("Game Won!\n");
            exit(0);
        } else {
            print_map(map, *laser_y); 
        }

    } else if (command == SHIFT_EVERYTHING_LEFT) {
        if ((has_lost_game(map, laser_y) != GAME_LOST)) {
            shift_everything_left(map, laser_y);
            print_map(map, *laser_y);
        } else {
            print_map(map, *laser_y);
            printf("Game Lost!\n");
            exit(0);
        }   
    } else if ((command == ROTATE_MAP_COMMAND)) {
        scanf("%d", &rotation_direction);
        if (rotation_count < 1) {
            switch (rotation_direction)
            {
            case ROTATE_MAP_CLOCKWISE_90:
                rotate_map_clockwise_90(map, laser_y);
                print_map(map, *laser_y);  
                rotation_count--;
            case ROTATE_MAP_COUNTER_CLOCKWISE_90:
                rotate_map_counter_clockwise_90(map, laser_y);
                print_map(map, *laser_y);
            } 
        }
        rotation_count--; 
    }   
}

/*
    Function    : fire_laser
    parameters  : int map[SIZE][SIZE], int *laser_y
    Description : This function will accept user input (2) 
    for destory stones. The check for valid user input 2 and 
    the maxinum num of stones that can be destoryed, 
    which is 4, is also included in the function.
    return      : void 
*/

void fire_laser(int map[SIZE][SIZE], int *laser_y) {
    int fire_laser = 0;
    scanf("%d", &fire_laser);
    int destoried_stones = 0;
    if (fire_laser == FIRE_LASER_COMMAND) {
        for (int i = 0; i < SIZE; i++) {
            if ((map[*laser_y][i] == STONE) && (destoried_stones < 4)) {
                map[*laser_y][i] = EMPTY;
                destoried_stones++;
            }
        }
        print_map(map, *laser_y);
    }
}

/*
    Function    : print_map
    parameters  : int map[SIZE][SIZE], int *laser_y
    Description : This function will print the map out 
    the contents of the map array and a > symbol 
    to denote the current laser position. The stones and > 
    on the map will reflect the changes as per various user inputs.
    return      : void 
*/
void print_map(int map[SIZE][SIZE], int laser_y) {
    int i = 0;
    while (i < SIZE) {
        if (i == laser_y) {
            printf("> ");
        } else {
            printf("  ");
        }
        int j = 0;
        while (j < SIZE) {
            printf("%d ", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

/*
=========================================================
Stage 2
=========================================================
*/

/*
    Function    : shift_everything_left
    parameters  : int map[SIZE][SIZE], int *laser_y
    Description : This function will shift all the items in the 
    array by one position (column) after receiving the user 
    input command 3.
    return      : void 
*/

void shift_everything_left(int map[SIZE][SIZE], int *laser_y) {
    
    int shift_left = 0;
    scanf("%d", &shift_left);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE;j++) {
            if (j+ 1 < SIZE) {
                map[i][j] = map[i][j+1];
            }
        }
    }
    print_map(map, *laser_y);
}

/*
    Function    : has_won_game
    parameters  : int map[SIZE][SIZE], int *laser_y
    Description : This function will determine "Game Won status"
    by checking the entire map. If the entire map is empty,
    the game has won.
    return      : void 
    0 is used to present false.
    1 is used to represent true.
*/
int has_won_game(int map[SIZE][SIZE], int *laser_y) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] != EMPTY) {
                return GAME_LOST;       
            } 
        }
    }
    return GAME_WON;
}

/*
    Function    : has_lost_game
    parameters  : int map[SIZE][SIZE], int *laser_y
    Description : This function will determine "Game Lost status"
    by checking two conditions:
    1) There is any STONE on the left-most column as a 3 
    (shift everything left) command is given.
    2) If the entire left row of the map is "NOT" EMPTY 
    prior to shifting everything left. 
    return      : void 
*/
int has_lost_game(int map[SIZE][SIZE], int *laser_y) {
    for (int i = 0; i < SIZE; i++) {
        if (map[i][0] == EMPTY) {
            continue;
        }
    }
    return GAME_LOST;
}

/*
=========================================================
Stage 3
=========================================================
*/

/*
    Function    : rotate_map_clockwise_90
    parameters  : int map[SIZE][SIZE], int *laser_y
    Description : This function will rotate the map by 90
    clockwise and do it in-place (Space Complexity O(1)).
    The rotation is done in 2 steps process:
    1) Move first column to first row using in place swapping.
    2) Use two pointer technique to swap left and right columns
    elements 
    return      : void 
*/
void rotate_map_clockwise_90(int map[SIZE][SIZE], int *laser_y) {
    
    // This first for loop will rotate map and then move
    // the first column to first row and so on.
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = temp;
        }
    }

    // Two Pointer technique is used to swap the corresponding
    // elements between left and right columns. 
    for (int i = 0; i < SIZE; i++) {
        int left_pointer = 0;
        int right_pointer = SIZE -1;
        while (left_pointer < right_pointer/2) {
            int temp = map[i][left_pointer];
            map[i][left_pointer] = map[i][right_pointer];
            map[i][right_pointer] = temp;
            left_pointer++;
            right_pointer--;
        }
    }
}

/*
    Function    : rotate_map_counter_clockwise_90
    parameters  : int map[SIZE][SIZE], int *laser_y
    Description : This function will rotate the map by 90
    clockwise and do it in-place (Space Complexity O(1)).
    The rotation is done in 2 steps process:
    1) Move first column to first row using in place swapping.
    2) Use two pointer technique to swap left and right columns
    elements 
    return      : void 
*/

void rotate_map_counter_clockwise_90(int map[SIZE][SIZE], int *laser_y) {
    
    // This first for loop will rotate map and then move
    // the first column to first row and so on.
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = temp;
        }
    }

    // Two Pointer technique is used to swap the corresponding
    // elements between top and bottom rows. 
    int top= 0;
    int bottom = SIZE -1;
    for (int i = 0; i < SIZE; i++) {
        int temp = map[top][i];
        map[top][i] = map[bottom][i];
        map[bottom][i] = temp;
    }
}

