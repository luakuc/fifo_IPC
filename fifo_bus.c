/*
 * =====================================================================================
 *
 *       Filename:  fifo_bus.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/19/2014 05:22:01 PM
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
#include <linux/string.h>

#include "fifo_dev.h"
#include <linux/device.h>

static unsigned char  get_new_bogus_ida(void)
{
	static unsigned char ida=(unsigned char)IDA_MAGIC;
	return ida++;
}

static int fifo_bus_match(struct device *dev,struct device_driver *drv)
{
	if(!dev&&!drv)
		return 0;//cannot compare if one is NULL 
	{
		struct fifo_device * pdev = to_fifo_device(dev);
	//	return !strncmp(dev_name(dev),drv->name,strlen(drv->name));
	return !strncmp(pdev->name,drv->name,strlen(drv->name));
	}
}

//static int probe(struct device *dev)//bus->probe() verse driver->probe()
//{
		//struct fifo_device* local_fifo_device = to_fifo_device(dev);

//}
static int fifo_bus_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct fifo_device *fifo_pdev = to_fifo_device(dev);
	add_uevent_var(env,"MODALIAS=%s%s",FIFO_PREFIX,fifo_pdev->name);
	return 0;
}

struct bus_type fifo_bus_type;

struct device fifo_bus={
.init_name= FIFO_BUS_NAME,

};
struct bus_type fifo_bus_type={
	.name= FIFO_BUS_NAME,
	
	//.dev_root = &fifo_bus,

	.match=fifo_bus_match,
	.uevent=fifo_bus_uevent,
};

int fifo_device_register(struct fifo_device *pdev)
{
//	if(!pdev->device.parent)
	pdev->device.parent = &fifo_bus;
	pdev->device.bus = &fifo_bus_type;
	pdev->device.init_name = pdev->name;
	//if(!pdev->name)
	{
		//unsigned char ida =get_new_bogus_ida();
		//pdev->device.id=ida;
		//dev_set_name(&pdev->device,"%s.%s(%d)",FIFO_PREFIX,pdev->name,pdev->device.id);
	//	pdev->name = kmalloc(strlen(FIFO_PREFIX)+1+sizeof(unsigned char)+strlen(".auto")+1,GFP_KERNEL);
	//	sprintf(pdev->name,"%s\n",dev_name(&pdev->name));
	}
	printk("pdev->name: %s \t pdev->device.name: %s\n",pdev->name,dev_name(&pdev->device));
	return device_register(&pdev->device);
}
static void device_defualt_release(struct device* pdev)
{

}
void fifo_device_unregister(struct fifo_device *pdev)
{
	if(pdev->device.release==NULL)
		pdev->device.release = device_defualt_release;
	 device_unregister(&pdev->device);
}

EXPORT_SYMBOL(fifo_device_register);
EXPORT_SYMBOL(fifo_device_unregister);

int fifo_driver_register(struct fifo_driver * pdrv)
{
	pdrv->driver.bus = &fifo_bus_type;
	if(pdrv->driver.owner==NULL)
		pdrv->driver.owner=THIS_MODULE;

	return driver_register(&pdrv->driver);
}
void fifo_driver_unregister(struct fifo_driver * pdrv)
{
	driver_unregister(&pdrv->driver);
}

EXPORT_SYMBOL(fifo_driver_register);
EXPORT_SYMBOL(fifo_driver_unregister);

EXPORT_SYMBOL(fifo_bus);
EXPORT_SYMBOL(fifo_bus_type);


static int __init fifo_bus_init(void)
{
	int ret=bus_register(&fifo_bus_type);
	if(ret==0)
	{
		ret = device_register(&fifo_bus);
		if(ret)
			put_device(&fifo_bus);
	}
		return ret;
	
}
static void __exit fifo_bus_exit(void)
{
	device_unregister(&fifo_bus);
	bus_unregister(&fifo_bus_type);
}

module_init(fifo_bus_init);
module_exit(fifo_bus_exit);

MODULE_AUTHOR("");
MODULE_LICENSE("GPL");

