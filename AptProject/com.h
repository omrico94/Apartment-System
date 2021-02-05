#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "I_O.h"

#define N 7
#ifndef com_h
#define com_h

typedef struct comNode
{
	char *com;
	int siriNum;
	struct comNode* next;
}ComNode;

typedef struct listCom
{
	ComNode* head;
	ComNode* tail;

}ListCom;

//This function gets a list and arraty of commands and a command and inserts the new command to the stock.
void addToStock(ListCom* lstCom, char** arrCom, char* com);

//This function gets a list of commands and new command and adds this command to the list.
ComNode* createComNode(ListCom* lstCom, char* st);

void freeNodeCom(ComNode* com);
//This function gets a list of commands and a command Node and insert the new node to the tail of the list.

void addToTail(ListCom* lstCom, ComNode* newCom);
//This function recieves an array of commands and inserts to it the new command

void reverseArr(char** arrCom, char* cpycom);
//his function gets a list and arr of commands and a number of command and returns the command in the right place.

char* findCom(ListCom* lstCom, char** arrCom, int numCom);
//This functions recieves a command and returns 1 if it all numbers and 0 else.

int is_AllDigits(char* str);
//This function gets an array of command and returns the last command.

char* findLastCom(char** arrCom);
//This function recieves a command, a list and array of commandns and changes a command from the list by the command that it recieves. 

char* replaceCom(char* com, ListCom* lsCom, char** arrCom);

//This function recieves a command and two strings one to delete from the command and one to put.
char** changeStr(char* newCom, char* strTochange, char* strToPut);

#endif /* com_h */
