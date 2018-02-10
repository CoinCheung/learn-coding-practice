CppC = g++
CFLAGs = -c -g
# LFLAGs
ODIR = ./build
_OBJs = main.o

OBJs = $(patsubst %.o, $(ODIR)/%.o, $(_OBJs))


main: $(OBJs)
	$(CppC) -o $@ $^

$(ODIR)/%.o: %.cpp
	$(CppC) -o $@ $< $(CFLAGs)


clean:
	rm main $(ODIR)/*
