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
	$(CC) -c main.c

utils.o: utils.c
	$(CC) -c utils.c

input.o: input.c
	$(CC) -c input.c

wqunion.o: wqunion.c
	$(CC) -c wqunion.c

maxsubarray.o: maxsubarray.c
	$(CC) -c maxsubarray.c

arrayutils.o: arrayutils.c
	$(CC) -c arrayutils.c

arraysort.o: arraysort.c
	$(CC) -c arraysort.c

listsort.o: listsort.c dllist.h
	$(CC) -c listsort.c

dllist.o: dllist.c
	$(CC) -c dllist.c

clean:
	rm -f $(OBJFILES) $(BINARY)
