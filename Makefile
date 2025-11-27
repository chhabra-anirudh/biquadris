# ================================================================
# Biquadris Makefile
# ================================================================

CXX      = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts
LDFLAGS  = -lX11
TARGET   = biquadris

# Standard headers to precompile
STD_HEADERS = iostream fstream sstream vector utility algorithm memory cstdlib map iomanip ctime string

# All source files in order
SRCS = \
    position.cc position-impl.cc \
    block.cc block-impl.cc \
    iblock.cc iblock-impl.cc \
    jblock.cc jblock-impl.cc \
    lblock.cc lblock-impl.cc \
    oblock.cc oblock-impl.cc \
    sblock.cc sblock-impl.cc \
    zblock.cc zblock-impl.cc \
    tblock.cc tblock-impl.cc \
    starblock.cc starblock-impl.cc \
    observer.cc observer-impl.cc \
    subject.cc subject-impl.cc \
    board.cc board-impl.cc \
    level.cc level-impl.cc \
    level0.cc level0-impl.cc \
    level1.cc level1-impl.cc \
    level2.cc level2-impl.cc \
    level3.cc level3-impl.cc \
    level4.cc level4-impl.cc \
    player.cc player-impl.cc \
    textdisplay.cc textdisplay-impl.cc \
    commandinterpreter.cc commandinterpreter-impl.cc \
    xwindow.cc xwindow-impl.cc \
    graphicsdisplay.cc graphicsdisplay-impl.cc \
    game.cc game-impl.cc \
    main.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# ================================================================
# Default rule
# ================================================================
all: precompile $(TARGET)

# Precompile standard headers
precompile:
	@for header in $(STD_HEADERS); do \
		echo "Precompiling $$header..."; \
		echo "#include <$$header>" | $(CXX) $(CXXFLAGS) -x c++-system-header $$header; \
	done

# Link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile each source file
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Full reset
cleanall: clean
	rm -rf *.gcm gcm.cache

.PHONY: all clean cleanall precompile