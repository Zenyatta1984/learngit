OBJS:=$(wildcard *.c)
main:${OBJS}
	gcc $^ -o $@ -pthread
clean:
	rm main
