obj-m := birthday.o

KERNEL_DIR = /lib/modules/${shell uname -r}

PWD := $(shell pwd)

all:
	make -C $(KERNEL_DIR)/build M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c	
	make -C $(KERNEL_DIR)/build M=$(PWD) clean
.PHONY:
	clean
