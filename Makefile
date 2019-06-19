CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
OBJFILES = input.o sort.o main.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)
