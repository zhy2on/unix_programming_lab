all: reader writer

reader: 19011522-reader.c
	gcc -o reader 19011522-reader.c

writer: 19011522-writer.c
	gcc -o writer 19011522-writer.c

test: test.c
	gcc -o test test.c

fclean:
	rm reader writer

re: fclean all
