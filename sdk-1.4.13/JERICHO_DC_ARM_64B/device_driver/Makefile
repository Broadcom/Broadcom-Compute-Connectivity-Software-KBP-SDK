# 
# This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
#
# $Copyright: (c) 2021 Broadcom Inc.
# All Rights Reserved$
# $ID:$
#

obj-m := kbp_driver.o

KERNELDIR := /lib/modules/$(shell uname -r)/build

##     useful option for building modules:
##     make KBUILD_VERBOSE=1
##     make V=1

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf *.o *.ko *.mod.c *.mod.o .*.cmd .tmp_versions Module.symvers *~
