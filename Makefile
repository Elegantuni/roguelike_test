roguelike_test:
	$(CC) -std=c99 -o roguelike_test main.c -lncurses

clean:
	rm -f roguelike_test
