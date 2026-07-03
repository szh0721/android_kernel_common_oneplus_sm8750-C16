/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SYSMS_FINDER_H
#define _LINUX_SYSMS_FINDER_H

#include <linux/types.h>

struct symbol_entry {
	const char *name;
	unsigned long addr;
	bool found;
};

unsigned long lookup_symbol(struct symbol_entry *symbol);
bool check_charging_state(void);

#endif /* _LINUX_SYSMS_FINDER_H */
