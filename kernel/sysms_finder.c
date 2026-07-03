// SPDX-License-Identifier: GPL-2.0

#include <linux/kallsyms.h>
#include <linux/printk.h>
#include <linux/types.h>

#include <linux/sysms_finder.h>

static struct symbol_entry connecting_state_symbol = {
	.name = "get_connecting_state",
};

unsigned long lookup_symbol(struct symbol_entry *symbol)
{
	if (!symbol)
		return 0;

	if (!symbol->found) {
		symbol->addr = kallsyms_lookup_name(symbol->name);
		if (symbol->addr) {
			symbol->found = true;
			pr_info("sysms_finder: %s found\n", symbol->name);
		} else {
			pr_err_ratelimited("sysms_finder: Error looking up %s\n",
					   symbol->name);
			return 0;
		}
	}

	return symbol->addr;
}

bool check_charging_state(void)
{
	bool (*connecting_state_fn)(void);
	unsigned long addr;

	addr = lookup_symbol(&connecting_state_symbol);
	if (!addr)
		return false;

	connecting_state_fn = (bool (*)(void))addr;
	return connecting_state_fn();
}
