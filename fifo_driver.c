/*
 * =====================================================================================
 *
 *       Filename:  fifo_driver.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/19/2014 04:24:29 PM
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
#include <linux/device.h>
#include <linux/slab.h>

#include "fifo_dev.h"

static struct fifo_driver mini_fifo_drv={
	.name = FIFO_DEFAULT_NAME,
	.module = THIS_MODULE,
	.version = "$version:T/0.1",
	.driver = {
		.name = FIFO_DEFAULT_NAME,
	//	.bus = &fifo_bus_type,
		.owner = THIS_MODULE,
		
	},
};

static ssize_t fifo_device_show(struct device*dev,struct device_attribute *attr,char *buf)
{
	struct fifo_device *pfifo_dev = to_fifo_device(dev);
	
	//size_t count = 0;
/* /	if(pfifo_dev->current_data_pos>=pfifo_dev->start_empty_pos)
	{
		if(unlikely(pfifo_dev->start_empty_pos==FIFO_BYTE))
		{
			count+=FIFO_BYTE - pfifo_dev->current_data_pos;
			strncpy(buf,&(pfifo_dev->fifo[pfifo_dev->current_data_pos]),count);
			strncpy(buf+count,&(pfifo_dev->fifo)[0],FIFO_BYTE-count);
			pfifo_dev->current_data_pos = 0;
			pfifo_dev->start_empty_pos = 0;
		}
		else
		{
		count += FIFO_BYTE - pfifo_dev->current_data_pos;
		strncpy(buf,&pfifo_dev->fifo[pfifo_dev->current_data_pos],count);
		strncpy(buf+count,&pfifo_dev->fifo[0],pfifo_dev->start_empty_pos);
		count += pfifo_dev->start_empty_pos;
		pfifo_dev->current_data_pos = 0;
		pfifo_dev->start_empty_pos = 0;//when no data in pdev->fifo,current_data_pos == start_empty_pos,and also current_data_pos == 0

		}
	}
	else
	{
		count = pfifo_dev->start_empty_pos - pfifo_dev->current_data_pos ;
		strncpy(buf,&(pfifo_dev->fifo[pfifo_dev->current_data_pos]),count);
		pfifo_dev->current_data_pos =0;
		pfifo_dev->start_empty_pos = 0;
	}
	*/

	if(unlikely(pfifo_dev->remaind_space == FIFO_BYTE))
	{
		return 0;
	}
	else
	{
		int i=0;
		int ret=FIFO_BYTE- pfifo_dev->remaind_space;
		for(;i<ret;i++)
		{
			buf[i] = pfifo_dev->fifo[pfifo_dev->current_data_pos];
			pfifo_dev->current_data_pos = (pfifo_dev->current_data_pos+1)%FIFO_BYTE;
		}		
	pfifo_dev->remaind_space+=ret;
	return ret;
	}

}
static ssize_t fifo_device_store(struct device *pdev,struct device_attribute *attr,const char *buf,size_t count)
{
	struct fifo_device *pfifo_dev = to_fifo_device(pdev);
	
//	if(unlikely(pfifo_dev->start_empty_pos == FIFO_BYTE))
	if(unlikely(pfifo_dev->remaind_space==0))
	{
		return 0;//pfifo_dev->fifo[] already full
	}else
	{
		ssize_t ret  =0;
				
		if(likely(pfifo_dev->remaind_space >= count))
		{
			//if(pfifo_dev->start_empty_pos+count >= FIFO_BYTE)
			//{
			//	ret = FIFO_BYTE - pfifo_dev->start_empty_pos;
			//	strncpy(&pfifo_dev->fifo[pfifo_dev->start_empty_pos],buf,ret);
			//	strncpy(&pfifo_dev->fifo[0],buf+ret,count-ret);
			//	ret = count;

		//	}else
			//{
			//	strncpy(&pfifo_dev->fifo[pfifo_dev->start_empty_pos],buf,count);
			//	ret = count;
			//}
			ret = count;
		//	pfifo_dev->remaind_space = pfifo_dev->remaind_space -count;
		}
		else
		{
			ret = pfifo_dev->remaind_space;
		//	pfifo_dev->remaind_space = 0;
		}
	
		{
			int i=0;
		
			for(;i<ret;i++)
			{
				pfifo_dev->fifo[pfifo_dev->start_empty_pos]=buf[i];
				pfifo_dev->start_empty_pos= (pfifo_dev->start_empty_pos+1)%FIFO_BYTE;
			}
		}
		pfifo_dev->remaind_space -= ret;
		return ret;
	}
}
  
static int probe(struct device *pdev)
{
	struct fifo_device* pfifo_dev = to_fifo_device(pdev);
	//if(pfifo_dev->bus&&pfifo->bus->probe)
	//	pfifo_dev->bus->probe(pfifo_dev);
	struct device_attribute *dev_attr = kzalloc(sizeof(struct device_attribute),GFP_KERNEL);
	dev_attr->attr.name = "fifo-IPC-MEM";
	dev_attr->attr.mode = S_IRUGO|S_IWUGO;
	dev_attr->show = fifo_device_show;
	dev_attr->store = fifo_device_store;

	
	if(pfifo_dev->private_data==NULL)
	{
		pfifo_dev->private_data = dev_attr;

	}
	else
	{
		device_remove_file(pdev,(struct device_attribute*)(pfifo_dev->private_data));
		kfree(pfifo_dev->private_data);
		pfifo_dev->private_data = dev_attr;
	}
	
	device_create_file(pdev,dev_attr);
	return 0;
}

static int remove(struct device *pdev)
{
	struct fifo_device *pfifo_dev = to_fifo_device(pdev);
	
		device_remove_file(pdev,(struct device_attribute*)(pfifo_dev->private_data));
		kfree(pfifo_dev->private_data);

		pfifo_dev->private_data=NULL;
	return 0;
}


static ssize_t version_show(struct device_driver *driver,char *buf)
{
	return 	snprintf(buf,PAGE_SIZE,"%s\n",mini_fifo_drv.version);
}


static DRIVER_ATTR_RO(version);

static int __init mini_fifo_driver_init(void)
{
	mini_fifo_drv.driver.probe = probe;
	mini_fifo_drv.driver.remove = remove;

	fifo_driver_register(&mini_fifo_drv);
	return 	driver_create_file(&mini_fifo_drv.driver,&driver_attr_version);
	
}


static void __exit mini_fifo_driver_exit(void)
{
	fifo_driver_unregister(&mini_fifo_drv);
}

module_init(mini_fifo_driver_init);
module_exit(mini_fifo_driver_exit);

MODULE_AUTHOR("");
MODULE_LICENSE("GPL");

