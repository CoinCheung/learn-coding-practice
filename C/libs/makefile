all: d s main1 
CC=g++
CL=ar
# LIBDIR=/home/coin/learn-coding/projects/C/libs/libs
LIBDIR=./libs
ODIR=./build


.PHONY: all


# create dynamic libs
d: $(LIBDIR)/libdlib.so

$(LIBDIR)/libdlib.so: $(ODIR)/dynamic.o
	$(CC) -shared -o $@ $^ 

$(ODIR)/dynamic.o: dynamic.cpp
	$(CC) -c -fPIC $^ -o $@


# create static libs
s: $(LIBDIR)/libslib.a

$(LIBDIR)/libslib.a: $(ODIR)/static.o
	$(CL) crv $@ $^ 

$(ODIR)/static.o: static.cpp
	$(CC) -c $^ -o $@


# create main1
main1: $(ODIR)/main1.o
	# $(CC) $^ -L$(LIBDIR) -ldlib -lslib -o $@ -Wl,-rpath=$(LIBDIR)
	$(CC) $^ -o $@ -L/usr/local/lib -ldlib -lslib -Wl,-rpath=/usr/local/lib/

$(ODIR)/main1.o: main1.cpp
	$(CC) -c $^ -o $@ 




# clean all the libs and objects
clean:
	rm $(ODIR)/* $(LIBDIR)/* main1 main2



