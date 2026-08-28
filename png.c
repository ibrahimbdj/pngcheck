#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "chunk.h"

struct chunk_type typeFnct = {"IHDR", ihdr};
unsigned char PNG[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
int len = 256;

void isPng(FILE* file, unsigned char* buffer){
	int t = fread(buffer, 1, 8, file);
	if(memcmp(PNG, buffer, t) == 0) printf("File type: png\n");
	else {
		printf("Wrond file type: png file required\n");
		exit(1);
	}
}

void info(FILE* file){}

void cat(FILE* file){
	unsigned char* buffer = malloc(len);
	int tmp = fread(buffer, 1, 48, file);
	while(tmp > 0){
		for(int i = 0; i < tmp; i++){
			printf("%02x ", *(buffer+i));
		}
		tmp = fread(buffer, 1, 48, file);
		printf("\n");
	}
	free(buffer);
}

void  list(FILE* file){

    unsigned char* buffer = malloc(len);
	//unsigned char* tmp = buffer;

	isPng(file, buffer);

	printf("\n");
	printf("OFFSET    TYPE    Size    CLASS\n");
	
	long offset;
	long dataLen;
	char* ctype;
	do{
		offset =  ftell(file);
		dataLen = chunkLength(file, buffer);
		ctype = chunkType(file, buffer);

		int lect = printf("%ld", offset);
		for(int i = 0; i < (10-lect);  i++) printf(" ");

		lect = printf("%s", ctype);
		for(int i = 0; i < (8-lect);  i++) printf(" ");

		lect = printf("%ld", dataLen);
		for(int i = 0; i < (8-lect);  i++) printf(" ");

		if(isupper(*ctype) > 0) printf("Critical\n");
		else printf("Anciliary\n");
		fseek(file, (dataLen+4), SEEK_CUR);
	}while(strcmp(ctype, "IEND") != 0);
	printf("\n\n");
	free(buffer);
}
