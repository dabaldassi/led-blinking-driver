obj-m := main.o
EXTRA_CFLAGS += -DDEBUG

all:$(BUILD_DIR_MAKEFILE)
	make VERBOSE=1 -C /lib/modules/$(shell uname -r)/build M=$(PWD) src=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) src=$(PWD) clean
