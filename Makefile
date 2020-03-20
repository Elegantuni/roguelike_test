roguelike_test:
	gcc -std=c99 -o roguelike_test main.c -lncurses

clean:
	rm -f roguelike_test
