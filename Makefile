TARGET	= ggsample08
SOURCES	= $(wildcard *.cpp)
HEADERS	= $(wildcard *.h)
OBJECTS	= $(patsubst %.cpp,%.o,$(SOURCES))
CXXFLAGS	= --std=c++17 -g -Wall -DDEBUG -DX11 -Iinclude
LDLIBS	= -Llib -lglfw3_linux -lGL -lXrandr -lXinerama -lXcursor -lXi -lX11 -lpthread -lrt -lm -ldl

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(TARGET).dep: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -MM $(SOURCES) > $@

clean:
	-$(RM) $(TARGET) *.o *~ .*~ *.bak *.dep a.out core

-include $(TARGET).dep
