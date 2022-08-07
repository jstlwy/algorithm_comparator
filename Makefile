CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -l ncurses
FILENAMES = arraysort arrayutils dllist listsort maxsubarray wqunion input utils
OBJFILES = main.o $(foreach name, $(FILENAMES), $(name).o)
HEADERS = $(foreach name, $(FILENAMES), $(name).h)
BINARY = algorithm_comparator

# ncurses used in:
# main
# utils
# input
# arrayutils
# dllist

all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LDFLAGS) -o $(BINARY)

main.o: main.c $(HEADERS)
	$(CC) -c $<

utils.o: utils.c
	$(CC) -c $<

input.o: input.c
	$(CC) -c $<

wqunion.o: wqunion.c
	$(CC) -c $<

maxsubarray.o: maxsubarray.c
	$(CC) -c $<

arrayutils.o: arrayutils.c
	$(CC) -c $<

arraysort.o: arraysort.c
	$(CC) -c $<

listsort.o: listsort.c dllist.h
	$(CC) -c $<

dllist.o: dllist.c
	$(CC) -c $<

clean:
	rm -f $(OBJFILES) $(BINARY)
