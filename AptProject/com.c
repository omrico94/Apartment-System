#define _CRT_SECURE_NO_WARNINGS

#include "com.h"

void addToStock(ListCom* lstCom, char** arrCom, char* com)
{
	ComNode* newCom;
	char *cpycom = (char*)malloc(sizeof(char)*(strlen(com) + 1));
	strcpy(cpycom, com);

	int i = 0;

	if (arrCom[N-1] == NULL)
	{
		while (arrCom[i])
		{
			i++;
		}
		arrCom[i] = cpycom;
	}
	else
	{
		newCom = createComNode(lstCom, arrCom[0]);
		addToTail(lstCom, newCom);
		reverseArr(arrCom, cpycom);
	}
}

ComNode* createComNode(ListCom* lstCom, char* st)
{
	ComNode* newCom = (ComNode*)malloc(sizeof(ComNode));
	newCom->com = st;
	newCom->next = NULL;

	if (lstCom->head == NULL)
	{
		newCom->siriNum = 1;
	}
	else
	{
		newCom->siriNum = lstCom->tail->siriNum + 1;
	}

	return newCom;
}

void addToTail(ListCom* lstCom, ComNode* newCom)
{
	if (lstCom->head == NULL)
	{
		lstCom->head = lstCom->tail = newCom;
	}
	else
	{
		lstCom->tail->next = newCom;
		lstCom->tail = newCom;
	}
}
void reverseArr(char** arrCom, char* cpycom)
{
	int i;
	for (i = 0; i < N-1; i++)
	{
		arrCom[i] = arrCom[i + 1];
	}
	arrCom[i] = cpycom;
}

char* findCom(ListCom* lstCom, char** arrCom, int numCom)
{
	int i;
	ComNode* temp;
	char* comToDo;
	if (lstCom->head == NULL)
	{
		comToDo = (char*)malloc(sizeof(char)*(strlen(arrCom[numCom - 1]) + 1));
		strcpy(comToDo, arrCom[numCom - 1]);
	}
	else if(lstCom->tail->siriNum < numCom)
	{
		numCom = numCom - lstCom->tail->siriNum;
		comToDo = (char*)malloc(sizeof(char)*(strlen(arrCom[numCom - 1]) + 1));
		strcpy(comToDo, arrCom[numCom - 1]);
	}
	else
	{
		temp = lstCom->head;
		for (i = 0; i < numCom - 1; i++)
		{
			temp = temp->next;
		}
		comToDo = (char*)malloc(sizeof(char)*(strlen(temp->com) + 1));
		strcpy(comToDo, temp->com);
	}
	return comToDo;
}

int is_AllDigits(char* str)
{
	char* checkerStr;
	checkerStr = (char*)malloc(sizeof(char)*(strlen(str) + 1));
	strcpy(checkerStr, str);

	checkerStr = strstr(checkerStr, "^");

	if (checkerStr)
	{
		return 0;
	}
	else
	{
		return 1;
	}

	free(checkerStr);
}

char* findLastCom(char** arrCom)
{
	char* comToDo;
	int i = 0;
	if (arrCom[N-1] == NULL) // if the last is empty find last com and insert to arrCom.
	{
		while (arrCom[i])
		{
			i++;
		}
	}
	else
	{
		i = N;
	}
	
	comToDo = (char*)malloc(sizeof(char)*(strlen(arrCom[i - 1]) + 1));
	strcpy(comToDo, arrCom[i - 1]);
	return comToDo;
}

char* replaceCom(char* com, ListCom* lsCom, char** arrCom)
{
	char* token, *newCom, *strTochange, *strToPut;
	int numCom;
	token = strtok(com + 1, "^");
	sscanf(token, "%d", &numCom);
	newCom = findCom(lsCom, arrCom, numCom);

	token = strtok(NULL, "^");
	strTochange = (char*)malloc(sizeof(char)*(strlen(token) + 1));
	strcpy(strTochange, token);
	token = strtok(NULL, "\0");
	strToPut = (char*)malloc(sizeof(char)*(strlen(token) + 1));
	strcpy(strToPut, token);

	newCom = changeStr(newCom, strTochange, strToPut);

	free(strTochange);
	free(strToPut);

	return newCom;
}

char** changeStr(char* newCom, char* strTochange, char* strToPut)
{
	int num;
	char* afterStr, *cpyafterStr;

	afterStr = strstr(newCom, strTochange);

	while (afterStr)
	{
		cpyafterStr = (char*)malloc(sizeof(char)*(strlen(afterStr) + 1));
		strcpy(cpyafterStr, afterStr);
		num = strlen(newCom) - strlen(afterStr);
		newCom[num] = '\0';

		newCom = (char*)realloc(newCom, sizeof(char)*(num + strlen(strToPut) + 1));
		strcat(newCom, strToPut);

		cpyafterStr = cpyafterStr + strlen(strTochange);

		newCom = (char*)realloc(newCom, sizeof(char)*(num + strlen(strToPut) + strlen(cpyafterStr)) + 1);
		strcat(newCom, cpyafterStr);

		free(cpyafterStr - strlen(strTochange));

		afterStr = strstr(newCom + num + strlen(strToPut), strTochange);
	}

	return newCom;
}

void freeNodeCom(ComNode* com)
{
	free(com->com);
	free(com);
}