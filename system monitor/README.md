# System Monitor Kernel Module

A Linux kernel module that provides real-time system information through the
`/proc` filesystem.

## Overview

This kernel module creates a virtual file at `/proc/sys_monitor` that displays
key system metrics including kernel version, memory usage, and process count.
It demonstrates how to create kernel modules that interact with the Linux proc
filesystem.

## Features

- **Kernel Version**: Displays the current Linux kernel release version
- **Memory Information**: Shows total, free, and used memory in MB
- **Process Count**: Reports the total number of running processes

## Requirements

- Linux kernel source/headers matching your running kernel
- `make` build tool
- Root/sudo privileges for loading/unloading the module

## Building

```bash
cd "System Monitor"
make
```

This will compile the module and generate `sys_monitor.ko`.

## Loading the Module

```bash
sudo make load
```

Or manually:
```bash
sudo insmod sys_monitor.ko
```

## Viewing System Information

Once loaded, view the system metrics:

```bash
cat /proc/sys_monitor
```

Expected output:
```
Kernel Version: <kernel-release>
Memory total:   <total-mb> MB
Memory Free:    <free-mb> MB
Memory Used:    <used-mb> MB
Processes Count: <count>
```

## Unloading the Module

```bash
sudo make unload
```

Or manually:
```bash
sudo rmmod sys_monitor
```

## Makefile Targets

| Target   | Description                    |
|----------|--------------------------------|
| `all`    | Build the kernel module        |
| `clean`  | Remove build artifacts         |
| `install`| Install the module system-wide |
| `load`   | Load the module into kernel    |
| `unload` | Remove the module from kernel  |
| `info`   | Display module information     |
| `reload` | Unload and reload the module   |

## Module Information

```bash
modinfo sys_monitor.ko
```

Shows:
- License: GPL
- Description: System monitor kernel module
- Version: 0.1

## Files

- `sys_monitor.c` - Main kernel module source code
- `Makefile` - Build configuration
- `README.md` - This documentation

## License

GPL
