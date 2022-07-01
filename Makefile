applock : applock.c proc.c util.c
	gcc applock.c proc.c util.c -o applock `pkg-config --libs libconfig openssl`

install : applock
	mkdir -p /opt/applock
	cp ./config.cfg /opt/applock/config

clean:
	rm applock
