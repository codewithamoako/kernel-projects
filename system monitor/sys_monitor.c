#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
#include <linux/sched/signal.h>
#include <linux/utsname.h>

#define PROC_NAME "sys_monitor"
#define MB (1024 * 1024)

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("System monitor kernel module");
MODULE_VERSION("0.1");

// Function to display system information in the /proc file
static int monitor_show(struct seq_file *s, void *data)
{
	// Variables
	struct new_utsname *uts;
	struct sysinfo memory_info;
	struct task_struct *task;
	unsigned long total_mb, free_mb, used_mb;
	int process_count = 0;

	// Kernel Version
	uts = utsname();

	// Memory Usage
	si_meminfo(&memory_info);
	total_mb = (memory_info.totalram * PAGE_SIZE) / MB;
	free_mb = (memory_info.freeram * PAGE_SIZE) / MB;
	used_mb = total_mb - free_mb;

	// No of Processes
	for_each_process(task)
		process_count++;

	// Print everything to the /proc file
	seq_printf(s, "Kernel Version: %s\n", uts->release);
	seq_printf(s, "Memory total:\t %lu MB \n", total_mb);
	seq_printf(s, "Memory Free:\t %lu MB \n", free_mb);
	seq_printf(s, "Memory Used:\t %lu MB \n", used_mb);
	seq_printf(s, "Processes Count:\t %d \n", process_count);

	return 0;
}

// Seqfile start operation - called first during read
static void *monitor_seq_start(struct seq_file *s, loff_t *pos)
{
	static unsigned long counter = 0;

	if (*pos == 0)
		return &counter;
	else
		return NULL;
}

// Seqfile next operation - called to get next item
static void *monitor_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	(*pos)++;

	return NULL;
}

// Seqfile stop operation - called at the end of read
static void monitor_seq_stop(struct seq_file *s, void *v)
{
	// Do nothing.
}

static struct seq_operations monitor_seq_ops = {
	.start = monitor_seq_start,
	.next = monitor_seq_next,
	.stop = monitor_seq_stop,
	.show = monitor_show,
};

// Function called when /proc/sys_monitor is opened
static int monitor_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &monitor_seq_ops);
}

static const struct proc_ops monitor_file_ops = {
	.proc_open = monitor_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = seq_release,
};

// Module initialization function - creates /proc entry
static int __init monitor_init(void)
{
	struct proc_dir_entry *entry;

	entry = proc_create(PROC_NAME, 0, NULL, &monitor_file_ops);
	if (entry == NULL) {
		pr_err("Error: Could not create /proc/%s\n", PROC_NAME);
		return -ENOMEM;
	}

	pr_info("sys_monitor: /proc/%s created. Try: cat /proc/%s\n",
		PROC_NAME, PROC_NAME);
	return 0;
}

// Module cleanup function - removes /proc entry
static void __exit monitor_exit(void)
{
	remove_proc_entry(PROC_NAME, NULL);
	pr_info("sys_monitor: /proc/%s removed\n", PROC_NAME);
}

module_init(monitor_init);
module_exit(monitor_exit);