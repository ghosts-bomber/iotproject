cc=gcc 
exec=zigbee_rc
obj=mqtt_rt.o serial.o
$(exec):$(obj)
	$(cc) $^ -o $@
%.o:%.c
	$(cc) -c $< -o $@
clean:
	rm *.o $(exec)

