CC=gcc

infinity: infinity.c
	$(CC) $^ -o $@

clean:
	rm infinity #Careful now. Infinity is kind of important.
