#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

void prep_sysenter(uint32_t esp, uint32_t eip);
uint32_t system_enter(uint32_t addr);

//wrappers should not be called directly! only
//passed to prep_sysenter
void syscall_wrapper();

#endif
