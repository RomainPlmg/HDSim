CXX = g++
EXEC = main

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

$(BUILDDIR)%.o : $(SOURCEDIR)%.cpp $(BUILDDIR)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

<<<<<<< HEAD
test_lexer : $(TESTDIR)test_lexer.cpp $(SOURCEDIR)lexer.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

test_parser : $(TESTDIR)test_parser.cpp $(SOURCEDIR)lexer.cpp $(SOURCEDIR)parser.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(EXEC) $(OBJDIR) test_lexer test_parser
