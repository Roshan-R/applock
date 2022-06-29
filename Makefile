applock : applock.c proc.c util.c
	gcc applock.c proc.c util.c -o applock `pkg-config --libs libconfig openssl`

install : applock
	mkdir -p ~/.config/app-lock 
	cp ./config.cfg ~/.config/app-lock/config

clean:
	rm applock
