obj-m += dev_mod.o

all:
	# symlink for /usr/src/kernels/$(uname -r)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
