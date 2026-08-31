#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png.h"

int main(int argc, char* argv[]){
	if(argc < 3) {
		printf("\nUsage: pngcheck <command> <file>\n\n");
		return 1;
	}

	FILE* file = fopen(argv[2], "r");
	if(strcmp(argv[1], "ispng") == 0) {
		if(isPng(file) > 0){
			printf("not PNG\n");
			return 1;
		}else{
			printf("PNG file\n");
			return 0;
		}
	}
	else if(strcmp(argv[1], "list") == 0) list(file);
	else if(strcmp(argv[1], "cat") == 0) cat(file);
	else if(strcmp(argv[1], "integrity") == 0) {
		if(integrity(file) > 0){
			printf("PNG Corrupted");
			return 1;
		}else{
			printf("PNG not corrupted\n");
			return 0;
		}
	} else if(strcmp(argv[1], "delmd") ==  0){
		if(argc < 4){
			printf("\nUsage: pngcheck delmd <src> <dest>\n\n");
			return 1;
		} else return delmd(file, argv[3]);
	}
	fclose(file);
	return 0;
}
