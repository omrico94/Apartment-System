#define _CRT_SECURE_NO_WARNINGS
#include "com.h"

//This function gets a text file and builds a string from the current line.
char* getStrFromTxt(FILE* fCom);

//This function gets an array of commands and a list and load the commands from the file to them.
void loadFromTxtFile(char** short_term_history, ListCom* lsCom);

//This function gets a File and it size, and an array of command and load the command from the file to the array.
void loadShortHistory(FILE* fCom, long int fSize, char** short_term_history);

//This function gets a File and it size, and a list of command and load the command from the file to the list.
void loadListHistory(FILE* fCom, long int fSize, ListCom* lsCom);

//This function gets a list and array of commands and writes the command from them to a text file. 
void writeToTxtFile(char** short_term_history, ListCom* lsCom);

//this function gets an array of commands and a file prints the commands to the file.
void writeShortHistory(char** short_term_history, FILE* fCom);

//This function gets a comNode and a text file and prints the command from the node to the file.
void writeListHistory(ComNode* com, FILE* fCom);
