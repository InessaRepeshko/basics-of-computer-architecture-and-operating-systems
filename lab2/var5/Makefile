CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
INCFOLDER = inc
OBJFOLDER = obj
SRCFOLDER = src
SRCFILES = main.c functionA.c functionB.c
OBJFILES = main.o functionA.o functionB.o
NAME = lab2

.PHONY: lab2 clean reinstall uninstall

all: $(NAME)

$(NAME): $(INCFOLDER) $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(NAME) -lm
	mkdir -p $(OBJFOLDER)
	mv $(OBJFILES) $(OBJFOLDER)

main.o: $(SRCFOLDER)/main.c
	$(CC) $(CFLAGS) -I $(INCFOLDER) -c $< -o $@

functionA.o: $(SRCFOLDER)/functionA.c
	$(CC) $(CFLAGS) -I $(INCFOLDER) -c $< -o $@

functionB.o: $(SRCFOLDER)/functionB.c
	$(CC) $(CFLAGS) -I $(INCFOLDER) -c $< -o $@

clean:
	rm -rf $(OBJFOLDER)

uninstall: clean
	rm -f $(NAME)

reinstall: uninstall all
