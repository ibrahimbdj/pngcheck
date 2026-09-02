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

		if(isCritical(c)) printf("Critical\n");
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

int delmd(FILE* src, char* destname){
	FILE* dest = fopen(destname, "w+");
	unsigned char* copyBuf = malloc(1024);
	struct chunk* c;
	int gain = 0;
	char* ctype;

	fwrite(PNG, 1, 8, dest);
	fseek(src, 8, SEEK_SET);

	do {
		c = chunkParser(src);
		ctype = c->type;
		if(isCritical(c)){
			long curPos = ftell(src);
			fseek(src, c->dataOffset - 8, SEEK_SET);
			long restant = c->dataLen + 12;
			while(restant > 0){
				if(restant >= 1024){
					fread(copyBuf, 1, 1024, src);
					fwrite(copyBuf, 1, 1024, dest);
					restant = restant - 1024;
				} else{
					fread(copyBuf, 1, restant, src);
					fwrite(copyBuf, 1, restant,  dest);
					restant = 0;
				}
			}
			fseek(src, curPos, SEEK_SET);
		} else gain = 12 + c->dataLen;
		free(c);
	} while(strcmp(ctype, "IEND") != 0);
	fclose(dest);
	printf("%i byte(s) deleted\n", gain);
	return 0;
}

unsigned int inv_uCharToInt(unsigned char* buf){
	return (((unsigned int)*buf << 24) | ((unsigned int)*(buf+1) << 16) | ((unsigned int)*(buf+2) << 8)  | *(buf+3));
}

int info(FILE* file){
	fseek(file, 8, SEEK_CUR);
	struct chunk* c = chunkParser(file);
	fseek(file, c->dataOffset, SEEK_SET);
	unsigned char* width = malloc(4);
	unsigned char* heigth = malloc(4);
	unsigned char bitDepth;
	unsigned char colorType;
	unsigned char compression;
	unsigned char filter;
	unsigned char interlace;

	fread(width, 1, 4, file);
	fread(heigth, 1, 4, file);
	fread(&bitDepth, 1, 1, file);
	fread(&colorType, 1, 1, file);
	fread(&compression, 1, 1, file);
	fread(&filter, 1, 1, file);
	fread(&interlace, 1, 1, file);

	printf("Width: %i\n", inv_uCharToInt(width));
	printf("Heigth: %i\n", inv_uCharToInt(heigth));
	printf("Bit depth: %i\n", bitDepth);

	switch (colorType) {
	case 0:
		printf("Color type: %i, (Greyscale)\n", colorType);
		break;
	case 2:
		printf("Color type: %i, (Truecolor)\n", colorType);
		break;
	case 3:
		printf("Color type: %i, (Indexed-color)\n", colorType);
		break;
	case 4:
		printf("Color type: %i, (Greyscale with alpha)\n", colorType);
		break;
	case 6:
		printf("Color type: %i, (Truecolor with alpha)\n", colorType);
		break;
	default:
		printf("Color type unknown\n");
		break;
	}

	//printf("Compression method: %i\n", compression);
	//printf("Filter: %i\n", filter);
	//printf("Interlace: %i\n", interlace);

	free(width);
	free(heigth);
	free(c);
	return 0;
}