CXXFLAGS = -Wall
DEPS = oiseaux.h      //Dans DEPS il faut mettre tous les fichiers .h
OBJ = main.o oiseaux.o oiseaux.o      //Dans OBJ, il faut mettre tous les fichiers .cpp en remplaçant .cpp par .o

excute: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)
	./execute

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CXXFLAGS)
