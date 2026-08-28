#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ihdr(FILE* file, unsigned char* buffer, long dataLen);

unsigned char PNG[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
int len = 256;

struct chunk_type { char* type; int (*chunkDataRead)(FILE* file, unsigned char* buffer, long dataLen);};
struct chunk_type typeFnct[2] = {{"IHDR", ihdr}, {NULL, NULL}};

int ihdr(FILE*  file, unsigned char* buffer, long dataLen){
	printf("ihdr\n");
	return 0;
}

void isPng(FILE* file, unsigned char* buffer){
	int t = fread(buffer, 1, 8, file);
	if(memcmp(PNG, buffer, t) == 0) printf("File type: png\n");
	else {
		printf("Wrond file type: png file required\n");
		exit(1);
	}
}

long chunkLength(FILE* file, unsigned char*  buffer){
	fread(buffer, 1, 4, file);
	return ((*buffer << 24) | (*(buffer+1) << 16) | *(buffer+2) << 8  | *(buffer+3));
}

char* chunkType(FILE* file, unsigned char* buffer){

	fread(buffer, 1, 4, file);
	*(buffer+4) = '\0';
	return (char*) buffer;
}

void info(FILE* file){}

void chunkRead(FILE* file, unsigned char* buffer){
	//long dataLen = chunkLength(file, buffer);
	//struct chunk_type* ctype = chunkType(file, buffer);
	//ctype-> chunkDataRead(file, buffer, dataLen);
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

void  list(FILE* file){

        unsigned char* buffer = malloc(len);
	//unsigned char* tmp = buffer;

	isPng(file, buffer);

	printf("\n");
	printf("OFFSET    TYPE    LONGUEUR    CLASSE\n");
	
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
		for(int i = 0; i < (12-lect);  i++) printf(" ");

		printf("a venir\n");
		fseek(file, (dataLen+4), SEEK_CUR);
	}while(strcmp(ctype, "IEND") != 0);
	printf("\n\n");
	free(buffer);
}
