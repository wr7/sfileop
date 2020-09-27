#include "config.h"
#include "readwritefunctions.h"
#if FILE_IO == 1
	#warning "C IO doesn't support schangelen"
	#include <stdio.h>
	int main(){
		printf("C IO doesn't support schangelen\n");
		return(1);
	}
#else
	int main(int argn, char (*args)[]){
		if(argn != 3){
			printf("Invalid number of arguments, 2 expected, got %d\n", argn-1);
			exit(1);
		}
		
		if(((args[2])[0] != '=') && ((args[2])[0] != '+') && ((args[2])[0] != '-')){
			printf("Invalid starting character, '=', '+' or '-' expected, got %c\n", (args[2])[0]);
			exit(2);
		}

		if()	
		
		OPENFILEASW(args[1], targetfile);
		
		if(FILENOTOPENED(targetfile)){
			printf("Cannot open file\n");
			exit(3);
		}
		
		FILEOFFSETTYPE filelength;
		long filelengthchange;
		
		GETENDOFFILEOFFSETAS(targetfile, filelength);
		
		

		return(0);
	}
#endif
