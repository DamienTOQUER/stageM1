CXXFLAGS=-Wall -Wno-sign-compare 
sources = main.cpp complex.cpp potential.cpp const.cpp initial.cpp opemath.cpp save.cpp fourier.cpp poly.cpp
entetes = complex.h potential.h const.h initial.h opemath.h save.h fourier.h poly.h
objets = $(sources:.cpp=.o)

%: %.o
	$(LINK.cpp) -o $@ $^
run: $(objets)
	g++ $^ -o $@ -lm -lgsl -lgslcblas
clean:
	rm -f *~ *.o *.bak
mrproper: clean
	rm -f run
depend:
	makedepend $(sources)
# DO NOT DELETE

complex.o: complex.h
potential.o: potential.h const.h
initial.o: const.h complex.h initial.h
fourier.o: complex.h fourier.h
