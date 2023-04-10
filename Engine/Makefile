########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++ 
# CXXFLAGS = -std=c++17 -g -Wall -Werror -I./include
CXXFLAGS = -std=c++17 -g -I./include -I./external/box2d/include -I./external/lua_win_32/include
LDFLAGS = -lmingw32 -lSDL2main -L./external/lib -lSDL2_mixer -lSDL2 -L./external/box2d/build/bin/Release -lbox2d -Wl,-rpath,.
LUA_LIB_DIR = ./external/lua_win_32
LDFLAGS += -L$(LUA_LIB_DIR) -llua54

# SDL2 settings
SDL2_INCLUDE_DIR = ./external/SDL

# Makefile settings - Can be customized.
APPNAME = finalProject
EXT = .cpp
SRCDIR = src
EXTERNALDIR = external
OBJDIR = obj
DEPDIR = dep

# Include directories
INCLUDES = -I$(SDL2_INCLUDE_DIR) -I./external/json/single_include/nlohmann -I./external/box2d/include -I./core/ -I./ecs -I./ecs/subsystem -I./ecs/component -I./ecs/module -I./io

# Compiler flags
CXXFLAGS += $(INCLUDES)

############## Do not change anything from here downwards! #############
# SRC = $(wildcard $(SRCDIR)/*$(EXT) $(EXTERNALDIR)/box2d/src/collision/*$(EXT) $(EXTERNALDIR)/box2d/src/common/*$(EXT) $(EXTERNALDIR)/box2d/src/dynamics/*$(EXT) $(EXTERNALDIR)/box2d/src/rope/*$(EXT))
SRC = $(wildcard $(SRCDIR)/*$(EXT) $(EXTERNALDIR)/box2d/src/collision/*$(EXT) $(EXTERNALDIR)/box2d/src/common/*$(EXT) $(EXTERNALDIR)/box2d/src/dynamics/*$(EXT) $(EXTERNALDIR)/box2d/src/dynamics/contacts/*$(EXT) $(EXTERNALDIR)/box2d/src/dynamics/joints/*$(EXT) $(EXTERNALDIR)/box2d/src/rope/*$(EXT))
# OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
# OBJ = $(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)$(CC) $(CXXFLAGS) -c -o $@ $< -MD -MP -MF $(DEPDIR)/$*.d
OBJ = $(patsubst $(SRCDIR)/%$(EXT),$(OBJDIR)/%.o,$(patsubst $(EXTERNALDIR)/box2d/%$(EXT),$(OBJDIR)/box2d/%.o,$(SRC)))
DEP = $(patsubst $(SRCDIR)/%$(EXT),$(DEPDIR)/%.d,$(patsubst $(EXTERNALDIR)/box2d/%$(EXT),$(DEPDIR)/box2d/%.d,$(SRC)))
# DEP = $(patsubst $(SRCDIR)/%$(EXT),$(DEPDIR)/%.d,$(SRC))
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
# %.d: $(SRCDIR)/%$(EXT)
# 	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

$(DEPDIR)/%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@
	
$(DEPDIR)/box2d/%.d: $(EXTERNALDIR)/box2d/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:$(DEPDIR)/box2d/%.d=$(OBJDIR)/box2d/%.o) >$@

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/box2d/%.o: $(EXTERNALDIR)/box2d/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<
# Includes all .h files
-include $(DEP)
# Includes all .d files
# -include $(wildcard $(DEPDIR)/*.d)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/box2d/%.o:
	mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(DEPDIR)/box2d/%.d:
	mkdir -p $(@D)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:$(DEPDIR)/box2d/%.d=$(OBJDIR)/box2d/%.o) >$@


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
	$(DEL) $(DEP)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)