Follwing steps are in expectation

<1> simply create  one sysfs-bus for bus-device and bus-driver to match  
	<1.1> implement it by sysfs attributes file fifo-MEM without file_operation directly    V
	<1.2> two or more progresses can communate  with each other                             V
	<1.3> support on wait-queue																trying
<2> find a way to access without multi-copy when data from user-space to kernel-space,like mmap 
	......
<3> add "asynchronous signal" like AIO if could
	......
<4> example foe explaination
	......
<5> doc prepare
	......
