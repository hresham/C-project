# Define the compiler
CC=gcc

# Define the compiler flags
CFLAGS=-Wall -g

# Define the target executable name
TARGET=rotormachine

# Define the source files
SRC=Resham_Hrishi_assn3.c rotorMachine.c

# Define the object files (source files with .o extension)
OBJ=$(SRC:.c=.o)

# Default target
all:$(TARGET)

# Rule to link object files and create the executable
$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the directory (remove object files and the executable)
clean:
	rm -f $(OBJ) $(TARGET)