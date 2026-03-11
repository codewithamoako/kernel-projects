obj-m += memory_tracker.o

# If the module has multiple source files, list them here
# memory_tracker-objs := file1.o file2.o

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
	sudo insmod memory_tracker.ko

# Unload the module
unload:
	sudo rmmod memory_tracker

# View module info
info:
	modinfo memory_tracker.ko

# Reload the module (unload + load)
reload:
	sudo rmmod memory_tracker && sudo insmod memory_tracker.ko

.PHONY: all clean install load unload info reload
