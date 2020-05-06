CPP = g++
ROOT = $(shell pwd)
ODIR = $(ROOT)/build
SUBDIRs = $(ROOT)/sub1 $(ROOT)/sub2
CFLAGs = -c -I$(ROOT)/sub1 -I$(ROOT)/sub2

CURR_SRCs = $(wildcard *.cpp)
CURR_OBJs = $(patsubst %.cpp, %.o, $(CURR_SRCs))
OBJs = $(wildcard $(ODIR)/*.o)

export CPP ROOT CFLAGs ODIR


main: $(CURR_OBJs) $(SUBDIRs)
	$(CPP) $(OBJs) -o $@


# $(SUBDIRs):  ECHO #这里必须有一个依赖 ECHO就可以，没有不行
$(SUBDIRs)::  
	$(MAKE) -C $@


$(CURR_OBJs): %.o: %.cpp
	@mkdir -p $(ODIR)
	$(CPP) $< -o $(ODIR)/$@ $(CFLAGs)

ECHO:
	@echo "ffff"

clean:
	rm -rf $(ODIR) main
