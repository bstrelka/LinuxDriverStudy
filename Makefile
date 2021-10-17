CFLAGS += -Wall
CFILES = devone.c

obj-m += sample.o
sample-objs := $(CFILES:.c=.o)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) V=1 modules
	gcc app.c
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm a.out
	