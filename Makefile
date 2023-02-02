CXXFLAGS = -Wall -lsfml-graphics -lsfml-window -lsfml-system
DEPS = fonctions.h obstacle.h oiseaux.f
OBJ = main.o fonctions.o obstacle.o oiseaux.o

mon_super_programme: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)
	./execute

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CXXFLAGS)
