#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ihdr(FILE* file, unsigned char* buffer, long dataLen);

struct chunk { 
	long dataLen; 
	char* type; 
	long dataOffset; 
	unsigned int crc; 
	int (*chunkDataRead)(FILE* file, unsigned char* buffer, long dataLen);
};

long chunkLength(FILE* file){
	unsigned char buffer[4];
	fread(buffer, 1, 4, file);
	return (((unsigned int)*buffer << 24) | ((unsigned int)*(buffer+1) << 16) | ((unsigned int)*(buffer+2) << 8)  | *(buffer+3));
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

unsigned int chunkCrc(FILE* file){
	unsigned char buf[4];
	fread(buf, 1, 4, file);
	return (((unsigned int)*(buf+3) << 24) | ((unsigned int)*(buf+2) << 16) | ((unsigned int)*(buf+1) << 8)  | *buf);
}

struct chunk* chunkParser(FILE* file){
	long dataLen = chunkLength(file);
	char* ctype = chunkType(file);
	long dataOffset = chunkData(file);
	fseek(file, dataLen, SEEK_CUR);
	unsigned int crc = chunkCrc(file);
	struct chunk* c = malloc(sizeof(struct chunk));
	*c = (struct chunk){dataLen, ctype, dataOffset, crc, NULL};
	return c;
}

int isCritical(struct chunk* c){
	if(isupper((unsigned char)*(c->type))) return 1;
	else return 0;
}

unsigned int inverseByte(unsigned int x){
	unsigned int r = 0;
	for(int i = 0; i < 32; i++){
		r = (r << 1) | (x & 1);
		x >>= 1;
	}
	return r;
}

unsigned int integrityChunk(struct chunk* c, FILE* file){
	unsigned int resultat = 0;
	unsigned int polynome = 0x04C11DB7;
	long restant = 4 + c->dataLen;
	unsigned char loadedByte;
	fseek(file, ((c->dataOffset)-4), SEEK_SET);
	for(long i = 0; i < restant; i++){
		fread(&loadedByte, 1, 1, file);
		if(i < 4) loadedByte ^= 0xFF;
		for (int j = 0; j < 8; j++) {
			unsigned int divisible = resultat & 0x80000000;
			resultat = (resultat << 1) | (loadedByte & 1);
			loadedByte = loadedByte >> 1;
			if(divisible) resultat = resultat ^ polynome;
		}
	}
	restant = 4;
	for(long i = 0; i < restant; i++){
		loadedByte = 0;
		for (int j = 0; j < 8; j++) {
			unsigned int divisible = resultat & 0x80000000;
			resultat = (resultat << 1) | (loadedByte & 1);
			loadedByte = loadedByte >> 1;
			if(divisible) resultat = resultat ^ polynome;
		}
	}
	resultat = inverseByte(resultat);
	resultat ^= 0xFFFFFFFF;
	return resultat;
}

int ihdr(FILE*  file, unsigned char* buffer, long dataLen){
	printf("ihdr\n");
	return 0;
}
