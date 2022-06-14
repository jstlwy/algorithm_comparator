CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS = -lncurses
OBJFILES = input.o utils.o arraysort.o arrayutils.o dllist.o listsort.o maxsubarray.o wqunion.o main.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)
