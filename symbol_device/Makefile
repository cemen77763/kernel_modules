obj-m += device.o

KVERSION = $(shell uname -r)
all:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) clean
	
load: all
	sudo insmod device.ko
	sudo dmesg -c
unload:
	sudo rmmod device.ko
	sudo dmesg -c