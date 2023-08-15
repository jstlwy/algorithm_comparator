CC := gcc
CFLAGS := -Wall -Wextra -Werror

OS := $(shell uname)
ifeq ($(OS), Darwin)
LDFLAGS := -lncurses
else
LDFLAGS := -lncurses -lpthread -lbsd
endif

.PHONY: all clean print

srcdir := ./src
objdir := ./obj
exclude := $(srcdir)/pqueue.c
src := $(filter-out $(exclude), $(wildcard $(srcdir)/*.c))
headers := $(patsubst %.c, %.h, $(filter-out $(srcdir)/main.c, $(src)))
obj := $(patsubst $(srcdir)/%.c, $(objdir)/%.o, $(src))
binary := algorithm_comparator

all: $(binary)

$(binary): $(obj)
	$(CC) $(LDFLAGS) $^ -o $@

$(objdir)/main.o: $(srcdir)/main.c $(headers)
$(objdir)/arraysort.o: $(srcdir)/arraysort.c
$(objdir)/arrayutils.o: $(srcdir)/arrayutils.c
$(objdir)/dllist.o: $(srcdir)/dllist.c $(srcdir)/utils.h
$(objdir)/input.o: $(srcdir)/input.c
$(objdir)/listsort.o: $(srcdir)/listsort.c $(srcdir)/dllist.h
$(objdir)/maxsubarray.o: $(srcdir)/maxsubarray.c
$(objdir)/pqueue.o: $(srcdir)/pqueue.c
$(objdir)/utils.o: $(srcdir)/utils.c
$(objdir)/wqunion.o: $(srcdir)/wqunion.c
$(obj):
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(obj) $(binary)

print:
	@echo src: $(src)
	@echo headers: $(headers)
	@echo obj: $(obj)
