CXX = g++
CXXFLAGS = -std=c++11 -O2
TARGET = test
REPORT = report.pdf

all: $(TARGET)

$(TARGET): test.cpp HeapSort.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) test.cpp

report: report.tex
	xelatex report.tex

clean:
	rm -f $(TARGET) *.aux *.log *.pdf