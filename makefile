CXX = g++
CXXFLAGS = -std=c++11 -g
NAME = gauntlet
SRCS = main.cpp game.cpp character.cpp
HEADERS = space.hpp game.hpp character.hpp item.hpp

gauntlet: ${SRCS} ${HEADERS}
	${CXX} ${SRCS} ${CXXFLAGS} -o ${NAME}

clean :
	-rm ${NAME}
