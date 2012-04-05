all:
	gcc -Wall -O2 -fpic -shared -ldl -o errspeak.so errspeak.c

clean:
	rm errspeak.so
