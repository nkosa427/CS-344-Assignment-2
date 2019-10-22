CC=gcc

all: r c

r:
	$(CC) kosan.buildrooms.c -o a

c:
	./a

clean:
	rm -f a


