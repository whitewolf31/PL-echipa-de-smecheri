CC=gcc

build:
	mkdir build/
	$(CC) -o build/proiect_echipa proiect_echipa.c

clean: 
	rm -r build/