
# g++ -c makelib.cpp -o makelib.o
# ar rsc libmakelib.a makelib.o
#
# gcc -c try.c -o try.o -I./
# g++ try.o -o try -lmakelib -L./
#
# rm *o



g++ -c -fPIC makelib.cpp -o makelib.o
g++ -shared makelib.o -o libmakelib.so

gcc -c try.c -o try.o -I./
gcc try.o -o try -lmakelib -L./

rm *.o
