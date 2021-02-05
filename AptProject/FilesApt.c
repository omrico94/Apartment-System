#include "FilesApt.h"

void loadFromBinFile(ListApt* lsApt, short int* key)
{
	FILE* fBin = fopen("fApt.bin", "rb");
	*key = 0;

	if (fBin)
	{
		long int fsize = fileSize(fBin);

		while (ftell(fBin) < fsize)
		{
			loadAptFromBin(lsApt, fBin);
			if (lsApt->tail->apt->key > *key)
				*key = lsApt->tail->apt->key;
		}

		fclose(fBin);
	}
}


void loadAptFromBin(ListApt* lsApt, FILE* fBin)
{
	Listnode* aptNode = (Listnode*)malloc(sizeof(Listnode));
	AptNode* newapt = (AptNode*)malloc(sizeof(AptNode));
	short int lenght;
	fread(&newapt->key, sizeof(short int), 1, fBin);

	fread(&lenght, sizeof(short int), 1, fBin);
	newapt->address = (char*)malloc(sizeof(char)*(lenght + 1));
	fread(newapt->address, sizeof(char), lenght, fBin);
	newapt->address[lenght] = '\0';

	fread(&newapt->price, sizeof(int), 1, fBin);

	loadRoomsAndDateFromBin(newapt, fBin);

	loadEntryToDB(newapt, fBin);

	aptNode->apt = newapt;
	insertAptToTail(lsApt, aptNode);
}

void loadRoomsAndDateFromBin(AptNode* newapt, FILE* fBin)
{
	unsigned char mask;

	Date* entryDate = (Date*)malloc(sizeof(Date));
	unsigned char ch[3];

	fread(ch, sizeof(unsigned char), 3, fBin);

	newapt->NumRooms = ch[0] >> 4;

	mask = 0x1E;
	entryDate->Day = (ch[0] << 1) & mask;
	entryDate->Day |= (ch[1] >> 7);

	mask = 0x0F;
	entryDate->Month = (ch[1] >> 3) & mask;

	mask = 0x38;
	entryDate->Year = (ch[1] << 4) & mask;
	entryDate->Year |= ch[2] >> 4;
	entryDate->Year += 2000;

	newapt->entryDate = entryDate;
}

void loadEntryToDB(AptNode* newapt, FILE* fBin)
{
	unsigned short int mask;
	Date* entryToDB = (Date*)malloc(sizeof(Date));

	unsigned short int dateDB;
	fread(&dateDB, sizeof(unsigned short int), 1, fBin);

	entryToDB->Day = dateDB >> 11;

	mask = 0xf;
	entryToDB->Month = (dateDB >> 7) & mask;

	mask = 0x7f;
	entryToDB->Year = dateDB & mask;
	entryToDB->Year += 2000;

	newapt->entryToDB = entryToDB;
}

void writeToBinFile(ListApt* apt)
{
	FILE* fApt = fopen("fApt.bin", "wb");

	Listnode* temp = apt->head;

	while (temp)
	{
		writeAptToBin(temp->apt, fApt);
		temp = temp->next;
		if (temp)
			freeListNode(temp->prev);
	}
	if (apt->tail)
		freeListNode(apt->tail);
	fclose(fApt);
}

void writeAptToBin(AptNode* temp, FILE* fApt)
{
	unsigned short int date;
	short int tempYear, tempYear2;
	int size = strlen(temp->address);

	fwrite(&(temp->key), sizeof(short int), 1, fApt);

	fwrite(&size, sizeof(short int), 1, fApt);
	fwrite(temp->address, sizeof(char), strlen(temp->address), fApt);

	fwrite(&temp->price, sizeof(int), 1, fApt);

	unsigned char* ch = (char*)calloc(3, sizeof(char));

	ch[0] = ch[0] | temp->NumRooms << 4;

	ch[0] = ch[0] | temp->entryDate->Day >> 1;
	ch[1] = ch[1] | temp->entryDate->Day << 7;

	ch[1] = ch[1] | temp->entryDate->Month << 3;

	tempYear = temp->entryDate->Year - 2000;
	ch[1] = ch[1] | tempYear >> 4;
	ch[2] = ch[2] | tempYear << 4;

	fwrite(ch, sizeof(char), 3, fApt);

	date = (temp->entryToDB->Day << 11);
	date = date | temp->entryToDB->Month << 7;

	tempYear2 = temp->entryToDB->Year - 2000;
	date = date | tempYear2;

	fwrite(&date, sizeof(short int), 1, fApt);
}