# Memory Tracker Kernel Module

A Linux kernel module that tracks and displays memory usage information for all running processes.

## Overview

This kernel module creates a `/proc/memory_tracker` entry that displays a table of all processes with their:

- **PID** - Process ID
- **NAME** - Process name
- **MEMORY_USED** - Resident Set Size (RSS) in MB
- **PAGE_FAULTS** - Total page faults (major + minor)

## Requirements

- Linux kernel headers for the running kernel
- `make` utility
- Root/sudo access for loading/unloading the module

## Building

```bash
make
```

This will compile the kernel module and produce `memory_tracker.ko`.

## Loading the Module

```bash
sudo make load
# or
sudo insmod memory_tracker.ko
```

## Viewing Memory Information

Once loaded, view the memory tracker output:

```bash
cat /proc/memory_tracker
```

## Unloading the Module

```bash
sudo make unload
# or
sudo rmmod memory_tracker
```

## Reloading the Module

```bash
sudo make reload
```

## Module Information

View module details:

```bash
make info
```

## Cleaning

Remove build artifacts:

```bash
make clean
```

## Installation

Install the module system-wide:

```bash
sudo make install
```

## Output Example

```
PID  NAME                MEMORY_USED     PAGE_FAULTS
---  ----                -----------     -----------
1    systemd             15              12345
2    kthreadd            0               0
123  bash                5               5432
456  nginx               25              9876
...
```

## License

GPL

## Version

0.1
