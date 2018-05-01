# Definitions for constants
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++
CFLAGS = -I. -std=c++11 -g

# This will create your final output using .o compiled files
make: main.o game.o resource_manager.o state_machine.o main_menu_state.o play_state.o game_over_state.o entity.o entity_manager.o
	$(CC) $(CFLAGS) -o main main.o game.o resource_manager.o state_machine.o main_menu_state.o play_state.o game_over_state.o entity.o entity_manager.o $(LIBS)

main.o: main.cpp include/game.hpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

game.o: game.cpp include/game.hpp
	$(CC) $(CFLAGS) -c game.cpp -o game.o

resource_manager.o: resource_manager.cpp include/resource_manager.hpp
	$(CC) $(CFLAGS) -c resource_manager.cpp -o resource_manager.o

state_machine.o: state_machine.cpp include/state_machine.hpp
	$(CC) $(CFLAGS) -c state_machine.cpp -o state_machine.o

main_menu_state.o: main_menu_state.cpp include/main_menu_state.hpp
	$(CC) $(CFLAGS) -c main_menu_state.cpp -o main_menu_state.o

play_state.o: play_state.cpp include/play_state.hpp
	$(CC) $(CFLAGS) -c play_state.cpp -o play_state.o

game_over_state.o: game_over_state.cpp include/game_over_state.hpp
	$(CC) $(CFLAGS) -c game_over_state.cpp -o game_over_state.o

entity.o: entity.cpp include/entity.hpp
	$(CC) $(CFLAGS) -c entity.cpp -o entity.o

entity_manager.o: entity_manager.cpp include/entity_manager.hpp
	$(CC) $(CFLAGS) -c entity_manager.cpp -o entity_manager.o

# This will clean or remove compiled files so you can start fresh
clean:
	rm -f *.o *.exe gamedev/*.o
