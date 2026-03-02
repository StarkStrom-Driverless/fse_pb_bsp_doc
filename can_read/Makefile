BINARY = bp_test
 

OBJS += main.o
OBJS += $(patsubst %.c, %.o, $(wildcard usr/src/*.c))



TGT_CPPFLAGS	+= -Iusr/inc

all: $(BINARY)


gdb:
	gdb-multiarch --tui -silent -x 'fse_pb_bsp/tools/gdbinit' -iex 'set auto-load safe-path /'

include fse_pb_bsp/Makefile.rtos
include fse_pb_bsp/Makefile
include fse_pb_bsp/tools/Makefile.include
include fse_pb_bsp/tools/rules.mk
