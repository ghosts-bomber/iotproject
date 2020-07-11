cc=gcc 
cflags=-lmosquitto -lpthread -ldl
cflags+=-I/home/mabao/share/mqtt/mosquitto/include
cflags+=-L/home/mabao/share/mqtt/mosquitto/lib

main:
	$(cc) subscriber.c -o subscriber $(cflags)
	$(cc) publisher.c -o publisher $(cflags)
	
.phony:clean
clean:
	rm *.o subscriber publisher -fr

