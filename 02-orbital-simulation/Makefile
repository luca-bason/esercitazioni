CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: Main

Vettore.o: Vettore.cpp
	$(CC) $(CFLAGS) -c Vettore.cpp      $(CFLAGSROOT)
PuntoMateriale.o: PuntoMateriale.cpp 
	$(CC) $(CFLAGS) -c PuntoMateriale.cpp    $(CFLAGSROOT)
OdeSolver.o: OdeSolver.cpp
	$(CC) $(CFLAGS) -c OdeSolver.cpp      $(CFLAGSROOT)
Main: Main.cpp Vettore.o PuntoMateriale.o OdeSolver.o
	$(CC) $(CFLAGS) -o Main Main.cpp Vettore.o OdeSolver.o PuntoMateriale.o $(CFLAGSROOT) $(LIBSROOT)

clean:
	rm *.o Main MainPM
