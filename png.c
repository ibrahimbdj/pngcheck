#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void  list(const char* path){
        FILE* file = fopen(path, "r");

        size_t l = 48;
        unsigned char* buffer = malloc(l);
        size_t tmp = fread(buffer, 1, l, file);
        while(tmp > 0){
                for(int i=0; i<tmp; i++){
                        printf("%02x ",  *(buffer+i));
                }
                tmp = fread(buffer, 1, l, file);
		printf("\n");
        }

        printf("\n");
        fclose(file);
        free(buffer);

}
