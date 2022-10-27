#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h> 
#include <linux/slab.h>
#include <linux/list.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

/* Module entry point */

int waysLinkedList_init(void) {

/* Creating each birthday struct in list */

	printk(KERN_INFO "Creating birthday list\n");

	struct birthday *way;
	way = kmalloc(sizeof(*way), GFP_KERNEL);
	way->day = 3;
	way->month = 8;
	way->year = 2000;
	INIT_LIST_HEAD(&way->list);
	list_add_tail(&way->list, &birthday_list);

	struct birthday *chen;
	chen = kmalloc(sizeof(*chen), GFP_KERNEL);
	chen->day = 1;
	chen->month = 1;
	chen->year = 1911;
	INIT_LIST_HEAD(&chen->list);
	list_add_tail(&chen->list, &birthday_list);

	struct birthday *pi;
	pi = kmalloc(sizeof(*pi), GFP_KERNEL);
	pi->day = 31;
	pi->month = 5;
	pi->year = 1987;
	INIT_LIST_HEAD(&pi->list);
	list_add_tail(&pi->list, &birthday_list);

	struct birthday *angel;
	angel = kmalloc(sizeof(*angel), GFP_KERNEL);
	angel->day = 3;
	angel->month = 3;
	angel->year = 1988;
	INIT_LIST_HEAD(&angel->list);
	list_add_tail(&angel->list, &birthday_list);

	struct birthday *bell;
	bell = kmalloc(sizeof(*bell), GFP_KERNEL);
	bell->day = 20;
	bell->month = 6;
	bell->year = 1477;
	INIT_LIST_HEAD(&bell->list);
	list_add_tail(&bell->list, &birthday_list);

/* Traversing the list */

	printk(KERN_INFO "Traversing birthday list\n");

	struct birthday *ptr;

	list_for_each_entry(ptr, &birthday_list, list) {
		printk(KERN_INFO "BIRTHDAY: Month: %d Day: %d Year: %d\n", 
			ptr->month, 
			ptr->day,
			ptr->year);
	}

	return 0;
}

/* Module exit point */

void waysLinkedList_exit(void) {

	printk(KERN_INFO "Removing module\n");

/* Removes each struct from list */
        struct birthday *ptr,*next;
	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		printk(KERN_INFO "REMOVING BIRTHDAY: Month: %d Day: %d Year: %d\n",
			ptr->month,
			ptr->day,
			ptr->year);

		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Register module entry/exit pts */

module_init(waysLinkedList_init);
module_exit(waysLinkedList_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Way's friends' bro birthdays");
MODULE_AUTHOR("108590033");
