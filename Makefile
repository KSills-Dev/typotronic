CXX=g++
CXXFLAGS=-std=c++11

all: typo/typo
	cp typo/typo run

typo/typo: typo/costs.o typo/io.o typo/layout.o typo/typo.o typo/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

typo/%.o: typo/%.cpp typo/%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f typo/*.o typo/typo run
