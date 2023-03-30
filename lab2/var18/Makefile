INC_FOLDER = inc
OBJ_FOLDER = obj
SRC_FOLDER = src
SRC_FILES = main.c function_a.c function_b.c
OBJ_FILES = main.o function_a.o function_b.o
NAME = LAB2
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g

.PHONY: LAB2 clean reinstall uninstall

all: $(NAME)

$(NAME): $(INC_FOLDER) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) -lm
	mkdir -p $(OBJ_FOLDER)
	mv $(OBJ_FILES) $(OBJ_FOLDER)

main.o: $(SRC_FOLDER)/main.c
	$(CC) $(CFLAGS) -I $(INC_FOLDER) -c $< -o $@

function_a.o: $(SRC_FOLDER)/function_a.c
	$(CC) $(CFLAGS) -I $(INC_FOLDER) -c $< -o $@

function_b.o: $(SRC_FOLDER)/function_b.c
	$(CC) $(CFLAGS) -I $(INC_FOLDER) -c $< -o $@

clean:
	rm -rf $(OBJ_FOLDER)

uninstall: clean
	rm -f $(NAME)

reinstall: uninstall all
