#ifndef __UPROBE_COMMON_H__
#define __UPROBE_COMMON_H__

enum event_type {
	EVENT_TYPE_ENTER,
	EVENT_TYPE_EXIT,
};

struct event {
	__u32 pid;
	enum event_type type;
	int arg1;
	int arg2;
	int ret;
	char func_name[16];
};

#endif // __UPROBE_COMMON_H__