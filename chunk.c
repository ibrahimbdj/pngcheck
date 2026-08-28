#include <stdio.h>
#include <stdlib.h>

int ihdr(FILE* file, unsigned char* buffer, long dataLen);

struct chunk { 
	long dataLen; 
	char* type; 
	long dataOffset; 
	int crc; 
	int (*chunkDataRead)(FILE* file, unsigned char* buffer, long dataLen);
};

long chunkLength(FILE* file, unsigned char*  buffer){
	fread(buffer, 1, 4, file);
	return (((unsigned int)*buffer << 24) | (*(buffer+1) << 16) | (*(buffer+2) << 8)  | *(buffer+3));
}

char* chunkType(FILE* file){
	char* typebuf = malloc(5);
	fread(typebuf, 1, 4, file);
	*(typebuf+4) = '\0';
	return typebuf;
}

long chunkData(FILE* file){
	return ftell(file);
}

int chunkCrc(FILE* file){
	unsigned char* crcbuf = malloc(4);
	fread(crcbuf, 1, 4, file);
	int crc = (((unsigned int)*crcbuf << 24) | (*(crcbuf+1) << 16) | (*(crcbuf+2) << 8)  | *(crcbuf+3));
}

struct chunk* chunkParser(FILE* file, unsigned char* buffer){
	long dataLen = chunkLength(file, buffer);
	char* ctype = chunkType(file);
	long dataOffset = chunkData(file);
	fseek(file, dataLen, SEEK_CUR);
	unsigned char* crc = chunkCrc(file);
	struct chunk* c = malloc(sizeof(c));
	*c = (struct chunk){dataLen, ctype, dataOffset, crc, NULL};
	return &c;
}

int ihdr(FILE*  file, unsigned char* buffer, long dataLen){
	printf("ihdr\n");
	return 0;
}
