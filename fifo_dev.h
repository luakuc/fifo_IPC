
#ifndef _FIFO_DEV_H_
#define _FIFO_DEV_H_


#include <linux/device.h>

#define FIFO_BYTE 1024
#define FIFO_BUS_NAME "fifo-IPC-bus"
#define FIFO_PREFIX "fifo-IPC"

#define FIFO_DEFAULT_NAME "mini_fifo"
#define IDA_MAGIC (25&0xffU)

struct fifo_device{
	struct device device;
	char fifo[FIFO_BYTE];
	size_t current_data_pos;//start position  of data stored space, when no data in fifo[],current_data_pos == start_empty_pos and current_data_pos == 0
	size_t start_empty_pos;//start position of usable space of fifo[],and if there is no room for data storing,start_empty_pos will be given value of FIFO_BYTE
	ssize_t remaind_space;//
	void *private_data;
	char  name[1];
};
#define to_fifo_device(dev) container_of(dev,struct fifo_device,device)

struct fifo_driver{
	char *name;
	char *version;
	struct module  *module;
	struct device_driver driver;
	
};

#define to_fifo_driver(drv) container_of(drv,struct fifo_driver,driver)

extern int fifo_device_register(struct fifo_device*);
extern void fifo_device_unregister(struct fifo_device*);
extern int fifo_driver_register(struct fifo_driver*);
extern void fifo_driver_unregister(struct fifo_driver*);

#endif
