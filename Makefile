DEBUG = 1

CC = gcc
CFLAGS = -g -Wall -Werror -std=c99 -Iinclude
LDFLAGS = $(shell pkg-config --cflags --libs sdl3) -lpng -lz

SRCDIR = src
OBJDIR = obj
LIBSDIR = third_party
BIN = main

INCLUDES := $(shell find $(LIBSDIR) -type d -name include)
CFLAGS += $(patsubst %, -I%, $(INCLUDES))

SRCS := $(wildcard $(SRCDIR)/*.c) $(wildcard $(LIBSDIR)/*/src/*.c)

OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

ifeq ($(DEBUG),1)
	CFLAGS += -g -O0
endif

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BIN)

.PHONY: all clean

