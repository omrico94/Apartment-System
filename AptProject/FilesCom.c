#include "FilesCom.h"
//This function gets an array of commands and a list and load the commands from the file to them.
void loadFromTxtFile(char** short_term_history, ListCom* lsCom)
{
	int counter = 0, i = 0;
	FILE* fCom;
	fCom = fopen("fCom.txt", "r+");

	if (fCom)
	{
		long int fSize = fileSize(fCom);
		loadShortHistory(fCom, fSize, short_term_history);
		if (short_term_history[6])
			loadListHistory(fCom, fSize, lsCom);
		fclose(fCom);
	}
}

void loadShortHistory(FILE* fCom, long int fSize, char** short_term_history)
{
	int i, j;

	for (i = 6; i >= 0 && ftell(fCom) + 1 < fSize; i--)//למה פלוס 1???
	{
		short_term_history[i] = getStrFromTxt(fCom);
	}

	i++;

	if (i != 0)//if there are less then 7 commands.
	{
		for (j = 0; i < 7; j++)
		{
			short_term_history[j] = short_term_history[i];
			short_term_history[i] = NULL;
			i++;
		}
	}
}

void loadListHistory(FILE* fCom, long int fSize, ListCom* lsCom)
{
	char* tempStr;
	ComNode* newCom;
	if (ftell(fCom) + 1 < fSize)//למה פלוס 1
	{
		tempStr = getStrFromTxt(fCom);

		loadListHistory(fCom, fSize, lsCom);

		newCom = createComNode(lsCom, tempStr);
		addToTail(lsCom, newCom);
	}
}

void writeToTxtFile(char** short_term_history, ListCom* lsCom)
{
	FILE* fCom;
	fCom = fopen("fCom.txt", "w");
	writeShortHistory(short_term_history, fCom);
	writeListHistory(lsCom->head, fCom);
	fclose(fCom);
}

void writeShortHistory(char** short_term_history, FILE* fCom)
{
	int i;
	for (i = 6; i >= 0; i--)
	{
		if (short_term_history[i])
		{
			fprintf(fCom, "%s\n", short_term_history[i]);
			free(short_term_history[i]);
		}
	}
}

void writeListHistory(ComNode* com, FILE* fCom)
{
	if (com)
	{
		writeListHistory(com->next, fCom);

		fprintf(fCom, "%s\n", com->com);
		freeNodeCom(com);
	}
}

char* getStrFromTxt(FILE* fCom)
{
	int Psize, Lsize;
	char* newStr;
	char ch;
	Psize = 1;
	Lsize = 0;

	newStr = (char*)malloc(sizeof(char)*Psize);

	fscanf(fCom, "%c", &ch);

	while (ch != '\n')
	{
		if (Lsize == Psize)
		{
			Psize *= 2;
			newStr = (char*)realloc(newStr, sizeof(char)* Psize);
		}

		newStr[Lsize] = ch;
		Lsize++;

		fscanf(fCom, "%c", &ch);
	}

	newStr = (char*)realloc(newStr, sizeof(char)*(Lsize + 1));
	newStr[Lsize] = '\0';

	return newStr;
}



