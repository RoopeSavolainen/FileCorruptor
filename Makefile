CXX = c++
STD = -std=c++11
IN = main.cpp
OUT = corrupt
CXXTAGS =
WARN = -Wall

build:	
	$(CXX) -g $(STD) $(WARN) $(IN) -o $(OUT)
