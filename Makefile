CC := gcc
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -lncurses

# Declare names that indicate recipes, not files 
.PHONY: all clean

srcdir := ./src
objdir := ./obj
exclude := $(srcdir)/pqueue.c
src := $(filter-out $(exclude), $(wildcard $(srcdir)/*.c))
headers := $(filter-out $(srcdir)/main.h, $(patsubst %.c, %.h, $(src)))
obj := $(patsubst $(srcdir)/%.c, $(objdir)/%.o, $(src))
binary := algorithm_comparator

all: $(binary)

$(binary): $(obj)
	$(CC) $(LDFLAGS) $^ -o $@

# Generic object file creation rule
$(objdir)/%.o: $(srcdir)/%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# If not using -MMD to automatically generate dependencies,
# the dependencies can be manually specified as follows:
#$(objdir)/main.o: $(headers)
#$(objdir)/listsort.o: $(srcdir)/listsort.h $(srcdir)/dllist.h

clean:
	rm -f $(obj) $(binary)
