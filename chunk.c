#include <stdio.h>
#include <stdlib.h>

int ihdr(FILE* file, unsigned char* buffer, long dataLen);

struct chunk_type { char* type; int (*chunkDataRead)(FILE* file, unsigned char* buffer, long dataLen);};

long chunkLength(FILE* file, unsigned char*  buffer){
	fread(buffer, 1, 4, file);
	return ((*buffer << 24) | (*(buffer+1) << 16) | *(buffer+2) << 8  | *(buffer+3));
}

char* chunkType(FILE* file, unsigned char* buffer){

	fread(buffer, 1, 4, file);
	*(buffer+4) = '\0';
	return (char*) buffer;
}

void chunkRead(FILE* file, unsigned char* buffer){
	//long dataLen = chunkLength(file, buffer);
	//struct chunk_type* ctype = chunkType(file, buffer);
	//ctype-> chunkDataRead(file, buffer, dataLen);
}

int ihdr(FILE*  file, unsigned char* buffer, long dataLen){
	printf("ihdr\n");
	return 0;
}
