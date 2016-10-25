# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g --ansi --pedantic -Wall

# the build target executable:
TARGET = calc
TARGET2 = format
RM = rm -rf
all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).c

debug:
	$(CC) $(CFLAGS) -DDEBUG -o $(TARGET) $(TARGET).c
	$(CC) $(CFLAGS) -DDEBUG -o $(TARGET2) $(TARGET2).c

clean:
	$(RM) $(TARGET) $(TARGET).o
	$(RM) $(TARGET2) $(TARGET2).o
