#include "perfMonIOCTL18.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <asm/reg_fsl_emb.h>

#define mfpmr(rn)       ({unsigned int rval; \
                         asm volatile("mfpmr %0," __stringify(rn) \
                                     : "=r" (rval)); rval;})

#define mtpmr(rn, v)    asm volatile("mtpmr " __stringify(rn) ",%0" : : "r" (v))

#define FIRST_MINOR 0
#define MINOR_CNT 1

unsigned long read_pmc(int idx);
void write_pmc(int idx, unsigned long val);

void write_pmlca(int idx, unsigned long val);
unsigned long read_pmlca(int idx);

unsigned long read_pmlcb(int idx);
void write_pmlcb(int idx, unsigned long val);

void set_pmgc0();

void set_pmc_event(int ctr, int event);

void enable_perf_stat_counting(int ctr);

static int eventCount = 0;

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;

static int my_open(struct inode *i, struct file *f)
{
return 0;
}
static int my_close(struct inode *i, struct file *f)
{
return 0;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int my_ioctl(struct inode *i, struct file *f, unsigned int cmd, unsigned long arg)
#else
static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
#endif
{
	unsigned long q;

	switch (cmd)
	{
		case PERF_MON_READ:
			printk(KERN_INFO "FD in read is %d\n", f);
			printk(KERN_INFO "Going to read counter %d\n", arg);
			q = read_pmc(arg);
			printk(KERN_INFO "Q value in PERF_MON_READ is %lu\n", q);
			return q;
		break;
		case PERF_MON_EVENT_OPEN:
			if(eventCount < 4){
				printk(KERN_INFO "Going to map the event %d to counter %d\n", arg, eventCount);
				set_pmc_event(eventCount, arg);
				printk(KERN_INFO "Mapped the event \n");
				++eventCount;
				printk(KERN_INFO "Written the event open to file \n");
				return (eventCount-1);
			}
			else{
				return -EINVAL;
			}

		break;
		case PERF_MON_RESET:
			printk(KERN_INFO "Going to reset counters %d\n", arg);
			write_pmc(arg, 0);
		break;
		
		case PERF_MON_ENABLE:
			printk(KERN_INFO "Going to enable counters %d\n", arg);
			write_pmc(arg, 0);
		break;
		case PERF_MON_DISABLE:
			printk(KERN_INFO "Going to disable counters %d\n", arg);		
			write_pmlca(arg, 0);
		break;		
		default:
			return -EINVAL;
	}

	return 0;
}


static struct file_operations query_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
	.ioctl = my_ioctl
	#else
	.unlocked_ioctl = my_ioctl
	#endif
};


static int __init perfMon_ioctl_init(void)
{
	int ret;
	struct device *dev_ret;


	if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "perfMon_ioctl")) < 0)
	{
		return ret;
	}

	cdev_init(&c_dev, &query_fops);

	if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
	{
		return ret;
	}

	if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
	{
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(cl);
	}
	if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "perfMon")))
	{
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(dev_ret);
	}
	printk(KERN_INFO "Performance Monitoring Started \n");
	int i = 0;
	/* clear PMC counter as well as PMLCA);*/
	for(i = 0; i < 4; i++)
		write_pmc(i,0);

	for(i = 0; i < 4; i++){
		write_pmlca(i,0);
		write_pmlcb(i,0);
	}

	set_pmgc0();
	return 0;
}

static void __exit perfMon_ioctl_exit(void)
{
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
}

void set_pmgc0(){
	mtpmr(PMRN_PMGC0, 0);
}

void set_pmc_event(int ctr, int event)
{
	u32 pmlca;
	pmlca = read_pmlca(ctr);
	//printk(KERN_INFO "before setting the event %lu \n", pmlca);
	//printk(KERN_INFO "before setting the event %x \n", pmlca);
	pmlca = (pmlca & ~PMLCA_EVENT_MASK) |
		((event << PMLCA_EVENT_SHIFT) &
		 PMLCA_EVENT_MASK);
	write_pmlca(ctr, pmlca);
	pmlca = read_pmlca(ctr);
	//printk(KERN_INFO "PMLCA after mapping event to PMLCA %lu \n", pmlca);
	//printk(KERN_INFO "PMLCA after mapping event to PMLCA %x \n", pmlca);

}

void enable_perf_stat_counting(int ctr){
	/* Clear PMLCan[FCS], PMLCan[FCU], PMLCan[FCM1], and PMLCan[FCM0] for each counter control. */
	u32 pmlca = read_pmlca(ctr);
	pmlca &= ~(PMLCA_FCU | PMLCA_FCM1);
	/* Mark this process so that events can be monitored for this process */
	/* Marked and user - refer to table 9-45) */
	pmlca &= (PMLCA_FCS | PMLCA_FCM0); 
	write_pmlca(ctr, pmlca);
	pmlca = read_pmlca(ctr);
	//printk(KERN_INFO "PMLCA%d after enabling unconditional counting %lu \n", ctr,pmlca);	
}
unsigned long read_pmc(int idx)
{
	unsigned long val;

	switch (idx) {
		case 0:
			val = mfpmr(PMRN_PMC0);			
		break;
		case 1:
			val = mfpmr(PMRN_PMC1);
		break;
		case 2:
			val = mfpmr(PMRN_PMC2);
		break;
		case 3:
			val = mfpmr(PMRN_PMC3);
		break;
		default:
			printk(KERN_ERR "oops trying to read PMC%d\n", idx);
			val = 0;
		break;		
	}
	printk(KERN_INFO "PMC Counter %d value is %lu\n",idx, val);
	return val;
}


void write_pmc(int idx, unsigned long val)
{
	switch (idx) {
		case 0:
			mtpmr(PMRN_PMC0, val);
		break;
		case 1:
			mtpmr(PMRN_PMC1, val);
		break;
		case 2:
			mtpmr(PMRN_PMC2, val);
		break;
		case 3:
			mtpmr(PMRN_PMC3, val);
		break;
		default:
			printk(KERN_ERR "oops trying to write PMC%d\n", idx);
		break;
	}
	isync();
}

unsigned long read_pmlca(int ctr)
{
	unsigned long val;

	switch (ctr) {
		case 0:
			val = mfpmr(PMRN_PMLCA0);
		break;
		case 1:
			val = mfpmr(PMRN_PMLCA1);
		break;
		case 2:
			val = mfpmr(PMRN_PMLCA2);
		break;
		case 3:
			val = mfpmr(PMRN_PMLCA3);
		break;
		default:
			printk(KERN_ERR "oops trying to read PMLCA%d\n", ctr);
			val = 0;
		break;
	}
	return val;
}

void write_pmlca(int idx, unsigned long val)
{
	switch (idx) {
		case 0:
			mtpmr(PMRN_PMLCA0, val);
		break;
		case 1:
			mtpmr(PMRN_PMLCA1, val);
		break;
		case 2:
			mtpmr(PMRN_PMLCA2, val);
		break;
		case 3:
			mtpmr(PMRN_PMLCA3, val);
		break;
		default:
			printk(KERN_ERR "oops trying to write PMLCA%d\n", idx);
		break;
	}

	isync();
}

unsigned long read_pmlcb(int ctr)
{
	unsigned long val;

	switch (ctr) {
		case 0:
			val = mfpmr(PMRN_PMLCB0);
		break;
		case 1:
			val = mfpmr(PMRN_PMLCB1);
		break;
		case 2:
			val = mfpmr(PMRN_PMLCB2);
		break;
		case 3:
			val = mfpmr(PMRN_PMLCB3);
		break;
		default:
			printk(KERN_ERR "oops trying to read PMLCB%d\n", ctr);
			val = 0;
		break;
	}
	return val;
}

/*
* Write one local control B register
*/
void write_pmlcb(int idx, unsigned long val)
{
	switch (idx) {
		case 0:
			mtpmr(PMRN_PMLCB0, val);
		break;
		case 1:
			mtpmr(PMRN_PMLCB1, val);
		break;
		case 2:
			mtpmr(PMRN_PMLCB2, val);
		break;
		case 3:
			mtpmr(PMRN_PMLCB3, val);
		break;
		default:
			printk(KERN_ERR "oops trying to write PMLCB%d\n", idx);
		break;
	}

	isync();
}


module_init(perfMon_ioctl_init);
module_exit(perfMon_ioctl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SIUC");
MODULE_DESCRIPTION("P4080DS Performance Monitor");
MODULE_SUPPORTED_DEVICE("P4080DS");


