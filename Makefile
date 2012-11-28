EXECUTABLE := peng
LIBRARY    := libpeng.a
VPATH      += src lib
CXXFLAGS   += -Wall -Werror -I include
LDFLAGS    += -Wall -Werror -lfbxsdk-2013.3

.PHONY: all clean

all: $(EXECUTABLE)

clean:
	rm -f *.o *.d $(EXECUTABLE) $(LIBRARY)

$(EXECUTABLE): $(patsubst src/%.cpp, %.o, $(wildcard src/*.cpp)) $(LIBRARY)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(LIBRARY): $(patsubst lib/%.cpp, %.o, $(wildcard lib/*.cpp))
	$(AR) rcs $@ $^

%.src.d: src/%.cpp
	$(CXX) $(CXXFLAGS) -MM $< > $@

%.lib.d: lib/%.cpp
	$(CXX) $(CXXFLAGS) -MM $< > $@

ifneq ($(MAKECMDGOALS),clean)
-include $(patsubst src/%.cpp, %.src.d, $(wildcard src/*.cpp))
-include $(patsubst lib/%.cpp, %.lib.d, $(wildcard lib/*.cpp))
endif
