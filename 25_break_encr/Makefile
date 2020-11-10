breaker:breaker.c
	gcc -o breaker -Wall -Werror --pedantic -std=gnu99 breaker.c

encrypt:
	gcc -o encrypt -Wall -Werror -pedantic -std=gnu99 encryption.c

test-text:
	./encrypt 6 sample-text.txt > test-text.txt
