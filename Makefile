CXX = g++-5 -g
CXXFLAGS = -std=c++14  -MMD
EXEC = random
OBJECTS = generate_helper.o generate_floor.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
