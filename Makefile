EXE := genetic-image
SRC := $(shell find src/ -type f -name '*.cpp')
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)
CXX := g++

CPPFLAGS := -MMD -MP
CXXFLAGS := -std=c++14 -Wall -W -pedantic
LDLIBS   := -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ $(LDLIBS) -o $(EXE)

clean:
	$(RM) $(EXE) $(OBJ) $(DEP)

ifeq "$(MAKECMDGOALS)" ""
-include $(DEP)
endif
