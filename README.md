# Linux Kernel Projects

A collection of Linux kernel modules that provide system monitoring and information gathering capabilities through the `/proc` filesystem.

## Projects

This repository contains kernel modules:

### 1. System Monitor (`system-monitor/`)
A kernel module that provides real-time system information through a virtual file at `/proc/sys_monitor`.

**Features:**
- Kernel version detection
- Memory usage statistics (total, free, used)
- Process count reporting

**Usage:**
```bash
sudo make load
cat /proc/sys_monitor
sudo make unload
```

### 2. Memory Tracker (`memory-tracker/`)
A kernel module that tracks and displays memory usage information for all running processes via `/proc/memory_tracker`.

**Features:**
- PID (Process ID) tracking
- Process name display
- RSS (Resident Set Size) memory usage in MB
- Page fault statistics (major + minor)

**Usage:**
```bash
sudo make load
cat /proc/memory_tracker
sudo make unload
```

## Requirements

- Linux kernel headers for the running kernel
- `make` utility
- Root/sudo access for loading/unloading modules
- A Linux system to run these modules

## Building

Each project can be built independently:

```bash
cd system-monitor
make

cd ../memory-tracker
make
```

## License

GPL
