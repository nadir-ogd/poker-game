CC = g++
CPPLAGS = -Wall -Iinclude -g
LDFLAGS = -O3
EXC = main
OBJDIR = obj
SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)



all: $(EXC)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -o $@ -c $< $(CPPLAGS) $(LDFLAGS)
 
$(OBJDIR)/main.o: main.cpp
	$(CC) -o $@ -c $< $(CPPLAGS) $(LDFLAGS)

$(EXC): $(OBJ) $(OBJDIR)/main.o
	echo "Compilation avec succes !, Pour executer tapez $(EXC)"
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)/*.o $(EXC)

.PHONY: clean all