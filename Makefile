CXX = g++
EXEC = main

SOURCEDIR = ./src/
OBJDIR = ./obj/
TESTDIR = ./tests/

SRC = $(wildcard $(SOURCEDIR)*.cpp)

OBJ = $(patsubst $(SOURCEDIR)%.cpp, $(OBJDIR)%.o, $(SRC))

CXXFLAGS = -I./include
LDFLAGS = -Wall

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o : $(SOURCEDIR)%.cpp $(OBJDIR)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

test_linked_list : $(TESTDIR)test_linked_list.cpp $(SOURCEDIR)lexer.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(EXEC) $(OBJDIR) test_linked_list
	@echo $(TESTOBJ)