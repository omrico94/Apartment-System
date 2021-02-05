#define _CRT_SECURE_NO_WARNINGS

#include "apt.h"

void add_an_apt(ListApt* lsapt, char* newApt, short int key)
{
	char* token;

	Listnode* lstnode = (Listnode*)calloc(1,sizeof(Listnode));
	AptNode* newapt = (AptNode*)calloc(1, sizeof(AptNode));
	lstnode->apt = newapt;

	newapt->key = key;

	token = strtok(newApt, "\"");
	char* address = (char*)malloc(sizeof(char)*(strlen(token)+1));
	newapt->address = address;
	strcpy(address, token);

	token = strtok(NULL, " ");
	sscanf(token , "%d", &(newapt->price));

	token = strtok(NULL, " ");
	sscanf(token, "%hu", &(newapt->NumRooms));
	
	Date* date = (Date*)calloc(1, sizeof(Date));
	newapt->entryDate = date;

	token = strtok(NULL, " ");
	sscanf(token, "%hu", &(date->Day));

	token = strtok(NULL, " ");
	sscanf(token, "%hu", &(date->Month));

	token = strtok(NULL, "\0");
	sscanf(token, "%d", &(date->Year));
	date->Year += 2000;

	newapt->entryToDB = CurTime();

	insertNewNode(lsapt, lstnode, lstnode->apt->price);
}

void insertNewNode(ListApt *lsapt, Listnode *lstnode, int price)
{
	if (lsapt->head == NULL)
	{
		lsapt->head = lsapt->tail = lstnode;
		lstnode->prev = lstnode->next = NULL;
	}
	else
	{
		Listnode* temp = lsapt->head;

		if (lsapt->head->apt->price > price)
		{
			lstnode->next = lsapt->head;
			lsapt->head = lstnode;
			lstnode->prev = NULL;
			lstnode->next->prev = lstnode;
		}
		else
		{
			while ((temp) && (temp->apt->price <= price))
			{
				temp = temp->next;
			}

			if (!temp)//if the current price is the highest insert it to tail.
			{
				lsapt->tail->next = lstnode;
				lstnode->prev = lsapt->tail;
				lstnode->next = NULL;
				lsapt->tail = lstnode;
			}
			else
			{
				temp->prev->next = lstnode;
				lstnode->prev = temp->prev;
				temp->prev = lstnode;
				lstnode->next = temp;
			}
		}
	}
}

void insertAptToTail(ListApt* lsApt, Listnode* lsnode)
{
	if (!lsApt->head)
	{
		lsApt->head = lsApt->tail = lsnode;
		lsnode->next = lsnode->prev = NULL;
	}
	else
	{
		lsApt->tail->next = lsnode;
		lsnode->prev = lsApt->tail;
		lsApt->tail = lsnode;
		lsnode->next = NULL;
	}
}

void buy_an_apt(ListApt *lstApt, short int key)
{
	Listnode* temp;
	if (lstApt->head->apt->key == key)
	{
		temp = lstApt->head;
		lstApt->head = temp->next;
		
		if (temp->next == NULL)
		{
			lstApt->tail = NULL;
		}
		else
		{
			lstApt->head->prev = NULL;
		}
	}
	else
	{
		temp = lstApt->head->next;
		
		while (temp->apt->key != key)
		{
			temp = temp->next;
		}

		if (temp->next == NULL)
		{
			lstApt->tail = temp->prev;
			lstApt->tail->next = NULL;
		}
		else
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			
		}
	}

	freeListNode(temp);
}



void get_an_apt(char* st, ListApt* lsApt)
{
	st++;
	int minPrice = -1, maxPrice = -1, minRooms = -1, maxRooms = -1, printWay = 1;
	char *token, date[9];
	date[0] = '9';

	if (st[strlen(st) - 1] == 'r')
	{
		printWay = 0;
	}

	token = strtok(st, " ");

	while (token)
	{
		if (!strcmp(token, MINROOMS))
		{
			token = strtok(NULL, " ");
			sscanf(token, "%d", &minRooms);
		}
		else if (!strcmp(token, MAXROOMS))
		{
			token = strtok(NULL, " ");
			sscanf(token, "%d", &maxRooms);
		}
		else if (!strcmp(token, MINPRICE))
		{
			token = strtok(NULL, " ");
			sscanf(token, "%d", &minPrice);
		}
		else if (!strcmp(token, MAXPRICE))
		{
			token = strtok(NULL, " ");
			sscanf(token, "%d", &maxPrice);
		}
		else if (!strcmp(token, DATE))
		{
			token = strtok(NULL, " ");
			sscanf(token, "%s", date);
		}

		token = strtok(NULL, "- ");
	}
	
	get_an_apt_printer(lsApt, minPrice, maxPrice, minRooms, maxRooms, printWay, date);
}

int get_an_apt_Date(AptNode* apt, char* st)
{
	int day, month, year;

	day = (st[0] - '0') * 10 + (st[1] - '0');
	month = (st[2] - '0') * 10 + (st[3] - '0');
	year = (st[4] - '0') * 1000 + (st[5] - '0') * 100 + (st[6] - '0') * 10 + (st[7] - '0');


	if (year > apt->entryDate->Year)
	{
		return 1;
	}
	else if (year == apt->entryDate->Year)
	{
		if (month > apt->entryDate->Month)
		{
			return 1;
		}
		else if (month == apt->entryDate->Month)
		{
			if (day >= apt->entryDate->Day)
			{
				return 1;
			}
		}
	}

	return 0;
}


void get_an_apt_printer(ListApt* lsApt, int minPrice, int maxPrice, int minRooms, int maxRooms, int printWay, char* date)
{
	Listnode* temp;
	int is_good;

	if (printWay)
	{
		temp = lsApt->head;
	}
	else
	{
		temp = lsApt->tail;
	}

	while (temp)
	{
		is_good = apt_checker(temp->apt, minPrice, maxPrice, minRooms, maxRooms, date);

		if (is_good)
		{
			printApt(temp->apt);
		}

		if (printWay)
		{
			temp = temp->next;
		}
		else
		{
			temp = temp->prev;
		}
	}
}

int apt_checker(AptNode* apt, int minPrice, int maxPrice, int minRooms, int maxRooms, char* date)
{
	int is_good = 1;

	if (minPrice != -1)
	{
		if (minPrice > apt->price)
		{
			is_good = 0;
		}
	}

	if (maxPrice != -1)
	{
		if (maxPrice < apt->price)
		{
			is_good = 0;
		}
	}

	if (minRooms != -1)
	{
		if (minRooms > apt->NumRooms)
		{
			is_good = 0;
		}
	}
	if (maxRooms != -1)
	{
		if (maxRooms < apt->NumRooms)
		{
			is_good = 0;
		}
	}
	if (date[0] != '9')
	{
		if (get_an_apt_Date(apt, date) == 0)
		{
			is_good = 0;
		}
	}

	return is_good;
}

void get_an_apt_Enter(ListApt* lsapt, char* str)
{
	str++;
	int num;
	char* token = strtok(str, " ");
	token = strtok(NULL,"\0");
	sscanf(token, "%d", &num);
	Date* currentdate;
	Listnode* temp = lsapt->head;
	currentdate = CurTime();
	setAnewDate(currentdate, num);

	while (temp)
	{
		if (checkDateLater(currentdate, temp->apt->entryToDB))
		{
			printf("%d,", temp->apt->key);
		}

		temp = temp->next;
	}
	printf("\b \n");
}

void delete_an_apt(ListApt *lstApt, int numDays)
{
	Date* currentdate;
	Listnode* tempToFree = lstApt->head;
	Listnode* temp;
	currentdate = CurTime();
	setAnewDate(currentdate, numDays);

	while (tempToFree)
	{
		if (checkDateLater(currentdate, tempToFree->apt->entryToDB))
		{
			if (tempToFree->prev == NULL)
			{
				lstApt->head = tempToFree->next;
				lstApt->head->prev = NULL;
				if (tempToFree->next == NULL)
				{
					lstApt->tail = NULL;
				}
				else
				{
					lstApt->head->prev = NULL;
				}
			}
			else if (tempToFree->next == NULL)
			{
				lstApt->tail = tempToFree->prev;
				tempToFree->prev->next = NULL;
			}
			else
			{
				tempToFree->prev->next = tempToFree->next;
				tempToFree->next->prev = tempToFree->prev;
			}
			temp = tempToFree;
			tempToFree = tempToFree->next;
			freeListNode(temp);
		}
		else
		{
			tempToFree = tempToFree->next;
		}
	}
}

void freeListNode(Listnode* lst)
{
	free(lst->apt->address);
	free(lst->apt->entryDate);
	free(lst->apt->entryToDB);
	free(lst->apt);
	free(lst);
}

