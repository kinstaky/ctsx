# NOTE: this is a GNU Makefile.  You must use "gmake" rather than "make".
#
# Makefile for the network assignment
#    Defines set up assuming this assignment is done last 
#    If not, use the "bare bones"  defines below. 
#
# Copyright (c) 1992 The Regents of the University of California.
# All rights reserved.  See copyright.h for copyright notice and limitation 
# of liability and disclaimer of warranty provisions.

DEFINES = -DUSER_PROGRAM -DVM -DFILESYS_NEEDED -DFILESYS -DNETWORK
INCPATH = -I../network -I../bin -I../filesys -I../vm -I../userprog -I../threads -I../machine
HFILES = $(THREAD_H) $(USERPROG_H) $(VM_H) $(FILESYS_H) $(NETWORK_H)
CFILES = $(THREAD_C) $(USERPROG_C) $(VM_C) $(FILESYS_C) $(NETWORK_C)
C_OFILES = $(THREAD_O) $(USERPROG_O) $(VM_O) $(FILESYS_O) $(NETWORK_O)

# bare bones version
# DEFINES =-DTHREADS -DNETWORK
# INCPATH = -I../network -I../threads -I../machine
# HFILES = $(THREAD_H) $(NETWORK_H)
# CFILES = $(THREAD_C) $(NETWORK_C)
# C_OFILES = $(THREAD_O) $(NETWORK_O)

include ../Makefile.common
include ../Makefile.dep
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
main.o: ../threads/main.cc /usr/x86_64-linux-gnu/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../threads/bool.h \
 ../machine/sysdep.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../threads/utility.h \
 ../machine/translate.h ../machine/disk.h ../threads/list.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../network/post.h ../machine/network.h \
 ../threads/synchlist.h ../threads/synch.h
list.o: ../threads/list.cc /usr/x86_64-linux-gnu/include/stdc-predef.h \
 ../threads/copyright.h ../threads/list.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h
scheduler.o: ../threads/scheduler.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/scheduler.h ../threads/list.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/system.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../network/post.h \
 ../machine/network.h ../threads/synchlist.h ../threads/synch.h
synch.o: ../threads/synch.cc /usr/x86_64-linux-gnu/include/stdc-predef.h \
 ../threads/copyright.h ../threads/synch.h ../threads/thread.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 ../threads/copyright.h /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../machine/machine.h \
 ../threads/utility.h ../machine/translate.h ../machine/disk.h \
 ../threads/list.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/list.h ../threads/system.h ../threads/scheduler.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h
synchlist.o: ../threads/synchlist.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/synchlist.h ../threads/list.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/synch.h \
 ../threads/thread.h ../machine/machine.h ../threads/utility.h \
 ../machine/translate.h ../machine/disk.h ../threads/list.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h
system.o: ../threads/system.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/system.h ../threads/utility.h ../threads/bool.h \
 ../machine/sysdep.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h
thread.o: ../threads/thread.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/thread.h ../threads/utility.h ../threads/bool.h \
 ../machine/sysdep.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../machine/machine.h \
 ../threads/utility.h ../machine/translate.h ../machine/disk.h \
 ../threads/list.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/switch.h ../threads/synch.h ../threads/list.h \
 ../threads/system.h ../threads/scheduler.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../network/post.h \
 ../machine/network.h ../threads/synchlist.h
utility.o: ../threads/utility.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 ../threads/copyright.h /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/stdarg.h
threadtest.o: ../threads/threadtest.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/system.h ../threads/utility.h ../threads/bool.h \
 ../machine/sysdep.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h ../machine/elevatortest.h
interrupt.o: ../machine/interrupt.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../machine/interrupt.h ../threads/list.h ../threads/copyright.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../threads/utility.h \
 ../machine/translate.h ../machine/disk.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h
sysdep.o: ../machine/sysdep.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h \
 /usr/x86_64-linux-gnu/include/signal.h \
 /usr/x86_64-linux-gnu/include/bits/signum.h \
 /usr/x86_64-linux-gnu/include/bits/signum-generic.h \
 /usr/x86_64-linux-gnu/include/bits/types/sig_atomic_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/sigset_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__sigset_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_timespec.h \
 /usr/x86_64-linux-gnu/include/bits/types/siginfo_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__sigval_t.h \
 /usr/x86_64-linux-gnu/include/bits/siginfo-arch.h \
 /usr/x86_64-linux-gnu/include/bits/siginfo-consts.h \
 /usr/x86_64-linux-gnu/include/bits/siginfo-consts-arch.h \
 /usr/x86_64-linux-gnu/include/bits/types/sigval_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/sigevent_t.h \
 /usr/x86_64-linux-gnu/include/bits/sigevent-consts.h \
 /usr/x86_64-linux-gnu/include/bits/sigaction.h \
 /usr/x86_64-linux-gnu/include/bits/sigcontext.h \
 /usr/x86_64-linux-gnu/include/bits/types/stack_t.h \
 /usr/x86_64-linux-gnu/include/sys/ucontext.h \
 /usr/x86_64-linux-gnu/include/bits/sigstack.h \
 /usr/x86_64-linux-gnu/include/bits/ss_flags.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_sigstack.h \
 /usr/x86_64-linux-gnu/include/bits/pthreadtypes.h \
 /usr/x86_64-linux-gnu/include/bits/thread-shared-types.h \
 /usr/x86_64-linux-gnu/include/bits/pthreadtypes-arch.h \
 /usr/x86_64-linux-gnu/include/bits/sigthread.h \
 /usr/x86_64-linux-gnu/include/sys/types.h \
 /usr/x86_64-linux-gnu/include/bits/types/clock_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/clockid_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/time_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/timer_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdint-intn.h \
 /usr/x86_64-linux-gnu/include/endian.h \
 /usr/x86_64-linux-gnu/include/bits/endian.h \
 /usr/x86_64-linux-gnu/include/bits/byteswap.h \
 /usr/x86_64-linux-gnu/include/bits/uintn-identity.h \
 /usr/x86_64-linux-gnu/include/sys/select.h \
 /usr/x86_64-linux-gnu/include/bits/select.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_timeval.h \
 /usr/x86_64-linux-gnu/include/sys/time.h \
 /usr/x86_64-linux-gnu/include/sys/socket.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_iovec.h \
 /usr/x86_64-linux-gnu/include/bits/socket.h \
 /usr/x86_64-linux-gnu/include/bits/socket_type.h \
 /usr/x86_64-linux-gnu/include/bits/sockaddr.h \
 /usr/x86_64-linux-gnu/include/asm/socket.h \
 /usr/x86_64-linux-gnu/include/asm-generic/socket.h \
 /usr/x86_64-linux-gnu/include/asm/sockios.h \
 /usr/x86_64-linux-gnu/include/asm-generic/sockios.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_osockaddr.h \
 /usr/x86_64-linux-gnu/include/sys/file.h \
 /usr/x86_64-linux-gnu/include/fcntl.h \
 /usr/x86_64-linux-gnu/include/bits/fcntl.h \
 /usr/x86_64-linux-gnu/include/bits/fcntl-linux.h \
 /usr/x86_64-linux-gnu/include/linux/falloc.h \
 /usr/x86_64-linux-gnu/include/bits/stat.h \
 /usr/x86_64-linux-gnu/include/sys/un.h \
 /usr/x86_64-linux-gnu/include/sys/mman.h \
 /usr/x86_64-linux-gnu/include/bits/mman.h \
 /usr/x86_64-linux-gnu/include/bits/mman-linux.h \
 /usr/x86_64-linux-gnu/include/bits/mman-shared.h \
 /usr/x86_64-linux-gnu/include/unistd.h \
 /usr/x86_64-linux-gnu/include/bits/posix_opt.h \
 /usr/x86_64-linux-gnu/include/bits/environments.h \
 /usr/x86_64-linux-gnu/include/bits/confname.h \
 /usr/x86_64-linux-gnu/include/bits/getopt_posix.h \
 /usr/x86_64-linux-gnu/include/bits/getopt_core.h \
 /usr/x86_64-linux-gnu/include/errno.h \
 /usr/x86_64-linux-gnu/include/bits/errno.h \
 /usr/x86_64-linux-gnu/include/linux/errno.h \
 /usr/x86_64-linux-gnu/include/asm/errno.h \
 /usr/x86_64-linux-gnu/include/asm-generic/errno.h \
 /usr/x86_64-linux-gnu/include/asm-generic/errno-base.h \
 /usr/x86_64-linux-gnu/include/bits/types/error_t.h \
 ../machine/interrupt.h ../threads/list.h ../threads/copyright.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 ../threads/system.h ../threads/thread.h ../machine/machine.h \
 ../threads/utility.h ../machine/translate.h ../machine/disk.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../network/post.h ../machine/network.h \
 ../threads/synchlist.h ../threads/synch.h
stats.o: ../machine/stats.cc /usr/x86_64-linux-gnu/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../machine/stats.h
timer.o: ../machine/timer.cc /usr/x86_64-linux-gnu/include/stdc-predef.h \
 ../threads/copyright.h ../machine/timer.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/system.h \
 ../threads/utility.h ../threads/thread.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../threads/list.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../network/post.h ../machine/network.h \
 ../threads/synchlist.h ../threads/synch.h
elevatortest.o: ../machine/elevatortest.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../machine/elevatortest.h ../machine/elevator.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/list.h \
 ../threads/utility.h ../threads/synch.h ../threads/thread.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/list.h \
 ../threads/thread.h
elevator.o: ../machine/elevator.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../machine/elevator.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/list.h \
 ../threads/utility.h ../threads/system.h ../threads/thread.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../network/post.h ../machine/network.h \
 ../threads/synchlist.h ../threads/synch.h
prischeduler.o: ../threads/prischeduler.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/scheduler.h \
 ../threads/copyright.h ../threads/list.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/system.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../network/post.h \
 ../machine/network.h ../threads/synchlist.h ../threads/synch.h
addrspace.o: ../userprog/addrspace.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/system.h ../threads/copyright.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h ../userprog/addrspace.h ../bin/noff.h
bitmap.o: ../userprog/bitmap.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../userprog/bitmap.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../filesys/openfile.h
exception.o: ../userprog/exception.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/system.h ../threads/copyright.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h ../userprog/syscall.h
progtest.o: ../userprog/progtest.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/system.h ../threads/copyright.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h ../machine/console.h ../userprog/addrspace.h
console.o: ../machine/console.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../machine/console.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/system.h \
 ../threads/utility.h ../threads/thread.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../threads/list.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../network/post.h ../machine/network.h \
 ../threads/synchlist.h ../threads/synch.h
machine.o: ../machine/machine.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../machine/machine.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../threads/utility.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../network/post.h ../machine/network.h \
 ../threads/synchlist.h ../threads/synch.h
mipssim.o: ../machine/mipssim.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../machine/machine.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../threads/utility.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../machine/mipssim.h \
 ../threads/system.h ../threads/thread.h ../machine/machine.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../network/post.h \
 ../machine/network.h ../threads/synchlist.h ../threads/synch.h
translate.o: ../machine/translate.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../machine/machine.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../threads/utility.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../network/post.h ../machine/network.h \
 ../threads/synchlist.h ../threads/synch.h
pageschedule.o: ../machine/pageschedule.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../machine/machine.h \
 ../threads/copyright.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../threads/utility.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/system.h \
 ../threads/thread.h ../machine/machine.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../network/post.h ../machine/network.h \
 ../threads/synchlist.h ../threads/synch.h
directory.o: ../filesys/directory.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/utility.h ../threads/copyright.h ../threads/bool.h \
 ../machine/sysdep.h /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../filesys/filehdr.h \
 ../machine/disk.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/directory.h ../filesys/openfile.h
filehdr.o: ../filesys/filehdr.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/system.h ../threads/copyright.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h ../filesys/filehdr.h
filesys.o: ../filesys/filesys.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../machine/disk.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../filesys/directory.h ../filesys/openfile.h \
 ../filesys/filehdr.h ../filesys/filesys.h
fstest.o: ../filesys/fstest.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/utility.h ../threads/copyright.h ../threads/bool.h \
 ../machine/sysdep.h /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/system.h ../threads/utility.h \
 ../threads/thread.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
 ../machine/stats.h ../machine/timer.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../network/post.h \
 ../machine/network.h ../threads/synchlist.h ../threads/synch.h \
 ../threads/thread.h
openfile.o: ../filesys/openfile.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../filesys/filehdr.h ../machine/disk.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../filesys/openfile.h ../threads/system.h \
 ../threads/utility.h ../threads/thread.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../threads/list.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../threads/scheduler.h \
 ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
 ../machine/timer.h ../filesys/synchdisk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h
synchdisk.o: ../filesys/synchdisk.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/synch.h \
 ../threads/thread.h ../threads/utility.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../threads/list.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/list.h
disk.o: ../machine/disk.cc /usr/x86_64-linux-gnu/include/stdc-predef.h \
 ../threads/copyright.h ../machine/disk.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/system.h \
 ../threads/utility.h ../threads/thread.h ../machine/machine.h \
 ../machine/translate.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h
nettest.o: ../network/nettest.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/system.h ../threads/copyright.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h ../network/post.h
post.o: ../network/post.cc /usr/x86_64-linux-gnu/include/stdc-predef.h \
 ../threads/copyright.h ../network/post.h ../machine/network.h \
 ../threads/utility.h ../threads/copyright.h ../threads/bool.h \
 ../machine/sysdep.h /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/synchlist.h \
 ../threads/list.h ../threads/utility.h ../threads/synch.h \
 ../threads/thread.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h
network.o: ../machine/network.cc \
 /usr/x86_64-linux-gnu/include/stdc-predef.h ../threads/copyright.h \
 ../threads/system.h ../threads/copyright.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h \
 /usr/x86_64-linux-gnu/include/stdio.h \
 /usr/x86_64-linux-gnu/include/bits/libc-header-start.h \
 /usr/x86_64-linux-gnu/include/features.h \
 /usr/x86_64-linux-gnu/include/sys/cdefs.h \
 /usr/x86_64-linux-gnu/include/bits/wordsize.h \
 /usr/x86_64-linux-gnu/include/bits/long-double.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs.h \
 /usr/x86_64-linux-gnu/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h ../threads/stdarg.h \
 /usr/x86_64-linux-gnu/include/bits/types.h \
 /usr/x86_64-linux-gnu/include/bits/typesizes.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__mbstate_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__fpos64_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/struct_FILE.h \
 /usr/x86_64-linux-gnu/include/bits/types/cookie_io_functions_t.h \
 /usr/x86_64-linux-gnu/include/bits/stdio_lim.h \
 /usr/x86_64-linux-gnu/include/bits/sys_errlist.h \
 /usr/x86_64-linux-gnu/include/string.h \
 /usr/x86_64-linux-gnu/include/bits/types/locale_t.h \
 /usr/x86_64-linux-gnu/include/bits/types/__locale_t.h \
 /usr/x86_64-linux-gnu/include/strings.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../threads/list.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../threads/list.h \
 ../machine/interrupt.h ../machine/stats.h ../machine/timer.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../network/post.h ../machine/network.h ../threads/synchlist.h \
 ../threads/synch.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
