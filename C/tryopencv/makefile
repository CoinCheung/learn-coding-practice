CC = g++
ODIR = ./build
_OBJs = tryopencv.o
CFLAGs = -c -g $(shell pkg-config --cflags opencv)
LFLAGs = $(shell pkg-config --libs opencv) -ltcmalloc

OBJs = $(patsubst %.o, $(ODIR)/%.o, $(_OBJs))

main: $(OBJs)
	$(CC) -o $@ $^ $(LFLAGs)

$(ODIR)/%.o: %.cpp %.h
	$(CC) -o $@ $< $(CFLAGs) 

clean:
	rm $(ODIR)/* main


