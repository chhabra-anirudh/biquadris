# Compiler and flags
CXX = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g

# Name of the final executable
Executable = a4q1

# Source and object files 
SourceFiles = position.cc position-impl.cc \
              block.cc cell.cc cell-impl.cc block-impl.cc\
              iblock.cc iblock-impl.cc jblock.cc jblock-impl.cc \
              lblock.cc lblock-impl.cc oblock.cc oblock-impl.cc \
              sblock.cc sblock-impl.cc tblock.cc tblock-impl.cc \
              zblock.cc zblock-impl.cc starblock.cc starblock-impl.cc \
              observer.cc observer-impl.cc subject.cc subject-impl.cc \
              level.cc level-impl.cc level0.cc level0-impl.cc \
              level1.cc level1-impl.cc level2.cc level2-impl.cc \
              level3.cc level3-impl.cc level4.cc level4-impl.cc \
              board.cc board-impl.cc player.cc player-impl.cc \
              commandinterpreter.cc specialAction.cc specialAction-impl.cc


ObjectFiles = position.o position-impl.o \
              block.o block-impl.o cell.o cell-impl.o \
              iblock.o iblock-impl.o jblock.o jblock-impl.o \
              lblock.o lblock-impl.o oblock.o oblock-impl.o \
              sblock.o sblock-impl.o tblock.o tblock-impl.o \
              zblock.o zblock-impl.o starblock.o starblock-impl.o \
              observer.o observer-impl.o subject.o subject-impl.o \
              level.o level-impl.o level0.o level0-impl.o \
              level1.o level1-impl.o level2.o level2-impl.o \
              level3.o level3-impl.o level4.o level4-impl.o \
              board.o board-impl.o player.o player-impl.o \
              commandinterpreter.o specialAction.o specialAction-impl.o

# Default target
all: $(Executable)

# Precompile system headers
precompile:
	@mkdir -p gcm.cache
	$(CXX) $(CXXFLAGS) -c -x c++-system-header iostream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header fstream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header sstream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header vector
	$(CXX) $(CXXFLAGS) -c -x c++-system-header utility
	$(CXX) $(CXXFLAGS) -c -x c++-system-header algorithm
	$(CXX) $(CXXFLAGS) -c -x c++-system-header memory
	$(CXX) $(CXXFLAGS) -c -x c++-system-header string

# Rule to convert .cc → .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking step
$(Executable): precompile $(ObjectFiles)
	$(CXX) $(CXXFLAGS) $(ObjectFiles) -o $(Executable)

# Clean
.PHONY: clean
clean:
	rm -f $(Executable) *.o
	rm -rf gcm.cache
