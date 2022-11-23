CXXFLAGS = -Wall
DEPS = oiseaux.h      //Dans DEPS il faut mettre tous les fichiers .h
OBJ = main.o oiseaux.o oiseaux.o      //Dans OBJ, il faut mettre tous les fichiers .cpp en remplaçant .cpp par .o

mon_super_programme: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)
	./mon_super_programme

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CXXFLAGS)
