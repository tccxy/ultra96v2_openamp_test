/*  icc.c - The simplest kernel module.

* Copyright (C) 2013 - 2016 Xilinx, Inc
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along
*   with this program. If not, see <http://www.gnu.org/licenses/>.

*/
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/of_address.h>
#include <linux/slab.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/compiler.h>
#include <linux/of.h>
#include <linux/highmem.h>
#include <linux/fsl_ifc.h>
#include <linux/irqreturn.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/hwmon-sysfs.h>
#include <linux/hwmon.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/sysfs.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/delay.h>

#include <linux/irqchip.h>
#include <linux/irqchip/chained_irq.h>
#include <linux/irqchip/arm-gic.h>

#include <asm/smp.h>


#define drv_printk(...)\
    do\
    {\
        if (1)\
        {\
            printk(__VA_ARGS__);\
        }\
    }while(0)
#define DRIVER_NAME "icc"

#define OCM_ADDR 0xfffc000

struct icc_local {
	int irq;
	void __iomem *iobase;
	const struct attribute_group *groups;/**添加sys下的属性用于应用调用 */
};

static ssize_t icc_write ( struct device *dev, struct device_attribute *devattr,
                            const char *buf, size_t count )

{
    //struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
    struct icc_local *lp = dev_get_drvdata ( dev );

    drv_printk ( "%s enter.\n", __func__ );


    return count;
}


static ssize_t icc_read  ( struct device *dev, struct device_attribute *devattr,
                              char *buf )

{
    //struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
    struct icc_local *lp = dev_get_drvdata ( dev );
	int value = 0;

    drv_printk ( "%s enter.\n", __func__ );
	value = readw ( lp->iobase  );

    return value;
}

static SENSOR_DEVICE_ATTR ( icc_write, S_IWUSR, NULL, icc_write, 0 );
static SENSOR_DEVICE_ATTR ( icc_read, S_IRUSR, icc_read, NULL, 0 );

static struct attribute *icc_attributes[] =
{
    &sensor_dev_attr_icc_write.dev_attr.attr,
    &sensor_dev_attr_icc_read.dev_attr.attr,
    NULL
};



static const struct attribute_group icc_group =
{
    .attrs = icc_attributes,
};



static void icc_kick(void)
{
	printk("icc interrupt\n");
}

static int icc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct icc_local *lp = NULL;

	int rc = 0;
	int *ocm_addr = NULL;

	drv_printk("icc: probe has in\n");
	ocm_addr = (int *)OCM_ADDR;
	lp = devm_kzalloc ( &pdev->dev, sizeof ( struct icc_local ), GFP_KERNEL );
    if ( !lp )
    {
        drv_printk ( "Unable to allocate device private data\n" );
        return -ENOMEM;
    }
	#if 0
	rc = of_property_read_u32(pdev->dev.of_node, "sgino",
				&lp->irq);
	if (rc) {
		drv_printk("IPI read sgino error\n");
		return -ENOMEM;
	}
	drv_printk("icc: lp->irq is %x\n",lp->irq);
	rc = set_ipi_handler(lp->irq, icc_kick,
			"icc kick");
	if (rc) {
		drv_printk("IPI handler already registered\n");
		return -ENOMEM;
	}
	#endif
	lp->iobase = ioremap(ocm_addr, SZ_64K);
	drv_printk( "lp->iobase = %x\n", lp->iobase);
	rc = sysfs_create_group ( &pdev->dev.kobj, &icc_group );

	
	return rc;
}

static int icc_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct icc_local *lp = dev_get_drvdata(dev);
	sysfs_remove_group ( &pdev->dev.kobj, lp->groups );
	return 0;
}

static const struct of_device_id icc_match[] =
{
	{
		.compatible = "autobrain,icc",
	},
	{ },
};

static struct platform_driver icc_driver =
{
    .driver = {
        .name  = "icc",
        .of_match_table = icc_match,
    },
    .probe  = icc_probe,
    .remove = icc_remove,
};

module_platform_driver ( icc_driver );

/* Standard module information, edit as appropriate */
MODULE_LICENSE("GPL");
MODULE_AUTHOR ("zw.");
MODULE_DESCRIPTION("icc for amp");