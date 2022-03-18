applock : applock.c proc.c util.c
	gcc applock.c proc.c util.c -o applock `pkg-config --libs libconfig openssl`

clean:
	rm applock
