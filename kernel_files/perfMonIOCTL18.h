#ifndef QUERY_IOCTL_H
#define QUERY_IOCTL_H
#include <linux/ioctl.h>


#define PERF_MON_READ _IOR('q', 1, unsigned long *)
#define PERF_MON_RESET _IO('q', 2)
#define PERF_MON_ENABLE _IO('q', 3)
#define PERF_MON_DISABLE _IO('q', 4)
#define PERF_MON_EVENT_OPEN _IOR('q', 5, unsigned long *)

#endif
