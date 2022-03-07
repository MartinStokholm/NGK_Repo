# This make file supports multiple sources and dependencies
# and will compile to either 64-bit or ARM
SOURCES=*.cpp
OBJ=$(SOURCES:.cpp=.o)
EXE=measurement_server

$(EXE): $(SOURCES)
	$(CXX) -o $@ $^