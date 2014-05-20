/*
 * =====================================================================================
 *
 *       Filename:  fiffo_dev.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/19/2014 11:38:46 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/slab.h>
#include "fifo_dev.h"

static struct fifo_device *_fifo_device=NULL;

static struct fifo_device * alloc_fifo_device(char* name )
{
	int size = sizeof(struct fifo_device) + strlen(name);
	
	//	struct fifo_device *dev= kzalloc(size,GFP_KERNEL);
		struct fifo_device *dev = kmalloc(size,GFP_KERNEL);
		memset(dev,0,size);
	printk("sizeof(fifo_device)+ strlen(name): %d\n",size);
		if(dev==NULL)
			return NULL;
		strcpy(dev->name,name);
		
		dev->current_data_pos = 0;
		dev->start_empty_pos = 0;
		dev->remaind_space = FIFO_BYTE;
		

		printk("strlen(name)=%d\n",strlen(name));
	//	dev->name[strlen(name)]=0;
		//	dev->device.init_name=dev->name;
		//printk("dev->dev.name : %s\n",dev->device.init_name);
		fifo_device_register(dev);//注册platfotaticm_device
		return dev;
}

static void dealloc_fifo_device(struct fifo_device *dev)
{
	fifo_device_unregister(dev);
	kfree(dev);
}


static int __init fifo_init(void)
{

	_fifo_device=alloc_fifo_device(FIFO_DEFAULT_NAME);
	if(_fifo_device!=NULL)
		return 0;
	else
		return -EIO;
}
static void __exit fifo_exit(void)
{
	dealloc_fifo_device(_fifo_device);
}

module_init(fifo_init);
module_exit(fifo_exit);


MODULE_AUTHOR("");
MODULE_LICENSE("GPL");
