#ifndef CHUNK_H
#define CHUNK_H

struct chunk_type { char* type; int (*chunkDataRead)(FILE* file, unsigned char* buffer, long dataLen);};
int ihdr(FILE*  file, unsigned char* buffer, long dataLen);
char* chunkType(FILE* file, unsigned char* buffer);
long chunkLength(FILE* file, unsigned char* buffer);

#endif