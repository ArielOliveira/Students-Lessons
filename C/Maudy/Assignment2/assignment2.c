#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define HEADER_LINE 1
#define STAGE_1 1
#define MAX_MALLS 50
#define TOTAL_AREA 2500
#define GRID_COL 500
#define GRID_ROW 500
#define X_MIN -25
#define Y_MAX 25
#define DELTA_X 0.1
#define DELTA_Y 0.1

/* data structure for recording information about one shopping centre */
typedef struct {
    char name;
    double xloc, yloc, glam, carp;
} mall_t;

int read_data(mall_t *malls, int maxmalls);
void print_data(mall_t *malls, int n_malls, int index);
void do_stage1(mall_t *malls, int n_malls, int index);
void discard_lines(int n);
void error_and_exit(char *err, int line);

int 
main(int argc, char *argv[]) {

    mall_t malls[MAX_MALLS];
    int n_malls;
    
    n_malls = read_data(malls, MAX_MALLS);
    do_stage1(malls, n_malls, STAGE_1); 
    
    return 0;
}

int 
read_data(mall_t *malls, int maxmalls) {
    int count = 0;
    char name;
    double xloc, yloc, glam, carp;
    discard_lines(HEADER_LINE);
    
    while (scanf(" %c%lf%lf%lf%lf", &name, &xloc, &yloc, &glam, &carp)==5) {
        if (count==maxmalls) {
            error_and_exit("Too much input data", __LINE__);
        }
        malls[count].name = name; 
        malls[count].xloc = xloc;
        malls[count].yloc = yloc;
        malls[count].glam = glam;
        malls[count].carp = carp;
        count++;
    }
    return count;
}

void
print_data(mall_t *malls, int n_malls, int index) {
    mall_t mall = malls[index];
    
    printf("S1, mall %d = %c, xloc = %5.1lf, yloc = %5.1lf, glam = %4.1lf, carp = %4.1lf\n",
           index, mall.name, mall.xloc, mall.yloc, mall.glam, mall.carp);
}

void
do_stage1(mall_t *malls, int n_malls, int index) {
    printf("S1, %d malls described in input file\n", n_malls);
    for(index=0; index<n_malls; index++) {
        print_data(malls, n_malls, index);
    }
}

void 
discard_lines(int n) {
    int c;
    while ((c=getchar()) != EOF) {
        if (c== '\n') {
            n--;
            if (n==0) return;
        }
    }
    /* Error, as unexpected end of input */
    error_and_exit("Unexpected end of input", __LINE__);
}

void
error_and_exit(char *err, int line) {
	printf("Problem at line %3d: %s\n", line, err);
	exit(EXIT_FAILURE);
}

void
do_stage2(mall_t *malls, int n_malls, int index) {
    double distance, RA;
    
    // midpoint of starting position
    x = X_MIN + DELTA_X/2
    y = Y_MAX - DELTA_Y/2

    for(int i=0; i<GRID_COL; i++) {
        for(int j=0; j<GRID_ROW; j++) {            
            mall_t mall = malls[index];
            x += DELTA_X;
            xval = mall.xloc - x;
            yval = mall.yloc - y;
            distance = sqrt((xval*xval) + (yval*yval));
            RA = mall.glam / (distance + mall.carp) 
        }
        y -= DELTA_Y;
    }
}