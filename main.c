#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png.h"

int main(int argc, char* argv[]){

	if(argc < 2) {
		printf("\nUtilisation: png <commande> <file>\n\n");
		return 1;
	}

	if(strcmp(argv[1], "list") == 0) list(argv[2]);

	return 0;
}
