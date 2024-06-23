CC = gcc
FLAGS = -Werror -fsanitize=address
smoldb: smoldb.c parser/parser.c engine/engine.c
	$(CC) $(FLAGS) -o smoldb smoldb.c

clean:
	rm smoldb