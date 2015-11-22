
# Makefile
# Leon Tabak
# CSC311 Systems Software
# 23 November 2015

all:
	gcc src/eratosthenes.c -o eratosthenes -Wall
	gcc src/schedules.c -lm -o schedules -Wall
	gcc src/treesort.c -o treesort -Wall

eratosthenes: src/eratosthenes.c
	gcc src/eratosthenes.c -o eratosthenes -Wall
schedules: src/schedules.c
	gcc src/schedules.c -lm -o schedules -Wall
treesort: src/treesort.c
	gcc src/treesort.c -o treesort -Wall

clean:
	rm -f eratosthenes src/eratosthenes.c~
	rm -f schedules src/schedules.c~
	rm -f treesort src/treesort.c~
