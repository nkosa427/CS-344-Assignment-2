CC=gcc

all: r c

r:
	$(CC) kosan.buildrooms.c -o a
	$(CC) kosan.adventure.c -o b -lpthread

c:
	./a
	./b

ad:
	$(CC) kosan.adventure.c -o b -lpthread
	./b

m:
	$(CC) kosan.adventure.c -o b -lpthread


clean:
	rm -f a


