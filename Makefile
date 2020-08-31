#
# Makefile
#
CC := arm-linux-gnueabihf-gcc-9.1.0
LVGL_DIR ?= ${shell pwd}
LVGL_DIR_NAME ?= lvgl

#WARNINGS = -Werror -Wall -Wextra \
#           -Wshadow -Wundef -Wmaybe-uninitialized -Wmissing-prototypes -Wpointer-arith -Wuninitialized \
#           -Wunreachable-code -Wreturn-type -Wmultichar -Wformat-security -Wdouble-promotion -Wclobbered -Wdeprecated  \
#           -Wempty-body -Wstack-usage=2048 \
#           -Wtype-limits -Wsizeof-pointer-memaccess

#-Wno-unused-value -Wno-unused-parameter 
OPTIMIZATION ?= -O3 -g0

CFLAGS ?= -I$(LVGL_DIR)/ $(DEFINES) $(WARNINGS) $(OPTIMIZATION) -I$(LVGL_DIR) -I.
CFLAGS += -Ilv_examples/
CFLAGS += -Ilv_drivers/display/
CFLAGS += -Ilv_drivers/indev/

BIN ?= demo

#Collect the files to compile
MAINSRC = test.c

include lvgl/lvgl.mk
include lv_examples/lv_examples.mk
include lv_drivers/lv_drivers.mk

CSRCS += sstar_port.c

OBJEXT ?= .o
OBJDIR = obj

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))
MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
#OBJS = $(patsubst %, $(OBJDIR)/%, $(notdir $(AOBJS) $(COBJS) $(MAINOBJ)))
OBJS = $(AOBJS) $(COBJS) $(MAINOBJ)

## MAINOBJ -> OBJFILES

all: $(OBJDIR) default

%.o: %.c
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo CC $<
    
default: $(OBJS)
	@$(CC) -o $(BIN) $(OBJS) $(LDFLAGS)
	@echo "------------------------------------------------"
	@echo "> Finish!!!"
	@echo "> CC  = $(CC)"
	@echo "> BIN = $(BIN)"
	@echo "------------------------------------------------"

clean: 
	@rm -f $(BIN) $(OBJS)
	@rm -fd $(OBJDIR)
	@echo "clean"

$(OBJDIR):
	mkdir -p $@

