build:
	gcc -Wextra -Wall *.c -o grip

builddebug:
	gcc -Wextra -Wall -g *.c -o grip

buildasan:
	gcc -Wextra -Wall -fsanitize=address *.c -o grip

run:
	echo "A needle in a haystack" | ./grip needle
