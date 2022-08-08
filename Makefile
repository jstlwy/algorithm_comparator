CC := gcc
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -lncurses
# ncurses used in:
# main
# utils
# input
# arrayutils
# dllist
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
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Generic object file creation rule
$(objdir)/%.o: $(srcdir)/%.c
	$(CC) -c $< -o $@

# Individual file prerequisites
$(objdir)/main.o: $(headers)
$(objdir)/utils.o: $(srcdir)/utils.h
$(objdir)/input.o: $(srcdir)/input.h
$(objdir)/wqunion.o: $(srcdir)/wqunion.h
$(objdir)/maxsubarray.o: $(srcdir)/maxsubarray.h
$(objdir)/arrayutils.o: $(srcdir)/arrayutils.h
$(objdir)/arraysort.o: $(srcdir)/arraysort.h
$(objdir)/listsort.o: $(srcdir)/listsort.h $(srcdir)/dllist.h
$(objdir)/dllist.o: $(srcdir)/dllist.h

clean:
	rm -f $(obj) $(binary)
