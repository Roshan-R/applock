# applock
An applocker for linux

# Dependencies
applockes depends on libconfig and openssl.
it uses zenity to make dialogues

# Builing 
to build applock, run 

```
gcc applock.c proc.c util.c -o applock `pkg-config --libs libconfig openssl`
sudo ./applock
```

the default password is '123'
