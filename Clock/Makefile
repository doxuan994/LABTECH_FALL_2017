# Makefile for the clock project
#
# Darren Provine, 17 July 2009

PROGRAM = clock
SOURCES = clock.c model.c view.c
OBJECTS = clock.o model.o view.o
DRIVERS = LEDisplay.o
INCLUDE = -I/usr/lib/gcc/x86_64-redhat-linux/3.4.6/include
LIBRARY = -lncurses
CFLAGS  = -O -Wall
COMPILER= gcc

.SUFFIXES:
.SUFFIXES: .c .o

.c.o: ; $(COMPILER) $(CFLAGS) -c $< $(INCLUDE)

$(PROGRAM) : $(OBJECTS)
	$(COMPILER) -o $(PROGRAM) $(CFLAGS) $(OBJECTS) $(DRIVERS) $(LIBRARY)

clean: ; /bin/rm -f $(PROGRAM) $(OBJECTS) core

depend: $(SOURCES)
	@ echo
	@ echo "NOTE: Ignore message about byteswap.h"
	@ echo
	makedepend $(INCLUDE) $(SOURCES)


# DO NOT DELETE

clock.o: clock.h /usr/include/sys/time.h /usr/include/features.h
clock.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
clock.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
clock.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
clock.o: /usr/include/time.h /usr/include/bits/time.h
clock.o: /usr/include/sys/select.h /usr/include/bits/select.h
clock.o: /usr/include/bits/sigset.h /usr/include/stdio.h
clock.o: /usr/lib/gcc/x86_64-redhat-linux/3.4.6/include/stddef.h
clock.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
clock.o: /usr/lib/gcc/x86_64-redhat-linux/3.4.6/include/stdarg.h
clock.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
clock.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
clock.o: /usr/include/bits/confname.h /usr/include/signal.h
clock.o: /usr/include/bits/signum.h /usr/include/bits/sigaction.h
clock.o: /usr/include/bits/sigcontext.h /usr/include/stdlib.h
clock.o: /usr/include/sys/types.h /usr/include/endian.h
clock.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
clock.o: /usr/include/bits/byteswap-16.h /usr/include/sys/sysmacros.h
clock.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h LEDisplay.h
clock.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/ncurses.h
clock.o: /usr/include/ncurses_dll.h /usr/include/stdint.h
clock.o: /usr/include/bits/wchar.h /usr/include/unctrl.h
clock.o: /usr/include/curses.h /usr/include/term.h /usr/include/termios.h
clock.o: /usr/include/bits/termios.h /usr/include/sys/ttydefaults.h
model.o: clock.h /usr/include/sys/time.h /usr/include/features.h
model.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
model.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
model.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
model.o: /usr/include/time.h /usr/include/bits/time.h
model.o: /usr/include/sys/select.h /usr/include/bits/select.h
model.o: /usr/include/bits/sigset.h /usr/include/stdio.h
model.o: /usr/lib/gcc/x86_64-redhat-linux/3.4.6/include/stddef.h
model.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
model.o: /usr/lib/gcc/x86_64-redhat-linux/3.4.6/include/stdarg.h
model.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
model.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
model.o: /usr/include/bits/confname.h /usr/include/signal.h
model.o: /usr/include/bits/signum.h /usr/include/bits/sigaction.h
model.o: /usr/include/bits/sigcontext.h /usr/include/stdlib.h
model.o: /usr/include/sys/types.h /usr/include/endian.h
model.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
model.o: /usr/include/bits/byteswap-16.h /usr/include/sys/sysmacros.h
model.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h LEDisplay.h
model.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/ncurses.h
model.o: /usr/include/ncurses_dll.h /usr/include/stdint.h
model.o: /usr/include/bits/wchar.h /usr/include/unctrl.h
model.o: /usr/include/curses.h /usr/include/term.h /usr/include/termios.h
model.o: /usr/include/bits/termios.h /usr/include/sys/ttydefaults.h
view.o: clock.h /usr/include/sys/time.h /usr/include/features.h
view.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
view.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
view.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
view.o: /usr/include/time.h /usr/include/bits/time.h
view.o: /usr/include/sys/select.h /usr/include/bits/select.h
view.o: /usr/include/bits/sigset.h /usr/include/stdio.h
view.o: /usr/lib/gcc/x86_64-redhat-linux/3.4.6/include/stddef.h
view.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
view.o: /usr/lib/gcc/x86_64-redhat-linux/3.4.6/include/stdarg.h
view.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
view.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
view.o: /usr/include/bits/confname.h /usr/include/signal.h
view.o: /usr/include/bits/signum.h /usr/include/bits/sigaction.h
view.o: /usr/include/bits/sigcontext.h /usr/include/stdlib.h
view.o: /usr/include/sys/types.h /usr/include/endian.h
view.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
view.o: /usr/include/bits/byteswap-16.h /usr/include/sys/sysmacros.h
view.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h LEDisplay.h
view.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/ncurses.h
view.o: /usr/include/ncurses_dll.h /usr/include/stdint.h
view.o: /usr/include/bits/wchar.h /usr/include/unctrl.h /usr/include/curses.h
view.o: /usr/include/term.h /usr/include/termios.h
view.o: /usr/include/bits/termios.h /usr/include/sys/ttydefaults.h
