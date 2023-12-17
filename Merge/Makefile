CXX = g++
CXXFLAGS = -std=c++14  -g -Wall -MMD 
# disable note: -fcompare-debug-second 
# -W NO WARNING
DEPENDS = ${OBJECTS:.o=.d}
OBJECTS = BA.o  Compass.o Item.o Enemy.o  Interpreter.o    PH.o  Small_horde.o    WD.o BD.o  Dragon.o Entity.o Merchant.o Phoenix.o  Treasure.o Werewolf.o Barrier.o  Dragon_horde.o   Floor.o  Merchant_horde.o Player.o Troll.o Cell.o   Dwarf.o  Goblin.o Normal_horde.o   Potion.o Vampire.o Chamber.o  Elf.o    Human.o  Orc.o    RH.o  WA.o main.o
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

