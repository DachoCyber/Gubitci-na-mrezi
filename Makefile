CC = g++
CFLAGS = -Wall -Wextra -g
TARGET = a
SRC = main.cpp mreza.cpp
OBJ = $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
