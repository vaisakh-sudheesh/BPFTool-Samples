#ifndef __UPROBE_COMMON_H__
#define __UPROBE_COMMON_H__

struct event {
	__u32 pid;
	int arg1;
	int arg2;
	int ret;
	char func_name[16];
};

#endif // __UPROBE_COMMON_H__