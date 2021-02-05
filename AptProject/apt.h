#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Date.h"
#include "I_O.h"

#ifndef apt_h
#define apt_h

typedef struct aptNode
{
	short int key;
	char  *address;
	int price;
	short int NumRooms;
	Date *entryDate;
	Date *entryToDB;
}AptNode;

typedef struct listnode
{
	struct listnode *next;
	struct listnode *prev;
	AptNode *apt;

}Listnode;

typedef struct listApt
{
	Listnode *head;
	Listnode *tail;
}ListApt;

#define MAXROOMS "MaximumNumRooms"
#define MINROOMS "MinimumNumRooms"
#define MAXPRICE "MaximumPrice"
#define _CRT_SECURE_NO_WARNINGS

#define MINPRICE "MinimumPrice"

//This function recieves a get command and a list of apartments.
//The function seperates the command into temrs, and prints all the apartments in the list that follow the terms.
void get_an_apt(char* st, ListApt* lsApt);

//This function recieves a list of apartments, and terms.
//The function prints all the apartments that follows the terms.
void get_an_apt_printer(ListApt* lsApt, int minPrice, int maxPrice, int minRooms, int maxRooms, int printWay, char* date);

//This function recieves an apartment and terms.
//The function returns 1 if the apartment follows the terms and 0 if not.
int apt_checker(AptNode* apt, int minPrice, int maxPrice, int minRooms, int maxRooms, char* date);

//This function recieves an apartment and a string of date.
//The function returns 1 if the apartment's entry date is before the above date.
int get_an_apt_Date(AptNode* apt, char* st);

//This function recieves a list of apartments and a command with a number.
//The function prints all the apartments that was entered into the DB num of days that has gotten in the str before today.
void get_an_apt_Enter(ListApt* lsapt,char* str);

//This function recieves a list of apartments a string of a new apartment and a key number.
//The function creates a new node of apartment and adds it to the list by order of price. 
void add_an_apt(ListApt* lsapt, char* newApt, short int key);

//This function recieves a list of apartments and a key number.
//The function delets the apartment that has the same key number.
void buy_an_apt(ListApt *lstApt, short int key);

//This function recieves a list of apartments and number of days.
//This function deletes all the apartments that entered to the DB "numdays" before today.
void delete_an_apt(ListApt *lstApt, int numDays);

//This function recieves a list node and free it.
void freeListNode(Listnode* lst);

//This function recieves a list of apartments, a new node of apartment and the apartment's price.
//The function insert the node to the right place in the list.
void insertNewNode(ListApt *lsapt, Listnode *lstnode, int price);

//This function recieves a list of apartments and a node of a new apartment.
//The function inserts the new node to the end of the list.
void insertAptToTail(ListApt* lsApt, Listnode* lsnode);

#endif /* apt_h */
