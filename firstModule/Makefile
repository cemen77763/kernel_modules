obj-m += firstmodule.o

KVERSION = $(shell uname -r)
all:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) clean
test:
	sudo dmesg -C
	sudo insmod firstmodule.ko
	sudo rmmod firstmodule.ko
	dmesg