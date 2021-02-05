#define _CRT_SECURE_NO_WARNINGS
//Omri Aohen 206199192
//Ron Alon 313534554
//05.06.2018

#include "I_O.h"
#include "Nev.h"
#include "FilesCom.h"
#include "FilesApt.h"

int main()
{
	short int key;
	printf("Please enter one of the following commands: \nadd - an - apt, get - an - apt, buy - an - apt or delete - an - apt \nFor reconstruction commands, please enter : \n!!, !num, history, short_history or !num^str1^str2 \nTo exit, enter exit.\n");
	
	ListApt lsApt;
	lsApt.head = lsApt.tail = NULL;
	
	char* short_term_history[N] = {0};
	ListCom lsCom;
	lsCom.head = lsCom.tail = NULL;
	
	loadFromTxtFile(short_term_history, &lsCom);
	loadFromBinFile(&lsApt, &key);

	getCommands(&lsApt, &lsCom, short_term_history, &key);
	
	writeToTxtFile(short_term_history, &lsCom);
	writeToBinFile(&lsApt);
}

