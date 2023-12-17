CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD 
OBJECTS = BA.o Entity.o Potion.o Barrier.o Floor.o RH.o BD.o Goblin.o Small_horde.o Cell.o Human.o Treasure.o Chamber.o Merchant.o Troll.o Compass.o Merchant_horde.o Vampire.o Dragon.o Normal_horde.o WA.o Dragon_horde.o Orc.o WD.o Dwarf.o PH.o Werewolf.o Elf.o Phoenix.o Enemy.o Player.o Item.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = a3q4

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o 

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

