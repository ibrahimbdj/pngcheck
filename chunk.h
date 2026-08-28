#ifndef CHUNK_H
#define CHUNK_H

struct chunk { 
	long dataLen; 
	char* type; 
	long dataOffset; 
	int crc; 
	int (*chunkDataRead)(FILE* file, unsigned char* buffer, long dataLen);
};
int ihdr(FILE* file, unsigned char* buffer, long dataLen);
struct chunk* chunkParser(FILE* file, unsigned char* buffer);

#endif