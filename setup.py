from distutils.core import setup, Extension

tuntap_module = Extension('tuntap',
                    sources = ['tuntap.c', 'tuntap_wrap.c'])

setup (name = 'tuntap',
       version = '0.1',
       description = 'TUN/TAP adapter package for Linux',
       ext_modules = [tuntap_module])
