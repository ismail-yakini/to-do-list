# Make file hahaha
all:
	gcc main.c src/date_time.c src/to_do_list.c -o main
exec:
	./main
clear:
	rm main