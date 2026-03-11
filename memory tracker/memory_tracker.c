#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/seq_file.h>

#define PROC_NAME "memory_tracker"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Memory tracker kernel module");
MODULE_VERSION("0.1");

// Callback function to display memory information for each process
static int show_handler(struct seq_file *m, void *v)
{
	struct task_struct *task;
	struct mm_struct *mm;

	seq_printf(m, "\n");
	seq_printf(m, "%-6s %-20s %-15s %-20s\n", "PID", "NAME",
		"MEMORY_USED", "PAGE_FAULTS");
	seq_printf(m, "%-6s %-20s %-15s %-20s\n", "---", "----", "-----------",
		 "-----------");

	for_each_process(task)
	{
		mm = task->mm;
		if (mm != NULL) {
			long rss = (get_mm_rss(mm) * PAGE_SIZE) / 1024 / 1024;
			long faults = 0;
			if (task->signal)
				faults =
				task->signal->maj_flt + task->signal->min_flt;

			seq_printf(m, "%-6d %-20s %-15ld %-20ld\n",
				   task->pid, task->comm, rss, faults);
		}
	}

	return 0;
}

// Handler for opening the proc file
static int open_handler(struct inode *inode, struct file *file)
{
	return single_open(file, show_handler, NULL);
}

// Proc file operations structure
static const struct proc_ops tracker_file_ops = {
	.proc_open = open_handler,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};

// Module initialization function
static int __init module_start(void)
{
	struct proc_dir_entry *entry;

	entry = proc_create(PROC_NAME, 0, NULL, &tracker_file_ops);
	if (entry == NULL) {
		pr_err("Error: Could not create /proc/%s\n", PROC_NAME);
		return -ENOMEM;
	}

	pr_info("mem_tracker: /proc/%s created\n", PROC_NAME);
	return 0;
}

// Module cleanup function
static void __exit module_stop(void)
{
	remove_proc_entry(PROC_NAME, NULL);
	pr_info("mem_tracker: /proc/%s removed\n", PROC_NAME);
}

module_init(module_start);
module_exit(module_stop);