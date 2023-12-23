CC = gcc
FLAGS = -Werror -fsanitize=address
smoldb: smoldb.c
	$(CC) $(FLAGS) -o smoldb smoldb.c

clean:
	rm smoldb