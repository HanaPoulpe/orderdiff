CXX=clang++
CXXFLAGS=-std=c++17 -O3
LDFLAGS=
EXEC=./bin/orderdiff
INSTALLDIR=/usr/bin/
SRCDIR=./src/

SRC=$(wildcard ./src/*.cpp)

OBJ = $(SRC:.cpp=.o)


all: $(OBJ) $(EXEC)

./bin/orderdiff: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

install: $(EXEC)
	cp ./bin/* $(INSTALLDIR)

%.o: %.c
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -r src/*.o

mrproper: clean
	rm -rf $(EXEC)

