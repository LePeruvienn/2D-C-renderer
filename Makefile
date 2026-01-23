CC = gcc
CFLAGS = -Wall -Werror -std=c99 -Iinclude $(shell pkg-config --cflags sdl3) $(shell pkg-config --cflags gl)
LDFLAGS = $(shell pkg-config --libs sdl3) $(shell pkg-config --libs gl)

SRCDIR = src
OBJDIR = obj
BIN = main

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BIN)


.PHONY: clean
