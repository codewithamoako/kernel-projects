obj-m += sys_monitor.o

# If the module has multiple source files, list them here
# sys_monitor-objs := file1.o file2.o

# Kernel build directory - use running kernel by default
KDIR ?= /lib/modules/$(shell uname -r)/build

# Build directory (current directory)
PWD := $(shell pwd)

# Compiler flags
ccflags-y := -Wall -Wextra

# Default target: build the module
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Clean target
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

# Install the module
install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

# Load the module
load:
	sudo insmod sys_monitor.ko

# Unload the module
unload:
	sudo rmmod sys_monitor

# View module info
info:
	modinfo sys_monitor.ko

# Reload the module (unload + load)
reload:
	sudo rmmod sys_monitor && sudo insmod sys_monitor.ko

.PHONY: all clean install load unload info reload
