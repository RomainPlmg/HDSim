CXX = g++
EXEC = HDSim

SOURCEDIR = ./src/
BUILDDIR = ./build/
TESTDIR = ./tests/

SRC = $(wildcard $(SOURCEDIR)*.cpp)
TEST = $(wildcard $(TESTDIR)*cpp)

OBJ = $(patsubst $(SOURCEDIR)%.cpp, $(BUILDDIR)%.o, $(SRC))

CXXFLAGS = -Iinclude -O3 -std=c++2a
LDFLAGS = -Wall

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)%.o : $(SOURCEDIR)%.cpp $(BUILDDIR)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

test_lexer : $(TESTDIR)test_lexer.cpp $(SOURCEDIR)lexer.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

test_parser : $(TESTDIR)test_parser.cpp $(SOURCEDIR)lexer.cpp $(SOURCEDIR)parser.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

test_write : $(TESTDIR)test_write_result.cpp $(SOURCEDIR)write_wave.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

test_simu : $(TESTDIR)test_simu.cpp $(SOURCEDIR)write_wave.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(BUILDDIR) :
	mkdir -p $(BUILDDIR)

clean :
	rm -rf $(EXEC) $(BUILDDIR) test_*
