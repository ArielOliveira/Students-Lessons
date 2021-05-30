/*
 ============================================================================
 Name        : CWK2Q5.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement an algorithm in C which given a file containing a block of text as
 input, redacts all words from a given set of “redactable” words (also from a
 file), and outputs the result to a file called “result.txt”. For example,
 given the block of text:
    The quick brown fox jumps over the lazy dog

 and the redactable set of words:
    the, jumps, lazy

 the output text in “result.txt” should be
    *** quick brown fox ***** over *** **** dog

 Note that the number of stars in the redacted text is the same as the number
 of letters in the word that has been redacted, and that capitalization is
 ignored. You should not use any of the string libraries to answer this
 question. You should also test your program using the example files
 provided.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

char *debate = "The quick brown fox jumps over the lazy dog";
char *redact = "the, jumps, lazy";

char* getStringFromFile(const char* filename) {
  FILE *fp;
  char buff[255];
  fp = fopen(filename, "r");

  return NULL;
}

void redact_words(const char *text_filename, const char *redact_words_filename){

}


int isChar(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int stringSize(const char* string) {
  int size = 0;
  for (int i = 0; string[i] != '\0'; i++)
    size++;

  return size;
}

// should be able to split the string by a space character
// returns a string containing the word splitted
char* getWord(const char* string, int pos) {
  //printf("getWord() - start\n");
  int i = pos;
  
  while(string[i] != '\0' && !isChar(string[i])) {
    //printf("%c", string[i]);
    i++;
  }

  //printf("\n");
  int count = 0;
  for (; string[i] != '\0'; i++) {
    if (!isChar(string[i]) && i != pos)
      break;
    else 
      count++;
  }

  char* result = (char*)malloc(sizeof(char) * count + 1);

  count = 0;
  for (int j = pos; j < i; j++) {
    //Making sure we are getting only characters
    // The character should be between 'a' and 'z'
    // or 'A' and 'Z'
    if (isChar(string[j])) {
      
      result[count] = string[j];
      //printf("%c", result[count]);
      count++;
    }
  }

  //printf("\n");
 
  result[i] = '\0';

  printf("\n%d %s getWord() - end\n", count, result);
  
  return result;
}

// case insensitive
int stringCompare(const char* string1, const char* string2) {
  int string1Size = stringSize(string1);
  int string2Size = stringSize(string2); 
  
  //printf("%s %s %d %d\n", string1, string2, string1Size, string2Size);

  // if strings have different size return false
  if (string1Size != string2Size)
    return 0;

  char* word1 = (char*)malloc(sizeof(char) * string1Size+1);
  char* word2 = (char*)malloc(sizeof(char) * string2Size+1);

  for (int i = 0; i < string1Size; i++) {
    word1[i] = string1[i];
    word2[i] = string2[i];
  }

  word1[string1Size] = '\0';
  word2[string2Size] = '\0';

  /////////////////////////////////////////////////
  // setting all the strings to lower case
  for (int k = 0; k < string1Size; k++) {
    if (isChar(word1[k]))
      if (word1[k] >= 65 && word1[k] <= 90)
        word1[k] += 32;
  }

  for (int k = 0; k < string2Size; k++) {
    if (isChar(word2[k]))
      if (word2[k] >= 65 && word2[k] <= 90)
        word2[k] += 32;
  }
  ////////////////////////////////////////////////

  // if there is any character that doesn't match,
  // return false
  for (int i = 0; word1[i] != '\0'; i++)
    if (word1[i] != word2[i])
      return 0;

  free(word1);
  free(word2);

  // else return true
  return 1;
}

char *redact_debate(const char* _debate, const char* _redact){
  int size1 = stringSize(_redact);
  int size2 = stringSize(_debate);
  
  printf("%s %d\n", _redact, size1);
  printf("%s %d\n", _debate, size2);
  
  char* newString = (char*)malloc(sizeof(char) * size2+1);
  for (int k = 0; k < size2; k++)
    newString[k] = debate[k];

  newString[size2] = '\0';
  printf("%s %d\n", newString, stringSize(newString));
  
  int i = 0;
  
  char* word1 = NULL;
  char* word2 = NULL;
  // while i is < size of _redact
  for (; i <size1;) {
    word1 = getWord(_redact, i);
    printf("%s from pos %d\n", word1, i);

    //while j is < size of _debate
    for (int j = 0; j < size2;) {
      
      word2 = getWord(_debate, j);

     /* if (stringCompare(word1, word2)) {
        for (int k = j; k < j + stringSize(word2); k++)
          newString[k] = '*';
      } */
      // increment by word size to get the next word in _debate
      j += stringSize(word2) + 1;
      
      free(word2);
      word2 = NULL;
    }

    // increment by word size to get the next word in _redact
    i += stringSize(word1) + 2;
    printf("%d %s\n", stringSize(word1), word1);
    
    free(word1);
    word1 = NULL;
  }

  // putting EOF character at end of the string
  newString[size2] = '\0';
  
  // should return  the string with the redacted words
  return newString;
}

void get_text_as_array(){
  FILE *fp;
   char buff[255];
   fp = fopen("redact.txt", "r");

  int i=0;
   while(i>=0){
    i = fscanf(fp, "%s", buff);
    printf("%s\n",buff);
   }
}

int main(int argc, char *argv[]) {
	const char *input_file = "./debate.txt";
	const char *redact_file = "./redact.txt";
	redact_words(input_file, redact_file);

  char* newString = redact_debate(debate, redact);
  printf("%s", newString);

  char* word = getWord(redact, 4);
  printf("%s %d", word, stringSize(word));

  free(word);
  word = getWord(redact, 4);
  printf("%s %d", word, stringSize(word));
  


	return EXIT_SUCCESS;
}