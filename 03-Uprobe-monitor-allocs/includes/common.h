#ifndef __UPROBE_COMMON_H__
#define __UPROBE_COMMON_H__

enum event_type {
	EVENT_TYPE_ALLOCATION,
	EVENT_TYPE_FREE,
};

struct event {
	__u32 pid;
	enum event_type type;
	__u64 size;
};

#endif // __UPROBE_COMMON_H__