CC=gcc

all: r c

r:
	$(CC) kosan.buildrooms.c -o a
	$(CC) kosan.adventure.c -o b

c:
	./a
	./b

ad:
	$(CC) kosan.adventure.c -o b
	./b

clean:
	rm -f a


