
# macro for using the proper compiler
CC = gcc

all: final 
#complies a final.c file/ not arduino final.no which are the same files

final: final_funct.o final.o
	${CC} final_funct.o final.o -o final

# source file dependencies
final.o: final.h Adafruit_NeoPixel.h  Adafruit_NeoPixel.cpp


# utility targets

clean:
	-rm -f *.o

real_clean: clean
	-rm -f driver1 spchk a.out core