#ifndef CHUNK_H
#define CHUNK_H

#include <stdio.h>
#include <stdlib.h>

struct chunk { 
	long dataLen; 
	char* type; 
	long dataOffset; 
	int crc; 
	int (*chunkDataRead)(FILE* file, unsigned char* buffer, long dataLen);
};
int ihdr(FILE* file, unsigned char* buffer, long dataLen);
struct chunk* chunkParser(FILE* file);
int integrityChunk(struct chunk* c, FILE* file);

#endif