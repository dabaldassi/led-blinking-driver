#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/timer.h>

#define LED 16

MODULE_AUTHOR("dabaldassi");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Testing LEDs with the rasp");

static struct timer_list timer_blink;
static const unsigned int blink_time = 500u; // msecs

static void blink_callback(struct timer_list * timer)
{
	int value;
	value = gpio_get_value(LED);
	gpio_set_value(LED, !value);
	mod_timer(timer, jiffies + msecs_to_jiffies(blink_time));
}

static int __init init_ledblinking(void)
{
	int ret = 0;

	if(gpio_is_valid(LED) == false)
	{
		pr_info("Gpio is not valid");
		return -1;
	}

	ret = gpio_request(LED, "LED"); 
	if(ret < 0)
	{
		pr_info("Request failed %d", ret);
		return -1;
	}

	gpio_direction_output(LED, 0);
	gpio_set_value(LED, 1);

	timer_setup(&timer_blink, blink_callback, 0);
	mod_timer(&timer_blink, jiffies + msecs_to_jiffies(blink_time));
	
	return 0;
}

static void __exit exit_ledblinking(void)
{
	gpio_set_value(LED, 0);
	gpio_free(LED);
	del_timer(&timer_blink);
}

module_init(init_ledblinking);
module_exit(exit_ledblinking);

