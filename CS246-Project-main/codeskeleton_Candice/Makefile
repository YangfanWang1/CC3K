CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD 
DEPENDS = ${OBJECTS:.o=.d}
OBJECTS = Dragon.o Elf.o Goblin.o Merchant.o Phoenix.o Troll.o Werewolf.o Dwarf.o Enemy.o Human.o Orc.o Player.o Vampire.o
EXEC = a3q4

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o 

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

