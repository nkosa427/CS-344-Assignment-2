CC=gcc

all: r c clean

r:
	$(CC) kosan.buildrooms.c -o a

c:
	./a

clean:
	rm -f a


