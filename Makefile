CXX = g++
EXEC = main

EXECDIR = ./exe/
SOURCEDIR = ./src/
BUILDDIR = ./build/
TESTDIR = ./tests/

SRC = $(wildcard $(SOURCEDIR)*.cpp)
TEST = $(wildcard $(TESTDIR)*cpp)

OBJ = $(patsubst $(SOURCEDIR)%.cpp, $(BUILDDIR)%.o, $(SRC))
OBJ += $(patsubst $(TESTDIR)%.cpp, $(BUILDDIR)%.o, $(TEST))

CXXFLAGS = -I./include
LDFLAGS = -Wall

all : $(EXEC) $(TEST)

$(EXEC) : $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)%.o : $(SOURCEDIR)%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	rm -rf $(OBJ) $(EXEC) build/