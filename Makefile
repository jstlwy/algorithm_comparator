CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS = -lncurses
OBJFILES = input.o utils.o arraysort.o dllist.o listsort.o wqunion.o main.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)
