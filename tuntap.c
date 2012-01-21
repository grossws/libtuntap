/*
 * Copyright (c) 2012, Konstantin Gribov. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

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
