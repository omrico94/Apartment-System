#define _CRT_SECURE_NO_WARNINGS

#include "apt.h"
#include "com.h"

//This function recieves a list of apartments, a list of commands and an array of commands.
//The function recieves from the user commands and execute them until the command is exit.
void getCommands(ListApt *lsApt, ListCom *lsCom, char **arrCom, short int *key);


//This function recieves a list of apartments, a list of commands, array of commands, an history command and a key number.
//The function realise which command is it and execute it.
void chooseReDo(ListApt* lsApt, ListCom* lsCom, char** arrCom, char* com, short int* key);

//This function recieves a new command, a list of apartments and a number key.
//The function realise which command is it and execute it.
void chooseCommand(char* com, ListApt *lsApt, short int key);
