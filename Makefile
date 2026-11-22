SRC = main.c vector.c reader.c

build:
	gcc -Wextra -Wall ${SRC} -o grip

builddebug:
	gcc -Wextra -Wall -g  ${SRC} -o grip

buildasan:
	gcc -Wextra -Wall -fsanitize=address,undefined ${SRC} -o grip

run:
	echo "A needle in a haystack" | ./grip needle

runlarge:
	cat /etc/services | ./grip e
