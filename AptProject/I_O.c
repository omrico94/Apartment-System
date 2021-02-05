#define _CRT_SECURE_NO_WARNINGS

#include "I_O.h"

char* buildStr()
{
	char* st = (char*)malloc(sizeof(char)*1);
	char ch;
	int countP = 1, countL = 0;

	ch = getchar();

	while (ch != '\n')
	{
		if (countL == countP)
		{
			countP *= 2;
			st = (char*)realloc(st, countP);
		}

		st[countL] = ch;
		countL++;

		ch = getchar();
	}

	st = (char*)realloc(st, countL + 1);

	st[countL] = '\0';

	return st;
}

void printListApt(ListApt* lstApt)
{
	Listnode* temp = lstApt->head;
	while (temp)
	{
		printApt(temp->apt);
		temp = temp->next;
	}
}

void printApt(AptNode *apt)
{
	printf("Apt details:\n");
	printf("Code: %d\nAddress: %s\nNumber of rooms: %hu\nPrice: %d\n", apt->key, apt->address, apt->NumRooms, apt->price);
	printf("Entry date: %d.%d.%d\n", apt->entryDate->Day, apt->entryDate->Month, apt->entryDate->Year);
	printf("Database entry date: %d.%d.%d\n", apt->entryToDB->Day, apt->entryToDB->Month, apt->entryToDB->Year);
}

void printArr(char** comArr, ListCom* lsCom)
{
	int siriNum = 1;
	if (lsCom->head != NULL)
	{
		siriNum +=lsCom->tail->siriNum;
	}
	int i;
	for (i = 0; i < 7 && comArr[i]; i++)
	{
		printf("%d. %s\n", siriNum + i, comArr[i]);
	}
}

void printListH(ListCom* lstCom)
{
	ComNode* temp;
	temp = lstCom->head;

	while (temp)
	{
		printf("%d. %s\n", temp->siriNum, temp->com);
		temp = temp->next;
	}
}

long int fileSize(FILE* file)
{
	long int res;

	fseek(file, 0, SEEK_END);
	res = ftell(file);
	fseek(file, 0, SEEK_SET);

	return res;
}