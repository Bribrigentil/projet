CXXFLAGS = -Wall
DEPS = truc.hpp bidule.hpp
OBJ = main.o truc.o bidule.o

mon_super_programme: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)
	./mon_super_programme

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CXXFLAGS)
