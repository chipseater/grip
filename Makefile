build:
	gcc -Wextra -Wall *.c -o grip

builddebug:
	gcc -Wextra -Wall -g *.c -o grip

run:
	./grip testfile pattern
