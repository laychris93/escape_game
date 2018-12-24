OBJS = game_main.o Space.o Prisoner.o YourCell.o Cell.o Armory.o Escape.o Hall.o Hospital.o WardenOffice.o Utilities.o Game.o Item.o 
MAIN = jailbreak
CC = g++
STD = -std=c++0x
DEBUG = -g
CFLAGS = -Wall -pedantic-errors -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)



$(MAIN) : $(OBJS)
	$(CC) $(STD) $(LFLAGS) $(OBJS) -o $(MAIN)

game_main.o : game_main.cpp Game.hpp
	$(CC) $(STD) $(CFLAGS) game_main.cpp

Game.o : Game.cpp Game.hpp Prisoner.hpp Armory.hpp Cell.hpp YourCell.hpp Escape.hpp Hall.hpp Hospital.hpp WardenOffice.hpp Item.hpp Utilities.hpp
	$(CC) $(STD) $(CFLAGS) Game.cpp

Armory.o : Armory.cpp Armory.hpp Space.hpp 
	$(CC) $(STD) $(CFLAGS) Armory.cpp

Cell.o : Cell.cpp Cell.hpp Space.hpp 
	$(CC) $(STD) $(CFLAGS) Cell.cpp

YourCell.o : YourCell.cpp YourCell.hpp Space.hpp 
	$(CC) $(STD) $(CFLAGS) YourCell.cpp

Escape.o : Escape.cpp Escape.hpp Space.hpp 
	$(CC) $(STD) $(CFLAGS) Escape.cpp

Hall.o : Hall.cpp Hall.hpp Space.hpp 
	$(CC) $(STD) $(CFLAGS) Hall.cpp

Hospital.o : Hospital.cpp Hospital.hpp Space.hpp 
	$(CC) $(STD) $(CFLAGS) Hospital.cpp

WardenOffice.o : WardenOffice.cpp WardenOffice.hpp Space.hpp 
	$(CC) $(STD) $(CFLAGS) WardenOffice.cpp

Space.o : Space.cpp Space.hpp Prisoner.hpp Item.hpp Utilities.hpp
	$(CC) $(STD) $(CFLAGS) Space.cpp

Item.o : Item.cpp Item.hpp 
	$(CC) $(STD) $(CFLAGS) Item.cpp

Prisoner.o : Prisoner.cpp Prisoner.hpp  
	$(CC) $(STD) $(CFLAGS) Prisoner.cpp

Utilities.o : Utilities.cpp Utilities.hpp
	$(CC) $(STD) $(CFLAGS) Utilities.cpp

clean :
	$(RM) $(MAIN) *.o *~

