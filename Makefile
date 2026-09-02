pngcheck: main.o png.o chunk.o
	gcc -o pngwalk main.o png.o chunk.o

chunk.o: chunk.c
	gcc -Wall -MMD -c chunk.c

main.o: main.c
	gcc -Wall -MMD -c main.c

png.o: png.c
	gcc -Wall -MMD -c png.c

clean:
	rm -f pngcheck *.o *.d

-include main.d png.d chunk.d
