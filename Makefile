CXXFLAGS = -Wall -lsfml-graphics -lsfml-window -lsfml-system
DEPS = fonctions.h obstacle.h cercle.h oiseaux3.h
OBJ = main3.o fonctions.o obstacle.o cercle.o oiseaux3.o

execute: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)
	./execute

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CXXFLAGS)
