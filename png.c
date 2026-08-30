#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "chunk.h"

unsigned char PNG[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

int isPng(FILE* file){
	long curPos = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char* buffer[8];
	int t = fread(buffer, 1, 8, file);
	fseek(file, curPos, SEEK_SET);
	if(memcmp(PNG, buffer, t) == 0) return 0;
	return 1;
}

void cat(FILE* file){
	unsigned char buffer[1024];
	int tmp = fread(buffer, 1, 48, file);
	while(tmp > 0){
		for(int i = 0; i < tmp; i++){
			printf("%02x ", *(buffer+i));
		}
		tmp = fread(buffer, 1, 48, file);
		printf("\n");
	}
}

void list(FILE* file){

	if(isPng(file) != 0){
		printf("Wrong file type or file corrupted\n");
		return;
	}
	fseek(file, 8, SEEK_SET);
	printf("\n");
	printf("OFFSET    TYPE    Size    CLASS\n");
	struct chunk* c;
	do{

		int lect = printf("%ld", ftell(file));
		for(int i = 0; i < (10-lect); i++) printf(" ");

		c = chunkParser(file);

		lect = printf("%s", c->type);
		for(int i = 0; i < (8-lect); i++) printf(" ");

		lect = printf("%ld", c->dataLen);
		for(int i = 0; i < (8-lect); i++) printf(" ");

		if(isupper((unsigned char)*(c->type)) > 0) printf("Critical\n");
		else printf("Anciliary\n");
	}while(strcmp(c->type, "IEND") != 0);
	printf("\n\n");
}

int integrity(FILE* file){
	if(isPng(file) > 0) return 1; 
	fseek(file, 8, SEEK_CUR);
	struct chunk* c;
	char ctype[5];
	do{
		c = chunkParser(file);
		long curPos = ftell(file);
		if (integrityChunk(c, file) > 0) return 1;
		fseek(file, curPos, SEEK_SET);
		strcpy(ctype, c->type);
		free(c->type);
		free(c);
	}while(strcmp(ctype, "IEND") != 0);
	return 0;
}
