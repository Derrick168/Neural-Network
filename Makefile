CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = obj

SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/NeuralNetwork.cpp $(SRCDIR)/Matrix.cpp
HEADERS = $(INCDIR)/NeuralNetwork.hpp $(INCDIR)/Matrix.hpp $(INCDIR)/Activation.hpp
OBJECTS = $(OBJDIR)/main.o $(OBJDIR)/NeuralNetwork.o $(OBJDIR)/Matrix.o
TARGET = $(BINDIR)/neural_network.exe

all: $(TARGET)

$(BINDIR):
	-@mkdir $(BINDIR) 2>nul

$(OBJDIR):
	-@mkdir $(OBJDIR) 2>nul

$(TARGET): $(OBJDIR) $(BINDIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/NeuralNetwork.o: $(SRCDIR)/NeuralNetwork.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/Matrix.o: $(SRCDIR)/Matrix.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	-@rmdir /s /q $(OBJDIR) 2>nul
	-@rmdir /s /q $(BINDIR) 2>nul

run: $(TARGET)
	@$(TARGET)

.PHONY: all clean run
