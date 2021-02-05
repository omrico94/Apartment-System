#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include "apt.h"
#include "com.h"

//This function recieves a string from the user and returns it.
char* buildStr();
//This function  recives an arr of commands and a List of commands and prints the 7 last commands. 
void printArr(char** comArr, ListCom* lsCom);
//This function gets a list of commands and prints it.
void printListH(ListCom* lstCom);
//This function recivies a list of appartments and prints it.
void printListApt(ListApt* lstApt);
//this function gets an aptnode  and prints it.
void printApt(AptNode *apt);
//this function gets a file and returns the size of it.
long int fileSize(FILE* file);