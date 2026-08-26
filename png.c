#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ihdr(FILE* file, unsigned char* buffer, size_t dataLen);

unsigned char PNG[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
int len = 128;

struct chunk_type { char* type; int (*chunkDataRead)(FILE* file, unsigned char* buffer, size_t dataLen)};
struct chunk_type typeFnct[2] = {{"IHDR", ihdr}, {NULL, NULL}};

int ihdr(FILE*  file, unsigned char* buffer, size_t dataLen){
	printf("ihdr\n");
	return 0;
}

void isPng(FILE* file, unsigned char* buffer){
	size_t t = fread(buffer, 1, 8, file);
	if(memcmp(PNG, buffer, t) == 0) printf("File type: png\n");
	else printf("Wrond file type: png file required\n");
}

size_t chunkLength(FILE* file, unsigned char*  buffer){
	fread(buffer, 1, 4, file);
	return ((*buffer << 24) | (*(buffer+1) << 16) | *(buffer+2) << 8  | *(buffer+3));
}

struct chunk_type* chunkType(FILE* file, unsigned char* buffer){

	int tmp = fread(buffer, 1, 4, file);
	*(buffer+4) = '\0';
	for(struct chunk_type* ct = typeFnct; ct->type != NULL; ct++){
		if(strcmp(ct->type, (const char*)buffer) == 0) return ct;
	}
	printf("Chunk type unknown");
	exit(1);
}

void chunkRead(FILE* file, unsigned char* buffer){
	size_t dataLen = chunkLength(file, buffer);
	struct chunk_type* ctype = chunkType(file, buffer);
	ctype-> chunkDataRead(file, buffer, dataLen);
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
}

void  info(FILE* file){

        unsigned char* buffer = malloc(len);

	isPng(file, buffer);
	chunkRead(file, buffer);

        free(buffer);
}
