MAIN = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

HEADER = pipex.h
SRC = pipex.c utils.c error.c ft_split.c execute_cmds.c
OBJ = $(SRC:c=o)


all: $(MAIN)

$(MAIN): $(OBJ)
	@echo "compiling pipex..."
	@$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)
	@echo "done!"

%.o: %.c
	@echo "generating pipex objects...\n" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "deleting objects..."
	@rm -f $(OBJ)
	@echo "done!"

fclean:
	@echo "deleting objects..."
	@rm -f $(OBJ)
	@echo "deleting executable..."
	@rm -f $(MAIN)
	@echo "done!"

re: fclean all

.PHONY: clean fclean re bonus