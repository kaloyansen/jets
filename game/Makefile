INC_DIR  = include
SRC_DIR  = src
OBJ_DIR  = obj
CXXFLAGS = $(CXX_FLAGS)
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0
OLDFLAGS = -std=c++17 -I. -I$(INC_DIR)
VERYOLDFLAGS = -std=c99
CXXLIBS  = -lncurses -ltinfo

SRCS     = $(SRC_DIR)/*.cpp
OBJS     = $(OBJ_DIR)/*.o
LIBS     =
TARGET   = game

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX_COMP) $(CXXFLAGS) -o $@ -c $<

$(TARGET):	$(OBJS)
	$(CXX_COMP) $(CXXLIBS) -o $@ $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -fv $(OBJS)

clobber:	clean
	rm -f $(TARGET)

new:	clobber all

version:
	$(CXX_COMP) --version;$(CXX_COMP) -dumpversion
	