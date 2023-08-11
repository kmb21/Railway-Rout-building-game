# Configure compiler settings
CXX=clang++
CXXFLAGS=-gdwarf-4 -std=c++11 -Werror -D_GLIBCXX_DEBUG
# The object files for the program.
OFILES = \
	stringUtils.o \
	goal.o \
	player.o \
	gui/cpipe.o \
	gui/subprocess.o \
	gui/dataReader.o \
	gui/dataWriter.o \
	gui/railwayDataReader.o \
	gui/railwayDataWriter.o \
	railwayGUI.o \
	ioUtils.o \
	railwayGame.o
	
# The header files for the program
HFILES = $(shell ls -1 *.h gui/*.h)

# unittest++ keeps its object files in this library.
UNITTEST_LIB = -lUnitTest++

TEST_DATA_LOCATION = "/usr/local/doc/lab09-data/"

all: railway tests manualTests

# This target ensures that the data for the main program is available.
test_data/:
	ln -s $(TEST_DATA_LOCATION) test_data

# This target builds your main program.
railway: $(HFILES) $(OFILES) main.o test_data/
	$(CXX) $(CXXFLAGS) -o $@ main.o $(OFILES)


# This target builds your tests.
tests: tests.o ioUtils.o stringUtils.o $(HFILES) test_data/
	$(CXX) $(CXXFLAGS) -o $@ tests.o ioUtils.o stringUtils.o $(UNITTEST_LIB)

# This target builds your manual testing program.
manualTests: manualTests.o $(HFILES) $(OFILES) test_data/
	$(CXX) $(CXXFLAGS) -o $@ manualTests.o $(OFILES)

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp $(HFILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# This target deletes the temporary files we have built.
.PHONY: clean
clean:
	rm -f *.o
	rm -f gui/*.o
	rm -f railway
	rm -f tests
	rm -f manualTests
