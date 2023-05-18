all: palindrom
palindrom:
	gcc -Wall -Werror -c src/*.c
	gcc -Wall -Werror *.o -o palindrom
	rm *.o
clean:
	rm palindrom
run:
	./palindrom