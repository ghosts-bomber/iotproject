#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"serial.h"
int main(void) {
    serial_t *serial;
    uint8_t s[] = "Hello World!";
    uint8_t buf[128];
    int ret;

    serial = serial_new();

    /* Open /dev/ttyUSB0 with baudrate 115200, and defaults of 8N1, no flow control */
    if (serial_open(serial, "/dev/ttyUSB0", 115200) < 0) {
        fprintf(stderr, "serial_open(): %s\n", serial_errmsg(serial));
        exit(1);
    }
#if 0
    /* Write to the serial port */
    if (serial_write(serial, s, sizeof(s)) < 0) {
        fprintf(stderr, "serial_write(): %s\n", serial_errmsg(serial));
        exit(1);
    }
#endif
while(1)
{
    /* Read up to buf size or 2000ms timeout */
    if ((ret = serial_read(serial, buf, sizeof(buf), 2000)) < 0) {
        fprintf(stderr, "serial_read(): %s\n", serial_errmsg(serial));
        exit(1);
    }

    //printf("read %d bytes: _%s_\n", ret, buf);
    printf("%s",buf);
}
    serial_close(serial);

    serial_free(serial);

    return 0;
}