OS := $(shell uname)
ifeq ($(OS), Darwin)
CC := clang
LDFLAGS := -lncurses
else
CC := gcc
LDFLAGS := -lncurses -lpthread -lbsd
endif

CFLAGS := -std=c17 -Wall -Wextra -Werror -pedantic -MMD -MP

.PHONY: all clean print

srcdir := ./src
objdir := ./obj
exclude := $(srcdir)/rbtree.c
src := $(filter-out $(exclude), $(wildcard $(srcdir)/*.c))
hdr := $(wildcard $(srcdir)/*.h)
obj := $(patsubst $(srcdir)/%.c, $(objdir)/%.o, $(src))
dep := $(obj:.o=.d)

vpath %.c $(srcdir)

binary := algorithm_comparator

all: $(binary)

$(binary): $(obj)
	$(CC) $^ -o $@ $(LDFLAGS)

$(objdir)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

-include $(dep)

clean:
	rm -f $(obj) $(binary) $(dep)
