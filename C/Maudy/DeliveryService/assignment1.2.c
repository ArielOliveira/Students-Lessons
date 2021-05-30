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

typedef struct _Drone {
    char label;
    int dep;
    int del;
    int rts;
    int DroneUsed;
} Drone;

void discard_lines(int n);
int read_data(int orders[], int rfdmmm[],  double delivx[], double delivy[]);
void print_order_rfd(int orders[], int rfdmmm[], double delivx[],double delivy[], 
                int index); 
void do_stage1(int orders[], int rfdmmm[], double delivx[], 
              double delivy[], int n);
void do_stage2(int orders[], int rfdmmm[], double delivx[], double delivy[], int time[], int n);
void do_stage3(int orders[], int rfdmmm[], double delivx[], double delivy[], int time[], int n);
int deliv_time(double delivx,double delivy);
int hour(int rfdmmm);
int minute(int rfdmmm);


int main(int argc, char* argv[]) {
    int orders[MAX_ORDERS], rfdmmm[MAX_ORDERS];
    double delivx[MAX_ORDERS], delivy[MAX_ORDERS];
    int time[MAX_ORDERS];
    int n;
    
    n = read_data(orders, rfdmmm, delivx, delivy);
    do_stage1(orders, rfdmmm, delivx, delivy, n);
    do_stage2(orders, rfdmmm, delivx, delivy, time, n);
    do_stage3(orders, rfdmmm, delivx, delivy, time, n);
    
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
    printf("\n");
    
}

void
do_stage2(int orders[], int rfdmmm[], double delivx[], double delivy[], int time[], int n) {
    Drone drones[MAX_DRONES];
    int count = 0;
    
    for (int x = 0; x < MAX_DRONES; x++) {
        drones[x].label = x + 'A';
        drones[x].dep = 0;
        drones[x].rts = 0;
        drones[x].DroneUsed = 0;
    }

    Drone* CurrentDrone;

    for (int i = 0; i < n; i++) {
        time[i] = deliv_time(delivx[i], delivy[i]);

        for (int j = 0; j < MAX_DRONES; j++) {
            if (drones[j].rts <= rfdmmm[i]) {
                CurrentDrone = &drones[j];
                if (!drones[j].DroneUsed)
                    count++;
                break;
            }
        }   
        CurrentDrone->dep = rfdmmm[i];
        CurrentDrone->del = (rfdmmm[i]+time[i]);
        CurrentDrone->rts = (rfdmmm[i]+(time[i]*2)+ RECOVERY_TIME);    
        CurrentDrone->DroneUsed = 1;

        printf("S2, order %d, rfd %02d:%02d, drone %c, dep %02d:%02d, del %02d:%02d, rts %02d:%02d\n",
        orders[i], hour(rfdmmm[i]), minute(rfdmmm[i]), CurrentDrone->label, 
        hour(CurrentDrone->dep), minute(CurrentDrone->dep), 
        hour(CurrentDrone->del), minute(CurrentDrone->del),
        hour(CurrentDrone->rts), minute(CurrentDrone->rts));      
    } 
    printf("S2, a total of %d drones are required\n", count); 
}

void
do_stage3(int orders[], int rfdmmm[], double delivx[], double delivy[], int time[], int n) {
    // 1 - rts of time[i] + drone[j].rts - rfdmmm[i] <= 30 -> drone[j] takes the order
    // 2 - if there are more than two drones availabe in less than 30 minutes gets the 
    // lower label
    // 3 - if no drones will reach rts within 30 minutes or less deploy a new one immediately
    // 4 - if the flight time is thirty minutes or more deploy immediately

    // what's n?
    //del max is rfdmmm[i] + time[i] + 30
    Drone drones[MAX_DRONES];
    int count = 0;
    
    for (int x = 0; x < MAX_DRONES; x++) {
        drones[x].label = x + 'A';
        drones[x].dep = 0;
        drones[x].del = 0;
        drones[x].rts = 0;    
        drones[x].DroneUsed = 0;
    }

    Drone* CurrentDrone;

    for (int i = 0; i < n; i++) {
            time[i] = deliv_time(delivx[i], delivy[i]);
            
            //int rts = (rfdmmm[i]+(time[i]*2)+ RECOVERY_TIME); 
            
            // If the flight time is bigger or equal to 30 minutes
            // deploy a drone immediately
            if (time[i] >= 30) {
                for (int j = 0; j < MAX_DRONES-1; j++) {
                    if (drones[j].rts <= rfdmmm[i]) {
                        CurrentDrone = &drones[j];
                        if (!drones[j].DroneUsed)
                            count++;
                        break;
                    }
                }
            } else { // else wait for the next drone to be ready
                for (int j = 0; j < MAX_DRONES-1; j++) {
                    int deliveryDelay = time[i] + (drones[j].rts - rfdmmm[i]);
                    printf("Time for delivery %d \n", deliveryDelay);
                    // if the time for wait is less or = to 30 minutes
                    // wait for this drone to be ready
                    if (deliveryDelay <= 30) {
                        CurrentDrone = &drones[j];
                        if (!drones[j].DroneUsed)
                            count++;
                        break;
                    } 
                }
            }

            // if no drones were available within 30 minutes, deploy immediately
            if (!CurrentDrone) {
                for (int j = 0; j < MAX_DRONES-1; j++) {
                  if (drones[j].rts <= rfdmmm[i]) {
                        CurrentDrone = &drones[j];
                        if (!drones[j].DroneUsed)
                            count++;
                        break;
                    }
                }
            }

        
        if (CurrentDrone->rts <= rfdmmm[i]) { // means it was deployed immediately
            CurrentDrone->dep = rfdmmm[i];
            CurrentDrone->del = (rfdmmm[i]+time[i]);
            CurrentDrone->rts = (rfdmmm[i]+(time[i]*2)+ RECOVERY_TIME);   
        } else if (time[i] + (CurrentDrone->rts - rfdmmm[i])) { // waited for it to return from service
            CurrentDrone->dep = CurrentDrone->rts;
            CurrentDrone->del = CurrentDrone->rts+time[i];
            CurrentDrone->rts = (CurrentDrone->rts+(time[i]*2)+ RECOVERY_TIME);  
        }

        CurrentDrone->DroneUsed = 1;

        printf("S2, order %d, rfd %02d:%02d, drone %c, dep %02d:%02d, del %02d:%02d, rts %02d:%02d\n",
        orders[i], hour(rfdmmm[i]), minute(rfdmmm[i]), CurrentDrone->label, 
        hour(CurrentDrone->dep), minute(CurrentDrone->dep), 
        hour(CurrentDrone->del), minute(CurrentDrone->del),
        hour(CurrentDrone->rts), minute(CurrentDrone->rts));     

        CurrentDrone = NULL;
    } 
    printf("S2, a total of %d drones are required\n", count); 
}

int
deliv_time(double delivx,double delivy) {
    
    double distance = sqrt((delivx * delivx) + (delivy * delivy));
    int time = ceil(distance / CNST_SPEED * MIN_PER_HOUR);
    
    return time;
}

int 
hour (int rfdmmm) {
    return rfdmmm / MIN_PER_HOUR;
}

int 
minute (int rfdmmm) {
    return rfdmmm % MIN_PER_HOUR;
}