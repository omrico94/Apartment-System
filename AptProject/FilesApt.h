#define _CRT_SECURE_NO_WARNINGS
#include "apt.h"

//This function recieves an apartment node and a file.
//The function prints the apartment to the file.
void writeAptToBin(AptNode* temp, FILE* fApt);

//This function recieves an apratment list and prints it to a file.
void writeToBinFile(ListApt* apt);

//This function recieves an apartment list and a key number.
//The function load from a file the list in apartments. 
//The function sets the highest key number of the list.
void loadFromBinFile(ListApt* lsApt, short int* key);

//This function recieves an apartments list and a binary file.
//The function load from the file the list in apartment. 
void loadAptFromBin(ListApt* lsApt, FILE* fBin);

//This function recieves an apartment node and a file.
//The function insert from the file to the apartment the num of rooms and its date.
void loadRoomsAndDateFromBin(AptNode* newapt, FILE* fBin);

//This function recieves an apartment node and a file.
//This function insert form the file to the aparment the entry date to DB.
void loadEntryToDB(AptNode* newapt, FILE* fBin);