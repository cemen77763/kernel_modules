#include <linux/module.h>           
#include <linux/init.h>  
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>

static char *buf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 600, my_minor = 0;

static struct cdev *my_cdev;

#define MYDEV_NAME  "chardev"
#define BUF_SIZE (size_t)((10) * PAGE_SIZE)


static int mychrdev_open(struct inode *inode, struct file *file){
	printk(KERN_ALERT "Opening device %s \n", MYDEV_NAME);
	return 0;
}

static int mychrdev_release(struct inode *inode, struct file *file){
	printk(KERN_ALERT "Releasing device %s \n", MYDEV_NAME);
	return 0;
}

static ssize_t mychrdev_read(struct file *file, char __user *buffer, size_t lbuffer, loff_t *ppos){
	int  nbytes = lbuffer - copy_to_user(buffer, buf + *ppos, lbuffer);
	*ppos += nbytes;

	printk(KERN_ALERT "Read device %s nbytes = %d, ppos = %d; \n", MYDEV_NAME, nbytes, (int)*ppos);

	return nbytes;
}

static ssize_t mychrdev_write(struct file *file, const char __user *buffer, size_t lbuffer, loff_t *ppos){
	int nbytes = lbuffer - copy_from_user(buf + *ppos, buffer, lbuffer);
	*ppos += nbytes;

	printk(KERN_ALERT "Write device %s nbytes = %d, ppos = %d; \n", MYDEV_NAME, nbytes, (int)*ppos);

	return nbytes;
}


static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.read = mychrdev_read,
	.write = mychrdev_write,
	.open = mychrdev_open,
	.release = mychrdev_release
};


static int dev_init(void)
{
  printk(KERN_ALERT "Hello world\n");
  buf = kmalloc(BUF_SIZE, GFP_KERNEL);

  first = MKDEV(my_major, my_minor);
  register_chrdev_region(first, count, MYDEV_NAME);

  my_cdev = cdev_alloc();

  cdev_init(my_cdev, &mycdev_fops);
  cdev_add(my_cdev, first, count);

  return 0;
}

static void  dev_exit(void)
{
  printk(KERN_ALERT "Goodbye world\n");
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");