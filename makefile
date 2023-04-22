CC = g++
CPPLAGS = -Iinclude -g
EXC = main
OBJDIR = obj
SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)



all: $(EXC)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -o $@ -c $< $(CPPLAGS)

$(OBJDIR)/main.o: main.cpp
	$(CC) -o $@ -c $< $(CPPLAGS)

$(EXC): $(OBJ) $(OBJDIR)/main.o
	echo "Compilation avec succes !, Pour executer tapez $(EXC)"
	$(CC) -o $@ $^

clean:
	rm -rf $(OBJDIR)/*.o $(EXC)

.PHONY: clean all