CPP = g++
ODIR = ./build
CFLAGS = -c -O2
LFLAGS =
_OBJS = list.o main.o

OBJS = $(patsubst %.o, $(ODIR)/%.o, $(_OBJS))


main: $(OBJS)
	$(CPP) $(LFLAGS) $^ -o $@

$(ODIR)/%.o: %.cpp
	@mkdir -p $(ODIR)
	$(CPP) $^ -o $@ $(CFLAGS)


clean:
	rm -rf $(ODIR) main

