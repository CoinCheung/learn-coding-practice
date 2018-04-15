SRCs = $(wildcard *cpp)
OBJs = $(patsubst %.cpp, %.o, $(SRCs))

$(OBJs): %.o: %.cpp
	@mkdir -p $(ODIR)
	$(CPP) $(CFLAGs) $< -o $(ODIR)/$@
