#if !defined(READWRITEFUNCTIONS_H)
#define READWRITEFUNCTIONS_H

#ifndef FILE_IO
	#define FILE_IO 2
#endif

#if FILE_IO == 2
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	
	#define FILEOFFSETTYPEFORMATSTRING "%zu"
	#define HEXFILEOFFSETTYPEFORMATSTRING "%zx"
	
	#define FILEOFFSETTYPE off_t
	
	#define OPENFILEASR(filename, variablename) \
		int variablename = open(filename, O_RDONLY)
	
	#define OPENFILEASW(filename, variablename) \
		int variablename = open(filename, O_RDWR)
	
	#define CLOSEFILE(variablename) \
		close(variablename)
	
	#define GETENDOFFILEOFFSETAS(filevariable, outputvariable) \
		outputvariable = lseek(filevariable, 0, SEEK_END)
	
	#define FILEOPENED(filevariable) (filevariable != -1)
	
	#define FILENOTOPENED(filevariable) (filevariable == -1)
	
	#define READFROMFILE(buffer, offset, length, file) \
		lseek(file, offset, SEEK_SET); \
		read(file, buffer, length)
	
	#define WRITETOFILE(data, offset, length, file) \
		lseek(file, offset, SEEK_SET); \
		write(file, data, length)
	#define TRUNCATEFILE(file, length) \
		ftruncate(file, length)

#else
	#include <stdio.h>
	
	#define FILEOFFSETTYPEFORMATSTRING "%lu"
	#define HEXFILEOFFSETTYPEFORMATSTRING "%lx"
	
	#define FILEOFFSETTYPE long
	
	#define OPENFILEASR(filename, variablename) \
		FILE *variablename = fopen(filename, "rb")

	#define OPENFILEASW(filename, variablename) \
		FILE *variablename = fopen(filename, "r+b")

	#define CLOSEFILE(filevariable) \
		fclose(filevariable)

	#define GETENDOFFILEOFFSETAS(filevariable, outputvariable) \
		fseek(filevariable, 0, SEEK_END); \
		outputvariable = ftell(filevariable)

	#define FILEOPENED(fp) (fp != NULL)
	#define FILENOTOPENED(fp) (fp == NULL)

	#define READFROMFILE(buffer, offset, length, file) \
		fseek(file, offset, SEEK_SET); \
		fread(buffer, 1, length, file)

	#define WRITETOFILE(data, offset, length, file) \
		fseek(file, offset, SEEK_SET); \
		fwrite(data, 1, length, file)
#endif
#endif
