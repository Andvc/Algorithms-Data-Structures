# Makefile for Expression Evaluator

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = evaluator
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean

report:
	xelatex report.tex