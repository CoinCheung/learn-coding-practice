CPP = g++
ODIR = ./build
CFLAGs = -c -g $(shell pkg-config --cflags opencv) 
LFLAGs = $(shell pkg-config --libs opencv) -ltcmalloc 
_OBJs = main.o ConnectedDomain.o grayscale.o


OBJs = $(patsubst %.o, $(ODIR)/%.o, $(_OBJs))


try: $(ODIR)/try.o
	$(CPP) -o $@ $^ $(LFLAGs)
$(ODIR)/try.o: try.cpp
	$(CPP) -o $@ $< $(CFLAGs) 


main: $(OBJs)
	$(CPP) -o $@ $^ $(LFLAGs)

# compile objects
$(ODIR)/%.o: %.cpp
	@mkdir -p $(ODIR)
	$(CPP) -o $@ $< $(CFLAGs) 






clean:
	rm -rf ./build/ main


