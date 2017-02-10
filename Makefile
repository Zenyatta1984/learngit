long_chat:server_talk.c client_talk.c
	gcc server_talk.c -o server
	gcc client_talk.c -o client
clean:
	rm -rf server client
