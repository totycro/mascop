SRCDIR = src
OBJDIR = obj

GPP = ccache g++


STARTUP_SOURCE = $(SRCDIR)/main.cpp

CPP_SOURCES = \
	$(SRCDIR)/aircraftlanding.cpp \
	$(SRCDIR)/instance.cpp

DEBUG = 1

CXXFLAGS = -Wall -Wno-non-virtual-dtor -pipe
LDFLAGS =  -lgecodesearch -lgecodeint -lgecodekernel -lgecodesupport -lgecodegist

ifeq ($(DEBUG), 1)
  CXXFLAGS += -g -p
else
  CXXFLAGS += -O3
endif

OBJ_FILES = $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o, \
  $(patsubst src/%, %, $(CPP_SOURCES) ) ) )
STARTUP_OBJ = $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o, \
  $(patsubst src/%, %,$(STARTUP_SOURCE) ) ) )

all: prog

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	@echo
	@echo "compiling $<"
	$(GPP) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $< 

# for startup (no header file available)
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	@echo 
	@echo "compiling $<"
	$(GPP) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $< 

prog: $(OBJ_FILES) $(STARTUP_OBJ)
	@echo 
	@echo "linking ..."
	@echo
	$(GPP) $(CPPFLAGS) $(CXXFLAGS) -o prog $(OBJ_FILES) $(STARTUP_OBJ) $(LDFLAGS)



depend:
	makedepend $(STARTUP_SOURCE) $(CPP_SOURCES)

clean:
	rm -f obj/*.o prog

# DO NOT DELETE

src/main.o: src/aircraftlanding.h src/instance.h
src/aircraftlanding.o: src/aircraftlanding.h src/instance.h
src/instance.o: src/instance.h
