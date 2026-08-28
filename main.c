#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png.h"

int main(int argc, char* argv[]){

	if(argc < 2) {
		printf("\nUsage: pngcheck <commande> <file>\n\n");
		return 1;
	}

	FILE* file = fopen(argv[2], "r");
	if(isPng(file) > 0) exit(1);
	if(strcmp(argv[1], "list") == 0) list(file);
	else if(strcmp(argv[1], "cat") == 0) cat(file);
	
	fclose(file);
	return 0;
}
