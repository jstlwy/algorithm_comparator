CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = 
OBJFILES = input.o sort.o main.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)
