# Definitions for constants
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++
CFLAGS = -I.

# This will create your final output using .o compiled files
make: main.o game.o resource_manager.o
	$(CC) $(CFLAGS) -o main main.o game.o resource_manager.o $(LIBS)

main.o: main.cpp game.hpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

game.o: game.cpp game.hpp
	$(CC) $(CFLAGS) -c game.cpp -o game.o

resource_manager.o: resource_manager.cpp resource_manager.hpp
	$(CC) $(CFLAGS) -c resource_manager.cpp -o resource_manager.o

# This will clean or remove compiled files so you can start fresh
clean:
	rm -f *.o *.exe gamedev/*.o
