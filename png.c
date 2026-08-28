#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "chunk.h"

unsigned char PNG[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
int len = 1048;

int isPng(FILE* file){
	unsigned char* buffer = malloc(8);
	int t = fread(buffer, 1, 8, file);
	if(memcmp(PNG, buffer, t) == 0) return 0;
	else return 1;
}

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

void list(FILE* file){
    unsigned char* buffer = malloc(len);

	printf("\n");
	printf("OFFSET    TYPE    Size    CLASS\n");
	struct chunk* c;
	do{

		int lect = printf("%ld", ftell(file));
		for(int i = 0; i < (10-lect); i++) printf(" ");

		c = chunkParser(file, buffer);

		lect = printf("%s", c->type);
		for(int i = 0; i < (8-lect); i++) printf(" ");

		lect = printf("%ld", c->dataLen);
		for(int i = 0; i < (8-lect); i++) printf(" ");

		if(isupper((unsigned char)*(c->type)) > 0) printf("Critical\n");
		else printf("Anciliary\n");
	}while(strcmp(c->type, "IEND") != 0);
	printf("\n\n");
	free(buffer);
}
