/*
 ============================================================================
 Name        : CWK2Q3.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement your own Hash Table in C for storing and searching names, i.e. char arrays. In the event of collisions, you should use linear probing with an interval of 1. The hash function should be the sum of the ASCII values of the string modulo the size of the underlying data structure. Your Hash Table implementation should have the following interface:
	int hash_function(const char *key)
	void resize_map(int new_size)
	void add_to_map(const char *name)
	int remove_from_map(const char *name)
	int search_map(const char *name)
	void print_map()

 ============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** hash_map;  // this is where you should store your names
//int hash_map[10]; //using an array not a pointer
//int *hash_map;
int size = 10;
int elements = 0;//70%full need to resize

/*int hash_function(const char *key) {

}*/
int hash_function(const char* key) {
  int sum = 0;
  
  for (int i = 0; key[i] != '\0'; i++) {
    sum += key[i];
  }

  return sum%size;
}

void resize_map(int new_size) {
  /*char ***/char** new_hash_map = (char**)(malloc(new_size*sizeof(char*)));

  if (hash_map != NULL) {
    memcpy(new_hash_map, hash_map, new_size);
    free(hash_map);
  }

  hash_map = new_hash_map;
  size = new_size;
} 

/*void add_to_map(const char *name) {

}*/

void add_to_map(const char* name) {
  // gets a location in the hash
  // based on the key
  // (the key in this case is our string)
  int loc = hash_function(name);
  int stringSize = 0;
  
  // count the size of the string
  // by checking where is the EOF character
  for (int i = 0; name[i] != '\0'; i++) 
    stringSize++;

  // check to see if this location 
  // has been set already
  if (hash_map[loc] == 0){
    printf("location = %d not set yet\n", loc);

    // if not allocates space to store the string
    // at this location
    hash_map[loc] = (char*)malloc(stringSize+1*sizeof(char));
    

    // assigning the string to the hash map
    for (int i = 0; name[i] != '\0'; i++) {
      hash_map[loc][i] = name[i];
    }
   
    // puts a EOF character at the end of this string
    hash_map[loc][stringSize+1] = '\0';

    // increments the size of elements
    // of the hash
    elements += stringSize;
  } else { // else: there is a string already set at this location
   
  }
}

int remove_from_map(const char *name) {

}

int search_map(const char *name) {

}

void print_map() {
  for (int i = 0; i < size; i++) {
      printf("%s", hash_map[i]);
    
    printf("\n");
  }
}

/*int main(int argc, char *argv[]) {
  char *stringOne = "#Hello world";
  resize_map(1);
  add_to_map(stringOne);
  print_map();

  return 0;
}*/

int main(int argc, char *argv[]) {
	char *stringOne = "#Hello world";
	char *stringTwo = "How are you?";
	char *stringThree = "Be the best you...!!";
	char *stringFour = "Be kind to yourself";
	char *stringFive = "Principles of Programming 2";

	resize_map(6);
	add_to_map(stringOne);
	add_to_map(stringTwo);
	add_to_map(stringOne);
	add_to_map(stringThree);
	add_to_map(stringFour);
	add_to_map(stringFive);
	print_map();
  printf("||||||||||||||||| MAPPED PRINTED |||||||||||||||\n");

	int ret = search_map(stringOne);
	if(ret)
		printf("Found %s!\n", stringOne);

	remove_from_map(stringThree);

	ret = search_map(stringFive);
	if(ret)
		printf("Found %s!\n", stringFive);
	print_map();

	add_to_map(stringThree);
	print_map();

	return EXIT_SUCCESS;
}
