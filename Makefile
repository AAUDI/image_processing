image.bin : main.o image.o
	gcc -o main.bin main.o image.o

main.o : main.c image.h
	gcc -c main.c

image.o : image.c image.h
	gcc -c image.c

clean : 
	rm *.o *.bin
