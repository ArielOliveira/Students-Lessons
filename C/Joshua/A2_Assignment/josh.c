/* PLEASE DO NOT MODIFY A SINGLE STATEMENT IN THE TEXT BELOW.
READ THE FOLLOWING CAREFULLY AND FILL IN THE GAPS

I hereby declare that all the work that was required to 
solve the following problem including designing the algorithms
and writing the code below, is solely my own and that I received
no help in creating this solution and I have not discussed my solution 
with anybody. I affirm that I have read and understood
the Senate Policy on Academic honesty at 
https://secretariat-policies.info.yorku.ca/policies/academic-honesty-senate-policy-on/
and I am well aware of the seriousness of the matter and the penalties that I will face as a 
result of committing plagiarism in this assignment.

BY FILLING THE GAPS,YOU ARE SIGNING THE ABOVE STATEMENTS.

Full Name:
Student Number:
Course Section:
eecs user id:
*/

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
  char code[20]; // e.g., EECS2030
  char title[fieldLength];
  char date[20];
  char time_start[20];
  char time_end[20];
  char location[20];
};

struct courseInfo courseArr[SIZE]; // global variable  array of struc
struct db_type pArr[SIZE];         // global variable array of struct for students

char prompt_menu(void);
void init_list(struct db_type *pArr[]);
void clearDB(struct db_type *pArr[]);
void init_courseArr(void);

void writeDisk(struct db_type *pArr[]);
void emptyDisk(void);
void loadDisk(struct db_type *pArr[]);

void displayCourses(void);
void enterNew(struct db_type *pArr[]);
void displayDB(struct db_type *pArr[]);
void removeRecord(struct db_type *pArr[]);
void swap(struct db_type *pArr[]);
void sort(struct db_type *pArr[]);
int timeConflict(int firstCourse, int secoundCourse);

int main(int argc, char *argv[])
{

  struct db_type *db_pArr[SIZE]; // main db storage

  init_list(db_pArr); // set to NULL

  init_courseArr(); // load course from diskfile

  char choice;
  for (;;)
  {
    choice = prompt_menu();
    switch (choice)
    {
    case 'n':
      enterNew(db_pArr);
      break;
    case 'd':
      displayDB(db_pArr);
      break;
    case 'w':
      writeDisk(db_pArr);
      break;
    case 'l':
      loadDisk(db_pArr);
      break;
    case 's':
      sort(db_pArr);
      break;

    case 'c':
      clearDB(db_pArr);
      break;
    case 'e':
      emptyDisk();
      break;

    case 'v':
      displayCourses();
      break;
    case 'p':
      swap(db_pArr);
      break;
    case 'r':
      removeRecord(db_pArr);
      break;

    case 'q':
      exit(1); // terminate the whole program
    }
  }
  return 0;
}

void init_list(struct db_type *pArr[])
{
  int t;
  for (t = 0; t < SIZE; t++)
  {
    pArr[t] = NULL;
  }
}

void clearDB(struct db_type *pArr[])
{
  char c3[3];
  printf("are you sure to clear db? (y) or (n)? ");

  fgets(c3, 3, stdin);

  if (!strcmp(c3, "y\n"))
    init_list(pArr);
}

char prompt_menu(void)
{
  char s[80];
  while (1)
  {
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s", "(N)ew record");
    printf("%-20s", "(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s", "(S)ort database");
    printf("%-20s", "(C)lear database");
    printf("(D)isplay db\t|\n");

    printf("|    %-20s", "(L)oad disk");
    printf("%-20s", "(W)rite disk");
    printf("(E)mpty disk\t|\n");

    printf("|    %-20s", "(V)iew courses"); //|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s", "(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");

    fgets(s, 50, stdin); // \n added

    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s)))
    {
      return tolower(*s); // s[0], return the first character of s
    }

    printf("not a valid input!\n");
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* display all or specified course */
// transfer if/else statement to a helper function which returns either 1,4 or 8
void displayCourses()
{
  // the provide PE2.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info

  // Hold user choice, either a single char, 4 digit course number or full 8 character course code.
  char userChoice[8];
  printf("course code (or 'a')? ");
  scanf("%s", userChoice);
  // convert string to all lower case
  for (int i = 0; i < strlen(userChoice); i++)
  {
    userChoice[i] = toupper(userChoice[i]);
  }

  if (userChoice[8] == '\0')
  {
    // Check courses using full course code
    for (int i = 0; i < SIZE; i++)
    {
      if (strcmp(userChoice, courseArr[i].code) == 0)
      {
        printf("%s\t%-40s%-5s %s-%s   %s\n", courseArr[i].code, courseArr[i].title, courseArr[i].date, courseArr[i].time_start,
               courseArr[i].time_end, courseArr[i].location);
      }

      else if (strcmp(courseArr[i].code, "EECS0000") == 0)
      {
        printf("error! course does not exist");
      }
    }
  }
  else if (strlen(userChoice) == 4)
  {
    // Check courses using 4 digit course number

    for (int i = 0; i < SIZE; i++)
    {
      char subString[5];
      memcpy(subString, &courseArr[i].code[4], 4);
      subString[4] = '\0';

      if (strcmp(subString, userChoice) == 0)
      {
        printf("%s\t%-40s%-5s %s-%s   %s\n", courseArr[i].code, courseArr[i].title, courseArr[i].date, courseArr[i].time_start,
               courseArr[i].time_end, courseArr[i].location);
        return;
      }
      else if (strcmp(courseArr[i].code, "EECS0000") == 0)
      {
        printf("error! course does not exist");
      }
    }
  }
  else if (userChoice[0] == 'a')
  {
    // display all courses
    printf("=================================================================================");
    for (int i = 0; i < SIZE; i++)
    {

      if (strcmp(courseArr[i].code, "EECS0000") == 0)
      {
        printf("=================================================================================");
        return;
      }

      printf("\n");

      printf("%s\t%-40s%-5s %s-%s   %s\n", courseArr[i].code, courseArr[i].title, courseArr[i].date, courseArr[i].time_start,
             courseArr[i].time_end, courseArr[i].location);
    }
  }
  else
  {
    printf("error!");
  }
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int courseFinder(char *courseCode, struct courseInfo *courses)
{

  // Check all courses to see if the selected course is amoung them returning the index of the course if true; -1 otherwise
  for (int i = 0; i < SIZE; i++)
  {
    if (strcmp(courseCode, courseArr[i].code + 4) == 0 || (courseCode, courseArr[i].code) == 0)
    {
      return i;
    }
  }
  return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* input items into the list */
void enterNew(struct db_type *pArr[SIZE])
{

  // Gets first null index in student struct
  int size = 0;
  while (pArr[size] != NULL)
  {
    size++;
  }
  pArr[size] = (struct db_type *)malloc(sizeof(struct db_type));

  // Check if max enroll has been reached, returning if true.
  if (size == SIZE)
  {
    printf("No Empty Student Slot!");
    return;
  }

  // User prompt for name and age
  printf("name: ");
  fgets(pArr[size]->name, fieldLength, stdin);
  pArr[size]->name[strlen(pArr[size]->name) - 1] = '\0';
  printf("age: ");
  scanf(" %d", &pArr[size]->age);
  getchar();

  ///////////////////////////////////////////////////// FIRST COURSE ADD
  int isValidInput = 0;
  // Store user inputted string for course they wish to add
  char userChoice[8];
  printf("course-1: ");
  fgets(userChoice, 20, stdin);
  userChoice[strlen(userChoice) - 1] = '\0';

  int firstCourseIndex;
  while (!isValidInput)
  {
    // Int to store the index of the desired course, holds value of -1 if that course does not exist
    int courseIndex = courseFinder(userChoice, courseArr);
    if (courseIndex != -1)
    {
      //pArr[size]->course1 = courseArr[courseIndex];
      //strcmp(pArr[size]->course1, courseArr[courseIndex].code);
      sprintf(pArr[size]->course1,"%s\t%-40s%-5s %s-%s   %s", courseArr[courseIndex].code, courseArr[courseIndex].title, courseArr[courseIndex].date, 
          courseArr[courseIndex].time_start, courseArr[courseIndex].time_end, courseArr[courseIndex].location);
      isValidInput = 1;
      firstCourseIndex = courseIndex;
    }
    else
    {
      printf("course does not exist, enter again: ");
      fgets(userChoice, 20, stdin);
      userChoice[strlen(userChoice) - 1] = '\0';
    }
  }
    ///////////////////////////////////////////////////// SECOND COURSE ADD
    isValidInput = 0; // flip flag back to false
    struct courseInfo *firstCourse; // hold location of the first course found

    int secoundCourseIndex;
    while (!isValidInput)
    {
      char userChoice[8]; // Store user inputted string for course they wish to add
      printf("course-2: ");
      fgets(userChoice, 20, stdin);
      userChoice[strlen(userChoice) - 1] = '\0';
      while (!isValidInput)
      {
        // Int to store the index of the desired course, holds value of -1 if that course does not exist
        int courseIndex = courseFinder(userChoice, courseArr);
        // Check if a course search was successful, if true add the course to the students course 2 slot; otherwise prompt user to enter a new course.
        if (courseIndex != -1)
        {
          //pArr[size]->course2 = courseArr[courseIndex];
          //strcmp(pArr[size]->course2, courseArr[courseIndex].code);
          sprintf(pArr[size]->course2,"%s\t%-40s%-5s %s-%s   %s", courseArr[courseIndex].code, courseArr[courseIndex].title, courseArr[courseIndex].date, 
          courseArr[courseIndex].time_start, courseArr[courseIndex].time_end, courseArr[courseIndex].location);
          isValidInput = 1;
          secoundCourseIndex = courseIndex;

        }
        else
        {
          printf("course does not exist, enter again: ");
          fgets(userChoice, 20, stdin);
          userChoice[strlen(userChoice) - 1] = '\0';
        }
      }

      // Check if there is a time conflict between the courses
      // If true update the status to contain an error remark; otherwise status is given a success message
      if (timeConflict(firstCourseIndex, secoundCourseIndex)) {
        sprintf(pArr[size]->status, "ATTENTION! time conflict");
        //pArr[size]->status = "ATTENTION! time conflict";
        printf(pArr[size]->status);
        return;
      } else {
        sprintf(pArr[size]->status, "SUCCESSFUL! no time conflict");
        //pArr[size]->status = "SUCCESSFUL! no time conflict";
        printf(pArr[size]->status);
      }
      
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * return false if there is no time conflict and the courses can be added with no issue; true otherwise.
 */
int timeConflict(int firstCourse, int secoundCourse)
// int timeConflict(struct courseInfo *firstCourse, struct courseInfo *secoundCourse)
{
  // Int flag to hold whether there is a conflict in the courses scheduled days
  int isDayConflict = 0;

  // Block to check if there is a day conflict ///////////////////////////////////////////////////////////////////////////////////////

  // Loop through the first course's dates
  for (int i = 0; i < strlen(courseArr[firstCourse].date); i++) {
    // Loop through the second course's dates
    for (int j = 0; strlen(courseArr[secoundCourse].date); j++) {
      if (courseArr[firstCourse].date[i] == courseArr[firstCourse].date[j]) {
        // Set day conflict flag
        isDayConflict = 1; 
        break;
      }
    } 
  }

  // If there is no day conflict return out of the function as there will be no time conflict
  if (!isDayConflict) {
    return 0;
  }

  // Block to check if there is a time conflict
  // temp
  char timeStr[5];
  timeStr[4] = '\0';

  memcpy(&timeStr[0], &courseArr[firstCourse].time_start[0], 2);
  memcpy(&timeStr[2], &courseArr[firstCourse].time_start[3], 2);
  int firstCourseStart = atoi(timeStr);

  memcpy(&timeStr[0], &courseArr[firstCourse].time_end[0], 2);
  memcpy(&timeStr[2], &courseArr[firstCourse].time_end[3], 2);
  int firstCourseEnd = atoi(timeStr);

  memcpy(&timeStr[0], &courseArr[secoundCourse].time_start[0], 2);
  memcpy(&timeStr[2], &courseArr[secoundCourse].time_start[3], 2);
  int secoundCourseStart = atoi(timeStr);

  memcpy(&timeStr[0], &courseArr[secoundCourse].time_end[0], 2);
  memcpy(&timeStr[2], &courseArr[secoundCourse].time_end[3], 2);
  int secoundCourseEnd = atoi(timeStr);

  if ((firstCourseStart < secoundCourseEnd) && (secoundCourseStart < firstCourseEnd))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* display records */
void displayDB(struct db_type *pArr[])
{
  // int to store all registered students in the pArr
  int studentCount = 0;
  printf("===============================\n\n");
  
  // Loop through the entire pArr
  for (int i = 0; i < SIZE; i++) {
    // Check if the position in the array is null, skipping said position if true; otherwise, print out the student info 
    if (pArr[i] == NULL) {
      continue;
    } else {
      printf("name:    %s\n", pArr[i]->name);
      printf("age:     %i\n", pArr[i]->age);
      printf("course1: %s\n", pArr[i]->course1);
      printf("course2: %s\n", pArr[i]->course2);
      printf("remarks: %s\n\n", pArr[i]->status);
      studentCount++;
    }
  }

  printf("========== %i records ==========\n", studentCount);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* remove an existing item */
void removeRecord(struct db_type *pArr[])
{
  // Int to store the index at which the name the user wants to remove is at
  int removalIndex;

  // Block to take in the name the user wishes to remove
  char removeName[fieldLength];
  printf("enter full name to remove: ");
  fgets(removeName, fieldLength, stdin);
  removeName[strlen(removeName) - 1] = '\0';

  // Loop through the entire pArr searching for the name to be removed
  for (int i = 0; i < SIZE; i++) {
    // Check if the name at the current index of pArr matches with the user inputted name 
    // If true set removalIndex to that value and shift all values past that point over one; otherwise print error message
    if (strcmp(pArr[i]->name, removeName) == 0) {
      removalIndex = i;
      // Loop through pArr starting at the index at which we are to remove a student
      for (int j = removalIndex; j < (SIZE - 1); j++) {
        // Check if we reached the last index of the array and manually set it to NULL to prevent going out of bounds; 
        // Otherwise Shift all values from the right of the removal index one left
        if (j == SIZE - 1) {
          pArr[j] = NULL;
        } else {
          pArr[j] = pArr[j + 1];
        }
      }
      printf("record [%s] removed successfully.", removeName);
      return;
    }
  }
  printf("record not found");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* swap records */
void swap(struct db_type *pArr[])
{

  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* load from course.txt, store into (global) array of courses  */
void init_courseArr(void)
{

  FILE *fr; //file pointer
  fr = fopen(courseFile, "r");
  char arr[50];
  int count = 0;
  while ((fgets(arr, 100, fr)) != NULL)
  {
    strncpy(courseArr[count].code, arr, strlen(arr) - 1); // remove \n
    courseArr[count].code[strlen(arr) - 1] = '\0';        //to be safe

    fgets(arr, 100, fr);
    strncpy(courseArr[count].title, arr, strlen(arr) - 1);
    courseArr[count].title[strlen(arr) - 1] = '\0'; //to be safe

    fgets(arr, 100, fr);
    strncpy(courseArr[count].date, arr, strlen(arr) - 1);
    courseArr[count].date[strlen(arr) - 1] = '\0'; //to be safe

    // other ways, remove \n before
    fgets(arr, 100, fr);
    arr[strlen(arr) - 1] = '\0';
    strcpy(courseArr[count].time_start, arr);

    fgets(arr, 100, fr);
    arr[strlen(arr) - 1] = '\0';
    strcpy(courseArr[count].time_end, arr);

    fgets(arr, 100, fr);
    arr[strlen(arr) - 1] = '\0';
    strcpy(courseArr[count].location, arr);

    count++;
    fgets(arr, 100, fr); // read the empty line
  }

  strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

  fclose(fr);
}

/************************ DISK IO *****************************************************************/

void writeDisk(struct db_type *pArr[])
{
  FILE *fp;
  int i;

  if ((fp = fopen(diskFile, "ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  for (i = 0; i < SIZE; i++)
  {
    if (pArr[i] != NULL)
    {
      if (fwrite(pArr[i], sizeof(struct db_type), 1, fp) != 1)
      {
        printf("file write error\n");
      }
    }
  }
  fclose(fp);
}

void emptyDisk(void)
{

  FILE *fp;

  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3, 3, stdin);
  if (strcmp(c3, "y\n"))
    return;

  //else
  if ((fp = fopen(diskFile, "w")) == NULL)
  {
    printf("no file to open\n");
    return;
  }
  fclose(fp); // open close, will empty the file
}

void loadDisk(struct db_type *pArr[])
{
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3, 3, stdin);
  if (strcmp(c3, "y\n"))
    return;

  struct db_type *tmp;

  if ((fp = fopen(diskFile, "r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i = 0; i < SIZE; i++)
  {

    tmp = (struct db_type *)malloc(sizeof(struct db_type));

    if (fread(tmp, sizeof(struct db_type), 1, fp) != 1)
    {
      if (feof(fp))
      {
        fclose(fp);
        return;
      }
      printf("file read error\n");
    }
    else
      pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type *pArr[])
{
}
