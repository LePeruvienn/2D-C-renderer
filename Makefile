CC = gcc
CFLAGS = -Wall -Werror -std=c99 -Iinclude $(shell pkg-config --cflags sdl3)
LDFLAGS = $(shell pkg-config --libs sdl3)

SRCDIR = src
OBJDIR = obj
LIBSDIR = third_party
BIN = main

INCLUDES := $(shell find $(LIBSDIR) -type d -name include)
CFLAGS += $(patsubst %, -I%, $(INCLUDES))

SRCS := $(wildcard $(SRCDIR)/*.c) $(wildcard $(LIBSDIR)/*/src/*.c)

OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BIN)

.PHONY: all clean

