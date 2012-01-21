#ifndef _TUNTAP_H
#define _TUNTAP_H

int tun_open(char *dev);
int tap_open(char *dev);

int tun_close(int fd);
int tap_close(int fd);

int tun_write(int fd, char *buf, int len);
int tap_write(int fd, char *buf, int len);

int tun_read(int fd, char *buf, int len);
int tap_read(int fd, char *buf, int len);

#endif
