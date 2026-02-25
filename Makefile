# Fill this makefile with the makefile format instructions to 
#   build your program.
dict1: dict1.o data.o csv.o bit.o
	gcc -o dict1 dict1.o data.o csv.o bit.o

data.o: data.c data.h
	gcc -c data.c

csv.o: csv.c csv.h
	gcc -c csv.c

bit.o: bit.c bit.h
	gcc -c bit.c

dict1.o: dict1.c

clean1: dict1
	rm *.o dict1

