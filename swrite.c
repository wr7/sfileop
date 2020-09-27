#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "readwritefunctions.h"

#define true 1
#define false 0

#define ishexcharacter(x) (((x >= 'a')&&(x <= 'f'))||((x >= 'A')&&(x <= 'F'))||((x >= '0')&&(x <= '9')))
/*ungodly expression that only returns true when given hex characters abcdefABCDEF0123456789*/

int main(int argn, char *args[]){
	#if defined(FILE_IO) && FILE_IO == 2 && !defined(IGNORE_OFF_T_SIZE)
		if(sizeof(off_t) != sizeof(long)){
			printf("off_t isn't the same size as long, plz change lines 83 and 85 of swrite.c to use the proper size or compile with C io\n");
			printf("sizeof(off_t): %lu\n", sizeof(off_t));
			printf("sizeof(long): %lu\n", sizeof(long));
			exit(5);
		}
	#endif

	int i; /*for further use in for statements*/
	
	char *arg1;

	char *arg2;
	int byteposisinhex = false;

	char *arg3;

	int argumentnumber = 1;
	int ishex = false;
	
	for(i=1; i<argn; i++){
		if(strcmp(args[i], "-x") == 0){
			ishex = true;
		}else {
			switch(argumentnumber){
				case 1:
					if(ishex){
						printf("The -x flag doesn't work for the filename e.e\n");
						exit(6);
					}
					arg1 = args[i];
					break;
				case 2:
					if(ishex){
						byteposisinhex = true;
					}
					arg2 = args[i];
					break;
				case 3:
					if(ishex){
						printf("Write data is already in hexadecimal e.e\n");
						exit(6);
					}
					arg3 = args[i];
					break;
				default:
					printf("Invalid number of arguments specified\n");
					exit(2);
					break;
			}
			argumentnumber++;
			ishex = false;
		}
	}
	argumentnumber--;
	
	if(argumentnumber != 3){
		printf("Invalid number of arguments specified, 3 expected, got %d\n", argumentnumber);
	}
	
	OPENFILEASW(arg1, targetfile);
	
	if(FILENOTOPENED(targetfile)){
		printf("Could not open specified file, exiting\n");
		exit(3);
	}
	
	FILEOFFSETTYPE bytepos;
	
	if(byteposisinhex){
		sscanf(arg2, HEXFILEOFFSETTYPEFORMATSTRING, &bytepos);
	}else {
		sscanf(arg2, FILEOFFSETTYPEFORMATSTRING, &bytepos);
	}

	int allocationsize = 0;
	for(i=0; i<strlen(arg3); i++){
		if(ishexcharacter((arg3)[i])){
			allocationsize++;
		}
	}

	if(allocationsize == 0){
		printf("Write data isn't in hex e.e\n");
		exit(3);
	}

	if(allocationsize % 2 != 0){
		printf("The provided write data isn't a whole number of bytes e.e\n");
		exit(4);
	}

	uint8_t *writestring = malloc(allocationsize/2 * sizeof(uint8_t));
	long writestringlength = 0;
	writestring[0] = '\0';
	char twodigithexnumber[3] = {'\0', '\0', '\0'};
	
	for(i=0; i<strlen(arg3); i++){
		#define currentcharacter arg3[i]
		if(ishexcharacter(currentcharacter)){
			twodigithexnumber[strlen(twodigithexnumber)] = currentcharacter;
			if(strlen(twodigithexnumber) == 2){
				sscanf(twodigithexnumber, "%x", &(writestring[writestringlength]));
				writestringlength++;
				twodigithexnumber[0] = '\0';
				twodigithexnumber[1] = '\0';
			}
		}
	}
	
	

	WRITETOFILE(writestring, bytepos, allocationsize/2, targetfile);

	CLOSEFILE(targetfile);
	free(writestring);

	return 0;
}
