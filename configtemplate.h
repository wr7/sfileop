/* All configurations here are the default */

#define FILE_IO 1
/*
 * 1: C (fopen, fclose, fseek, ftell, fread, fwrite)
 * 2: POSIX (open, lseek, read, write, close)
*/

/*#define IGNORE_OFF_T_SIZE*/ /*removes OFF_T size check; can cause overflow or file offset limit if you're not careful*/
