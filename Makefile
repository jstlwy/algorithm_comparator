CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = 
OBJFILES = input.o utils.o arraysort.o linklist.o llsort.o main.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)
