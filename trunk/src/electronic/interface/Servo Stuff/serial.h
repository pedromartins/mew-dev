
int serialport_writebyte( int fd, char b);
int serialport_write(int fd, const char* str);
int serialport_read_until(int fd, char* buf, char until);
int serialport_init(const char* serialport, int baud);
