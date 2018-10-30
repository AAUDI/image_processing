image.bin : main.o image.o
	gcc -o main.bin main.o image.o -lm `pkg-config --cflags opencv` `pkg-config --libs opencv`

main.o : main.c image.h
	gcc -c main.c

image.o : image.c image.h
	gcc -c image.c

clean : 
	rm *.o *.bin
