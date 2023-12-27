CC = gcc
FLAGS = -Werror -fsanitize=address
smoldb: smoldb.c parser.c engine.c
	$(CC) $(FLAGS) -o smoldb smoldb.c

clean:
	rm smoldb