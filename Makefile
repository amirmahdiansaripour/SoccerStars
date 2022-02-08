CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

soccerStars.out: main.o rsdl.o field.o game_element.o team.o controller.o
	$(CC) main.o rsdl.o field.o game_element.o team.o controller.o $(CCFLAGS) -o soccerStars.out

main.o: RSDL/src/rsdl.hpp definitions.hpp controller.hpp main.cpp
	$(CC) -c main.cpp -o main.o
	
rsdl.o: RSDL/src/rsdl.hpp RSDL/src/rsdl.cpp
	$(CC) -c RSDL/src/rsdl.cpp -o rsdl.o

game_element.o: RSDL/src/rsdl.hpp definitions.hpp team.hpp game_element.hpp game_element.cpp
	$(CC) -c game_element.cpp -o game_element.o
	
team.o:  RSDL/src/rsdl.hpp definitions.hpp game_element.hpp team.hpp team.cpp
	$(CC) -c team.cpp -o team.o

field.o: RSDL/src/rsdl.hpp definitions.hpp game_element.hpp team.hpp field.hpp field.cpp
	$(CC) -c field.cpp -o field.o

controller.o: RSDL/src/rsdl.hpp definitions.hpp game_element.hpp team.hpp field.hpp controller.hpp controller.cpp
	$(CC) -c controller.cpp -o controller.o


.PHONY: clean
clean:
	rm -r *.o
