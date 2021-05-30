
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "course.txt"

struct db_type
{
   char name[fieldLength];
   int age;
   char course1[fieldLength];
   char course2[fieldLength];
   char status[fieldLength];
 };

struct courseInfo
{ 
  char code [20]; // e.g., EECS2030
  char title [fieldLength];
  char  date [20];
  char time_start [20];
  char time_end [20];
  char  location [20]; 
};
 
struct courseInfo courseArr[SIZE]; // global variable  array of struc
struct db_type pArr[SIZE]; // global variable array of struct for students
     
struct db_type *freeIndex = &pArr[0];

char prompt_menu(void);
void init_list(struct db_type * pArr[]); 
void clearDB(struct db_type * pArr[]);
void init_courseArr(void);

void writeDisk(struct db_type * pArr[]); 
void emptyDisk(void); 
void loadDisk(struct db_type * pArr[]); 

void displayCourses(void);
void enterNew(struct db_type * pArr[]);
void displayDB(struct db_type * pArr[]);
void removeRecord (struct db_type * pArr[]);
void swap(struct db_type * pArr[]);
void sort(struct db_type * pArr[]);

int timeConflict(struct courseInfo *firstCourse, struct courseInfo *secoundCourse);
int readInteger(int* number);
int readString(char* string);
void printCourse(struct courseInfo* course);
struct courseInfo* retrieveCourse(char* courseCode);


int main(int argc, char *argv[])
{   
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    init_courseArr();  // load course from diskfile
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
         case 'w': writeDisk(db_pArr);  break;    
         case 'l': loadDisk(db_pArr); break;
         case 's': sort(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
         case 'e': emptyDisk();break;

         case 'v': displayCourses();break;
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
 
   fgets(c3,3,stdin);
   
   if(! strcmp(c3, "y\n"))  
      init_list(pArr);
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    printf("|    %-20s","(L)oad disk");
    printf("%-20s","(W)rite disk");
    printf("(E)mpty disk\t|\n");
  
    printf("|    %-20s", "(V)iew courses");//|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s","(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
   
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) {
      return tolower(*s); // s[0], return the first character of s  
    }
       
    printf("not a valid input!\n");
	 
 }
}

/* display all or specified course */
// transfer if/else statement to a helper function which returns either 1,4 or 8
void displayCourses(){   
  // the provide PE2.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info

  // Hold user choice, either a single char, 4 digit course number or full 8 character course code.
  char userChoice[8];
  int isValid = 0;
  
  do {
    puts("course code (or 'a')? ");
    if (readString(userChoice) == 0) isValid = 1;
    else puts("Wrong input\n");
  } while(!isValid);
  puts("\n");

  // convert string to all lower case
  for (int i = 0; i < strlen(userChoice); i++) {
    userChoice[i] = toupper(userChoice[i]);
  }

  if (strlen(userChoice) == 1 && (userChoice[0] == 'A')) {
    for (int i = 0; i < SIZE; i++)
      printCourse(&courseArr[i]);
  } else {
    struct courseInfo* course = retrieveCourse(userChoice);
    if (course) {
      printCourse(course);
    }
  }
}

/*
void courseFinder(char *courseCode) {
  return;
}
*/

/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){  
	
  // Gets first null index in student struct
  int size = 0; 
  while(pArr[size] != NULL && size < SIZE){
    size++;
  }
  pArr[size] =  (struct db_type *) malloc (sizeof(struct db_type)); 
  // Check if max enroll has been reached, returning if true.
  if (size == SIZE) {
    printf("No Empty Student Slot!");
    return;
  }

  int isValid = 0;
  do {
    printf("name: ");
    if (readString(pArr[size]->name) == 0) isValid = 1;
    else puts("Wrong input");
  } while (!isValid);
  
  isValid = 0;
  do {
     printf("age: ");
    if (readInteger(&pArr[size]->age) == 0) isValid = 1;
    else puts("Wrong input");
  } while (!isValid);

  ///////////////////////////////////////////////////// FIRST COURSE ADD
  int isValidInput = 0;
  struct courseInfo *firstCourse = NULL; // hold location of the first course found
  while (!isValidInput) {
    char userChoice[8]; // Store user inputted string for course they wish to add
    isValid = 0;
    do {
      printf("course-1: ");
      if (readString(userChoice) == 0) isValid = 1;
      else puts("Wrong input");
    } while (!isValid);
    
    // Convert user's input to all uppercase alphabet
    for (int i = 0; i < strlen(userChoice); i++) {
      userChoice[i] = toupper(userChoice[i]);
    }

    firstCourse = retrieveCourse(userChoice);

    if (firstCourse) {
      *pArr[size]->course1 = *firstCourse->code;
      isValidInput = 1; 
    }
  }

  isValidInput = 0;
  while (!isValidInput) {
    char userChoice[8]; // Store user inputted string for course they wish to add
    isValid = 0;
    do {
      printf("course-2: ");
      if (readString(userChoice) == 0) isValid = 1;
      else puts("Wrong input");
    } while (!isValid);
    
   // Convert user's input to all uppercase alphabet
    for (int i = 0; i < strlen(userChoice); i++) {
      userChoice[i] = toupper(userChoice[i]);
    }

    struct courseInfo* secoundCourse = retrieveCourse(userChoice);

    if (secoundCourse) {
       if (timeConflict(firstCourse, secoundCourse) == 0) {
        isValidInput = 1;
        *pArr[size]->course2 = *secoundCourse->code;
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////
int timeConflict(struct courseInfo *firstCourse, struct courseInfo *secoundCourse) {
  // temp
  char timeStr[5];
  timeStr[4] = '\0';

  memcpy(&timeStr[0], &firstCourse->time_start[0], 2);
  memcpy(&timeStr[2], &firstCourse->time_start[3], 2);
  int firstCourseStart = atoi(timeStr);
  printf("TIME START - 1: %d\n", firstCourseStart);

  memcpy(&timeStr[0], &firstCourse->time_end[0], 2);
  memcpy(&timeStr[2], &firstCourse->time_end[3], 2);
  int firstCourseEnd = atoi(timeStr);
  printf("TIME END - 1: %d\n", firstCourseEnd);

  memcpy(&timeStr[0], &secoundCourse->time_start[0], 2);
  memcpy(&timeStr[2], &secoundCourse->time_start[3], 2);
  int secoundCourseStart = atoi(timeStr);
  printf("TIME START - 2: %d\n", secoundCourseStart);

  memcpy(&timeStr[0], &secoundCourse->time_end[0], 2);
  memcpy(&timeStr[2], &secoundCourse->time_end[3], 2);
  int secoundCourseEnd = atoi(timeStr);
  printf("TIME END - 2: %d\n", secoundCourseEnd);

  if (firstCourseStart < secoundCourseEnd) {
    if (firstCourseEnd <  secoundCourseStart) {
      printf("SUCESSFUL\n");
      return 0;
    } 
  } else if (secoundCourseStart < firstCourseEnd) {
    if (secoundCourseEnd < firstCourseStart) {
       printf("SUCESSFUL\n");
       return 0;
    }
  } else {
    printf("CONFLICTING TIMES\n");
    return 1;
  }
  return 1;
}



/* display records */
void displayDB(struct db_type * pArr[]){
  ;
 
}


/* remove an existing item */
void removeRecord (struct db_type * pArr[])	
{
  ;

}

/* swap records */
void swap(struct db_type * pArr[]){
   
	; 
} 

/* load from course.txt, store into (global) array of courses  */
void init_courseArr(void){ 
 
   FILE *fr; //file pointer
   fr = fopen (courseFile, "r");
   char arr[50];  
   int count = 0;
   while ((fgets(arr,100,fr)) != NULL)
   {  
     strncpy(courseArr[count].code,  arr, strlen(arr)-1); // remove \n  
     courseArr[count].code[strlen(arr)-1] = '\0';  //to be safe
	 
     fgets(arr,100,fr);  
     strncpy(courseArr[count].title ,  arr, strlen(arr)-1);
     courseArr[count].title[strlen(arr)-1] = '\0';  //to be safe
     
          
     fgets(arr,100,fr); 
     strncpy(courseArr[count].date,  arr, strlen(arr)-1);
     courseArr[count].date[strlen(arr)-1] = '\0';  //to be safe
	   
     // other ways, remove \n before
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_start,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_end,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].location,  arr); 
	  
     count++;
     fgets(arr,100,fr); // read the empty line
   }

   strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

   fclose(fr);
	 
 }
    
/************************ DISK IO *****************************************************************/

void writeDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;

  if ( (fp=fopen(diskFile,"ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  
  for (i=0; i< SIZE ; i++)
  {
     if ( pArr[i] != NULL)
     {  
       if (fwrite( pArr[i], sizeof(struct db_type), 1, fp) != 1)
       { 
          printf("file write error\n");
       }
     } 
   }
   fclose(fp);

}

void emptyDisk(void){

  FILE *fp;
  
  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;
 
  //else
  if ( (fp = fopen(diskFile,"w")) == NULL)
  {
     printf("no file to open\n");
     return;
  }
  fclose(fp); // open close, will empty the file
}


void loadDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;

  struct db_type * tmp;  
  
  if ( (fp = fopen(diskFile,"r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i=0; i < SIZE ; i++)
  {    
     
     tmp =  (struct db_type *) malloc (sizeof(struct db_type));   
	   
     if (fread( tmp, sizeof(struct db_type), 1, fp) != 1)
     {
       if (feof(fp))
       { fclose(fp); 
         return;
       }
       printf("file read error\n");
     }
     else pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
 

} 


int readInteger(int* number) {
  char line[256];
  int i;
  if (fgets(line, sizeof(line), stdin)) {
    if (1 == sscanf(line, "%d\n", &i)) {
      number = &i;
      return 0;     
    } 
  }
  return -1;
}

int readString(char* string) {
  char line[fieldLength];

  if (fgets(line, sizeof(line), stdin)) {
    sscanf(line, "%s\n", string);
    return 0;
  }
  return -1;
}

void printCourse(struct courseInfo* course) {
  if (strcmp(course->code, "EECS0000") != 0) {
    printf ("%s\t%-40s%-5s %s-%s   %s\n", course->code, course->title, course->date, course->time_start, 
      course->time_end, course->location);
  }
}

struct courseInfo* retrieveCourse(char* courseCode) {
  int length = strlen(courseCode);

  int strive = 0;
  
  if (length == 4) {
    strive = 4;
  } else if (length != 8) {
    return NULL;
  }
  
  for (int i = 0; i < SIZE; i++) {
    if (strncmp(&courseArr[i].code[strive], courseCode, 8-strive) == 0) {
      return &courseArr[i];
    }
  }
  return NULL;
}

 
    /*// Check if the user inputted a 8 character string
    if (userChoice[8] == '\0') {
      for (int i = 0; i < SIZE; i++) { // Itterate through entire courseFile array
        // If the user string and the string of the current course match, add that course to the first course 
        if (strcmp(userChoice, courseArr[i].code) == 0) { 
          
          //pArr[size]->course1 = courseArr[i].code;
          firstCourse = &courseArr[i];
          isValidInput = 1;
        }
      }
    } else if ((strlen(userChoice) == 4)) { // Check if the user inputted a 4 digit course code
      // Convert the 8 character course name from courseInfo into its last 4 char to give the 4 digit code
      for (int i = 0; i < SIZE; i++) {
      char subString[5];
      memcpy( subString, &courseArr[i].code[4], 4);
      subString[4] = '\0';
    
      // If the user string and the string of the current course match, add that course to the first course 
      if (strcmp(subString, userChoice) == 0) {
        //pArr[size]->course1 == courseArr[i].code;
        firstCourse = &courseArr[i];
        isValidInput = 1;
      }
    }
  } else {
    printf("course does not exist, enter again: \n");
   }
  }
/////////////////////////////////////////////////////////////////////// SECOUND COURSE ADD
isValidInput = 0;
getchar();
  while (!isValidInput) {
    char userChoice[8];
    printf("course-2: ");
    fgets(userChoice, 9, stdin);
    
    // Convert user's input to all uppercase alphabet
    for (int i = 0; i < strlen(userChoice); i++) {
      userChoice[i] = toupper(userChoice[i]);
    }

    // Check if the user inputted a 8 character string
    if (userChoice[8] == '\0') {
      for (int i = 0; i < SIZE; i++) { // Itterate through entire courseFile array
        // If the user string and the string of the current course match and there is no time conflict, add that course to the first course 
        if ((strcmp(userChoice, courseArr[i].code) == 0) && timeConflict(firstCourse, &courseArr[i])) {
          //pArr[size]->course2 == courseArr[i].code;
          isValidInput = 1;
        } 
      }
    } else if (userChoice[4] == '\0') { // Check if the user inputted a 4 digit course code
      // Convert the 8 character course name from courseInfo into its last 4 char to give the 4 digit code
      for (int i = 0; i < SIZE; i++) {
      char subString[5];
      memcpy( subString, &courseArr[i].code[4], 4);
      subString[4] = '\0';

      //printf(subString);
      // If the user string and the string of the current course match, add that course to the first course 
      if (strcmp(subString, userChoice) == 0 && timeConflict(firstCourse, &courseArr[i]) == 0) {
        //pArr[i]->course2 == courseArr[i].code;
        isValidInput = 1;
      }
    }
  } 
  } */
