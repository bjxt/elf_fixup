all:	fixelf.o
	$(CC) fixelf.o -o fixelf

clean:
	rm -rf fixelf.o fixelf
