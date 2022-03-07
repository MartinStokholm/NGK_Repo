# This make file supports multiple sources and dependencies
# and will compile to either 64-bit or ARM
SOURCES=*.cpp
# variabels for .o and .d files
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))
# compiler flags
CXXFLAGS=-I.
# linker flags
LXXFLAGS=
# archiceture flag
ARCH=x86-64
# Making for x86-64 e.g. x86-64 (the architecture employed)
# > make ARCH=x86-64
ifeq (${ARCH},x86-64)
CXX=g++ -pthread
BUILD_DIR=build/x86-64
BIN_DIR=bin/x86-64
EXE=$(addprefix $(BIN_DIR)/,prog_file)
endif
# Making for architecture
# > make ARCH=arm
ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR=build/arm
BIN_DIR=bin/arm
EXE=$(addprefix $(BIN_DIR)/,prog_file)
endif
# build all
all: $(EXE)

# run prog file
run:
	./$(EXE)
# clean up
clean:
	rm -f $(EXE) $(OBJECTS) $(DEPS)
# create program file
$(EXE):$(DEPS) $(OBJECTS) $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)
# pattern matchin for .o to .cpp
$(BUILD_DIR)/%.o:%.cpp $(BUILD_DIR)
	$(CXX) -o $@ -c $< $(CXXFLAGS)
# pattern matching for .d to .cpp 
$(BUILD_DIR)/%.d:%.cpp $(BUILD_DIR)
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@
# rule for making dir for generated files
$(BUILD_DIR):
	mkdir -p $@
# rule for making dir for executable
$(BIN_DIR):
	mkdir -p $@
# tidy rule for good coding practice
tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tittying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@
# format rule for fixing bad code formating
format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@
# Added from listing 4.6 to make tidy and format work with rest
ifneq ($(filter-out clean format tidy, $(MAKECMDGOALS)),)
-include $(DEPS)
endif
