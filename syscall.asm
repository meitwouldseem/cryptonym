global system_enter
global syscall_wrapper

;SYSEXIT will restore EIP and ESP from
;EDX and ECX respectively. We set them
;here but the kernel will need to take
;steps to preserve them.
system_enter:
	mov eax, [esp+4]
	mov ecx, esp
	mov edx, .exitpoint
	sysenter
.exitpoint:
	ret

;once we get here we are in kernel space.
;the first thing we do is push edx & ecx
;onto our brand new kernelspace stack
;so as to ptotect them from the kernel function.
syscall_wrapper:
	push edx
	push ecx

	;we need interupts here
	sti

	;we are forced to use a generic sysenter
	;entrypoint due to the MSR that dictates
	;the entrypoint only being writable from
	;ring 0
	;it is system_enter's job to put the address
	;of the desired kernel function in eax

	call eax

	;cdecl returns values in EAX. All we
	;need to do to pass the return value
	;from the kernel func to userspace is
	;not touch EAX
	;EAX should also survive sysexit so
	;no black magic needed there

	pop ecx
	pop edx

	sysexit

;TODO: add argument support to syscalls
