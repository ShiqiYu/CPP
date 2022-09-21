## VERSION 1
hello: main.cpp printhello.cpp  factorial.cpp
	g++ -o hello main.cpp printhello.cpp  factorial.cpp

# ## VERSION 2
# CC = g++
# TARGET = hello
# OBJ = main.o printhello.o factorial.o

# $(TARGET): $(OBJ)
# 	$(CC) -o $(TARGET) $(OBJ)

# main.o: main.cpp
# 	$(CC) -c main.cpp

# printhello.o: printhello.cpp
# 	$(CC) -c printhello.cpp

# factorial.o: factorial.cpp
# 	$(CC) -c factorial.cpp


# ## VERSION 3
# CC = g++
# TARGET = hello
# OBJ = main.o printhello.o factorial.o

# CFLAGS = -c -Wall

# $(TARGET): $(OBJ)
# 	$(CC) -o $@ $(OBJ)

# %.o: %.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# .PHONY: clean
# clean:
# 	rm -f *.o $(TARGET)


# ## VERSION 4
# CC = g++
# TARGET = hello
# SRC = $(wildcard *.cpp)
# OBJ = $(patsubst %.cpp, %.o, $(SRC))

# CFLAGS = -c -Wall

# $(TARGET): $(OBJ)
# 	$(CC) -o $@ $(OBJ)

# %.o: %.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# .PHONY: clean
# clean:
# 	rm -f *.o $(TARGET)