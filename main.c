#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png.h"

int main(int argc, char* argv[]){

	if(argc < 2) {
		printf("\nUtilisation: png <commande> <file>\n\n");
		return 1;
	}

	if(strcmp(argv[1], "info") == 0) info(fopen(argv[2], "r"));
	else if(strcmp(argv[1], "cat") == 0) cat(fopen(argv[2], "r"));
	return 0;
}
