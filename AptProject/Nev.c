#define _CRT_SECURE_NO_WARNINGS

#include "Nev.h"

void getCommands(ListApt* lsapt, ListCom* lscom, char** arrcom, short int *key)
{
	char* com;
	com = buildStr();
	while (strcmp(com, "exit"))
	{
		if (com[0] != '!' && com[0] != 's' && com[0] != 'h')
		{
			if (com[0] == 'a')
			{
				(*key)++;
			}
			addToStock(lscom, arrcom, com);
			chooseCommand(com, lsapt, *key);
		}
		else
		{
			chooseReDo(lsapt, lscom, arrcom, com, key);
		}
		free(com);
		com = buildStr();
	}

	printf("Good bye...!\n");

}


void chooseReDo(ListApt* lsApt, ListCom* lsCom, char** arrCom, char* com, short int* key)
{
	int i = 0, numCom;
	char* newCom;
	if (com[0] == 's')
	{
		printArr(arrCom, lsCom);
	}
	else if (com[0] == 'h')
	{
		printListH(lsCom);
		printArr(arrCom, lsCom);
	}
	else
	{
		if (com[1] == '!')
		{
			newCom = findLastCom(arrCom);
		}
		else
		{
			if (!is_AllDigits(com))
			{
				newCom = replaceCom(com, lsCom, arrCom);
			}
			else
			{
				sscanf(com + 1, "%d", &numCom);
				newCom = findCom(lsCom, arrCom, numCom);
			}
		}

		if (newCom[0] == 'a')
		{
			(*key)++;
		}

		addToStock(lsCom, arrCom, newCom);
		chooseCommand(newCom, lsApt, *key);
		free(newCom);
	}

}


void chooseCommand(char* com, ListApt *lsApt, short int key)
{
	int keyToBuy, days;
	char* token;
	char ch = com[0];

	switch (ch){
	case 'a':
	{
		token = strtok(com, "\"");
		token = strtok(NULL, "\0");
		add_an_apt(lsApt, token, key);
		break;
	}
	case 'g':
	{
		token = strtok(com, " ");
		token = strtok(NULL, "\0");

		if (token[1] == 'E')
		{
			get_an_apt_Enter(lsApt, token);
		}
		else
		{
			get_an_apt(token, lsApt);
		}
		break;
	}
	case 'b':
	{
		token = strtok(com, " ");
		token = strtok(NULL, "\0");
		sscanf(token, "%d", &keyToBuy);
		buy_an_apt(lsApt, keyToBuy);
		break;
	}
	case 'd':
	{
		token = strtok(com, " ");
		token = strtok(NULL, " ");
		token = strtok(NULL, "\0");
		sscanf(token, "%d", &days);
		delete_an_apt(lsApt, days);
		break;
	}
	}
}











