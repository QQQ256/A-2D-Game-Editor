########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++ 
# CXXFLAGS = -std=c++17 -g -Wall -Werror -I./include
CXXFLAGS = -std=c++17 -g -I./include
LDFLAGS = -lmingw32 -lSDL2main -lSDL2

# SDL2 settings
SDL2_INCLUDE_DIR = D:/EnvironmentVariables/SDL2-2.26.2/include

# Makefile settings - Can be customized.
APPNAME = finalProject
EXT = .cpp
SRCDIR = src
OBJDIR = obj
DEPDIR = dep

# Include directories
INCLUDES = -I$(SDL2_INCLUDE_DIR) -I./external/json/single_include/nlohmann -I./core/ -I./ecs -I./ecs/subsystem -I./ecs/component -I./ecs/module -I./io

# Compiler flags
CXXFLAGS += $(INCLUDES)

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
# OBJ = $(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)$(CC) $(CXXFLAGS) -c -o $@ $< -MD -MP -MF $(DEPDIR)/$*.d
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)
# Includes all .d files
# -include $(wildcard $(DEPDIR)/*.d)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)