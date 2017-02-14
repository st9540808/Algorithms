all: main

objects =
CC = g++-6
INCULDE = .
CFLAGS = -g -Wall -Wextra -std=gnu++14 

main: main.cpp Solution.h $(objects)
	$(CC) -o main main.cpp -I $(INCULDE) $(CFLAGS) $(objects)


.PHONY: clean
clean:
	rm main $(objects)
