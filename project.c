#include <linux/module.h>
#include <linux/kernel.h>   
#include <linux/init.h>     
#include <linux/list.h>    
#include <linux/types.h>    
#include <linux/slab.h>     

LIST_HEAD(birthday_list);

typedef struct _birthday {
    int day;
    int month;
    int year;
    struct list_head list;
}birthday;

int birthdayList_init(void) {
    printk(KERN_INFO "Loading Module\n");
    birthday *person;
    int i = 0;
    for(i = 0; i < 5; i++) {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = 2 + i*2;
        person->month = 1 + i*2;
        person->year = 1995 + i*2;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
    }
    list_for_each_entry(person, &birthday_list, list) {
        printk(KERN_INFO "Birthday: Day:%d Month:%d Year:%d\n",
                person->day,
                person->month,
                person->year);
    }
    return 0;
}

void birthdayList_exit(void) {
    printk(KERN_INFO "Removing Module\n");
    birthday *person, *next;
    list_for_each_entry_safe(person, next, &birthday_list, list) {

        printk(KERN_INFO "Removing Birthday: Day:%d Month:%d Year:%d\n",
                person->day,
                person->month,
                person->year);
        list_del(&person->list);
        kfree(person);
    
    }
}

module_init(birthdayList_init);
module_exit(birthdayList_exit);
