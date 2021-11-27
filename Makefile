CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
SRCFILES = sysprak-client.c helperFunctions.c
MAIN = sysprak-client

all: $(MAIN) 

$(MAIN): $(SRCFILES)
	$(CC) $(CFLAGS) -o $(MAIN) $(SRCFILES)
    
clean:
	rm -f $(MAIN)