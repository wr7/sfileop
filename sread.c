#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "readwritefunctions.h"

#define true 1
#define false 0

int main(int argn, char *args[]){
	int i;

	char *arg1;

	char *arg2;
	int byteposisinhex = false;

	char *arg3;
	int bytelenisinhex = false;

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
						bytelenisinhex = true;
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
		exit(1);
	}
	
	OPENFILEASR(arg1, targetfile);
	
	if(FILENOTOPENED(targetfile)){
		printf("Provided file cannot be opened, exiting\n");
		exit(3);
	}
	
	int byteposnegative = 0;
		
	FILEOFFSETTYPE bytepos;

	int bytelennegative = 0;
	FILEOFFSETTYPE bytelen;

	FILEOFFSETTYPE endoffile;
	
	GETENDOFFILEOFFSETAS(targetfile, endoffile);
	
	if(arg2[0] == '-'){
		byteposnegative = 1;
	}

	if(byteposisinhex){
		sscanf(arg2 + byteposnegative, HEXFILEOFFSETTYPEFORMATSTRING, &bytepos);
	}else {
		sscanf(arg2 + byteposnegative, FILEOFFSETTYPEFORMATSTRING, &bytepos);
	}

	if(arg3[0] == '-'){
		bytelennegative = 1;
	}

	if(bytelenisinhex){
		sscanf(arg3 + bytelennegative, HEXFILEOFFSETTYPEFORMATSTRING, &bytelen);
	}else {
		sscanf(arg3 + bytelennegative, FILEOFFSETTYPEFORMATSTRING, &bytelen );
	}

	if(byteposnegative){
		if(endoffile < bytepos){
			printf("The read position results in a negative value e.e\n");
			exit(1);
		}
		bytepos = endoffile - bytepos; /*if negative, it assumes that the position is relative to the end of the file*/
	}
	if(bytelennegative){
		if(endoffile - bytelen + 1 - bytepos < 1){
			printf("The write length results in a non-positive value e.e\n");
			exit(1);
		}
		bytelen = endoffile - bytelen + 1 - bytepos; /*assumes the negative value is a position relative to the end of the file so it translates it into a byte length (eg. -1 reads to the end of the file*/
	}

	uint8_t *readstring = malloc(bytelen);
	
	READFROMFILE(readstring, bytepos, bytelen, targetfile);
	
	long li;
	uint8_t printstring[2];
	for(li=0; li<bytelen; li++){
		if(readstring[li] <= 0x0f){
			printf("0");
		}

		printf("%x", readstring[li]&0xff);

		if(li != bytelen-1){
			printf(" ");
		}
	}
	
	printf("\n");
	
	free(readstring);
	CLOSEFILE(targetfile);
	
	printf("bytepos: "FILEOFFSETTYPEFORMATSTRING"\n", bytepos);
	
	printf("bytelen: "FILEOFFSETTYPEFORMATSTRING"\n", bytelen);

	
	return 0;
}
