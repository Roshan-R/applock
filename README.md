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

# Demo


https://user-images.githubusercontent.com/43182697/158877358-9772a86c-906a-48c7-97ef-61b84082199f.mp4

