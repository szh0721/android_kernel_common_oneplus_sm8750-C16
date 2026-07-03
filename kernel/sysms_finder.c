// SPDX-License-Identifier: GPL-2.0

#include <linux/kallsyms.h>
#include <linux/printk.h>
#include <linux/types.h>

#include <linux/sysms_finder.h>

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
