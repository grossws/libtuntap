#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/ioctl.h>

#include <net/if.h>
#include <linux/if_tun.h>

#include "tuntap.h"

#define IF_NAME_SIZE 14

int tuntap_open(char *dev, int flags) {
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ) {
    perror("Can't open /dev/net/tun");
    return fd;
  }

  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = flags;
  if( *dev )
    strncpy(ifr.ifr_name, dev, IF_NAME_SIZE);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    perror("ioctl error");
    close(fd);
    return err;
  }

  strcpy(dev, ifr.ifr_name);

  return fd;
}

int tun_open(char *dev) { return tuntap_open(dev, IFF_TUN | IFF_NO_PI ); }
int tap_open(char *dev) { return tuntap_open(dev, IFF_TAP | IFF_NO_PI ); }

int tun_close(int fd) { return close(fd); }
int tap_close(int fd) { return close(fd); }

int tun_write(int fd, char *buf, int len) { return write(fd, buf, len); }
int tap_write(int fd, char *buf, int len) { return write(fd, buf, len); }

int tun_read(int fd, char *buf, int len) { return read(fd, buf, len); }
int tap_read(int fd, char *buf, int len) { return read(fd, buf, len); }
