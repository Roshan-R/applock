# applock
An applocker for linux

# Dependencies
applockes depends on libconfig and openssl

# Builing 
to build applock, run 

```
gcc applock.c proc.c util.c -o applock `pkg-config --libs libconfig openssl`
sudo ./applock
```
