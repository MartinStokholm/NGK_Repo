SOURCES=client.cpp

EXE=client
CXXFLAGS=-I. -g
LDFLAGS=-lncurses 
GOOGLETEST_LDFLAGS=-lgtest_main -lgtest -lpthread

ARCH?=x86-64
# Making for x86 -64 e.g. x86 -64 (the architecture employed)
# > make ARCH=x86 -64
ifeq (${ARCH},x86-64)
CXX=g++
BUILD_DIR=build/x86-64
EXE_DIR=bin/x86-64
endif
# Making for architecture
# > make ARCH=arm
ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR=build/arm
EXE_DIR=bin/arm
endif


#Following variables define where the files .o and .d are placed
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))

#Following variables define where the files .o and .d are placed
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))

#Default target
all: $(EXE_DIR)/$(EXE)

#BUILD_DIR specifies which directory to put the files
$(EXE_DIR)/$(EXE): $(DEPS) $(OBJECTS) #Exe depends on .d files and .o files
	$(call Print_Titel,Linking)	
	$(call Print_Command,$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)) 
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)
	$(call Change_Colour,$(NO_COLOUR))

#Create -o files (from .cpp files), give them their target name ($@) and compile them
#from their first dependency ($<) which is .cpp that happens to include .h(pp) and etc 
$(BUILD_DIR)/%.o:%.cpp
	$(call Print_Titel,Creating .o from .cpp)
	$(call Print_Command,$(CXX) -o $@ -c $< $(CXXFLAGS))
	@$(CXX) -o $@ -c $< $(CXXFLAGS) 
	$(call Change_Colour, $(NO_COLOUR))
	
# Rule that describes how a .d (dependency) file is created from a .cpp file
# Similar to the assigment that you just completed %.cpp -> %.o

$(BUILD_DIR)/%.d:%.cpp
# mkdir -p creates folders, if they are missing, and does not though errors if they exits
	$(call Print_Titel,Creating .d from .cpp)
	$(call Change_Colour,$(BLUE))
	mkdir -p $(BUILD_DIR) 
	mkdir -p $(EXE_DIR)
	$(call Print_Command,$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@)
	@$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@ 
	$(call Print_Command,$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@)
	@$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS)  $< >> $@
	$(call Change_Colour,$(NO_COLOUR))

ifneq ($(filter-out clean format tidy, $(MAKECMDGOALS)),)
 -include $(DEPS)
endif

clean: 
	$(call Print_Titel,CLEAN)
	@printf "$(BLUE)"
	rm -f $(OBJECTS)
	rm -f $(DEPS)
	@printf "$(NO_COLOUR)"

format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@
	
tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tidying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@
#Line 31 creates rule for .o files' dependencies inside a .d file
#Line 30 creates rule for .d files' dependencies inside a .d file
#Line 25-26 creates rule for generating .o files

# ---- functions ---- 

Print_Titel=@echo "$(BLUE)--$1--$(NO_COLOUR)"
Print_Command=@echo "$(BLUE)$1$(RED)"
Change_Colour=@printf "$1"


# ---- colours -----
NO_COLOUR=\033[0m
BLACK=\033[0;30m
DARKGRAY=\033[1;30m
RED=\033[0;31m
LIGHT_RED=\033[1;31m
GREEN=\033[0;32m
LIGHT_GREEN=\033[1;32m
BROWN_ORANGE=\033[0;33m
YELLOW=\033[1;33m
BLUE=\033[0;34m
LIGHT_BLUE=\033[1;34m
PURPLE=\033[0;35m
LIGHT_PURPLE=\033[1;35m
CYAN=\033[0;36m
LIGHT_CYAN=\033[1;36m
LIGHT_GRAY=\033[0;37m
WHITE=\033[1;37m


