cc=gcc 
exec=service_rc
obj=www_mqtt_rt.o sqlite3.o analy_data.o
cflags=-ldl -pthread
$(exec):$(obj)
	$(cc) $^ -o $@	$(cflags)
%.o:%.c
	$(cc) -c $< -o $@ $(cflags)
clean:
	rm *.o $(exec)

