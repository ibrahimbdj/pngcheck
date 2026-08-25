pngcheck: main.o png.o
	gcc -o pngcheck main.o png.o

main.o: main.c
	gcc -Wall -MMD -c main.c

png.o: png.c
	gcc -Wall -MMD -c png.c

clean:
	rm -f pngcheck *.o *.d

-include main.d png.d
