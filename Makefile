CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -MMD
EXEC = biquadris
OBJECTS = main.o controller.o game.o textWindow.o graphicsWindow.o window.o block.o level.o level_0.o level_1.o level_2.o level_3.o level_4.o board.o cell.o lblock.o oblock.o sblock.o tblock.o zblock.o jblock.o iblock.o oneblock.o bombblock.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
