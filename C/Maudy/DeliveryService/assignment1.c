/* Solution to comp20005 Assignment 1, 2021 semester 1.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Maudy Chahine 1118360
   Dated:     25/04/2021

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ORDERS 999
#define MIN_PER_HOUR 60
#define HEADER_LINE 1
#define CNST_SPEED 17.3
#define RECOVERY_TIME 5
#define MAX_DRONES 26

struct Order {
    int orderNumber;
    int RFD;
};

void discard_lines(int n);
int read_data(int orders[], int rfdmmm[],  double delivx[], double delivy[]);
void print_order_rfd(int orders[], int rfdmmm[], double delivx[],double delivy[], 
                int index); 
void do_stage1(int orders[], int rfdmmm[], double delivx[], 
              double delivy[], int n);
void do_stage2(int orders[], int rfdmmm[], double delivx[], double delivy[], int time[], int n);
int flight_time(double delivx,double delivy);


int main(int argc, char* argv[]) {
    int orders[MAX_ORDERS], rfdmmm[MAX_ORDERS];
    double delivx[MAX_ORDERS], delivy[MAX_ORDERS];
    int time[MAX_ORDERS];
    int n;
    
    n = read_data(orders, rfdmmm, delivx, delivy);
    do_stage1(orders, rfdmmm, delivx, delivy, n);
    do_stage2(orders, rfdmmm, delivx, delivy, time, n);
    
    return 0;
}
   
void discard_lines(int n) {
    int c;
    while ((c=getchar()) != EOF) {
        if (c== '\n') {
            n--;
            if (n==0) return;
        }
    }
    /* Error, as unexpected end of input */
    exit(EXIT_FAILURE); 
}

int read_data(int orders[], int rfdmmm[],  double delivx[], double delivy[]) {
    int order, rfdhh, rfdmm, count = 0;
    double xcoord, ycoord;
    discard_lines(HEADER_LINE);
    
    while (scanf("%d %d %d %lf %lf", &order, &rfdhh, &rfdmm, &xcoord, &ycoord) == 5) {
        orders[count] = order; 
        rfdmmm[count] = rfdhh*MIN_PER_HOUR + rfdmm;
        delivx[count] = xcoord;
        delivy[count] = ycoord;
        count++;
    }
    return count;
}


void 
print_order_rfd(int orders[], int rfdmmm[], double delivx[],double delivy[], 
                int index) {
    double distance;
    printf("S1, order %d, rfd %02d:%02d, ", orders[index], 
        rfdmmm[index]/MIN_PER_HOUR, rfdmmm[index]%MIN_PER_HOUR);
    distance = sqrt((delivx[index] * delivx[index])+(delivy[index] * delivy[index]));
    printf("distance %.1lf km\n", distance);    
}

void
do_stage1(int orders[], int rfdmmm[], 
    double delivx[], double delivy[], int n) {
    
    
    printf("S1, %d meals to be delivered\n", n);
    // print the first order
    print_order_rfd(orders, rfdmmm, delivx, delivy,0);
    // print the last order
    print_order_rfd(orders, rfdmmm, delivx, delivy, n-1);
    
}

void
do_stage2(int orders[], int rfdmmm[], double delivx[], double delivy[], int time[], int n) {
    int rts[MAX_DRONES];
    int n_drones=0;
    int i;
    
    for (i = 0; i < n; i++){
        time[i] = flight_time(delivx[i], delivy[i]);

        printf("S2, orders %d, rfd %02d:%02d, dep %02d:%02d, del %02d:%02d, rts %02d:%02d\n",orders[i], 
        rfdmmm[i]/MIN_PER_HOUR, rfdmmm[i]%MIN_PER_HOUR, rfdmmm[i]/MIN_PER_HOUR, 
        rfdmmm[i]%MIN_PER_HOUR, (rfdmmm[i]+time[i])/MIN_PER_HOUR, (rfdmmm[i]+time[i])%MIN_PER_HOUR,
        (((rfdmmm[i]*2)+time[i])+5)/MIN_PER_HOUR, (((rfdmmm[i]*2)+time[i])+5)%MIN_PER_HOUR);
    } 
}

int
flight_time(double delivx,double delivy) {
    int i = 0;
    
    double distance = sqrt((delivx * delivx) + (delivy * delivy));
    int time = ceil(distance/(CNST_SPEED * MIN_PER_HOUR));
    
    return time;
}

//int rfdmmm + time[indx]
