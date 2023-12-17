CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD 
OBJECTS = BA.o            Merchant.o        Small_horde.o Barrier.o       Merchant_horde.o  Treasure.o BD.o            Normal_horde.o    WA.o Compass.o       PH.o              WD.o Dragon_horde.o  Potion.o Entity.o        RH.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = a3q4

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o 

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

