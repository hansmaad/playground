TARGET   := main
INCLUDE  := 
CXXFLAGS := -g -Wextra -Wall -std=c++11 -I/lib/gcc/i686-pc-cygwin/4.7.2/include/c++ -I/lib/gcc/i686-pc-cygwin/4.7.2/include/c++/i686-pc-cygwin
CXX      := clang++ 
LIBS     :=
EXT      := cpp
BUILDDIR := build
 
override BUILDDIR := $(strip $(BUILDDIR))
SOURCES  := $(wildcard *.$(EXT))
OBJECTS  := $(patsubst %.$(EXT), $(BUILDDIR)/%.o, $(SOURCES))
DEPS     := $(patsubst %.$(EXT), $(BUILDDIR)/%.dep, $(SOURCES))
 
.PHONY: all
all: $(TARGET)
 
$(TARGET): $(OBJECTS) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
 
ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif
 
$(OBJECTS): $(BUILDDIR)/%.o: %.$(EXT) $(BUILDDIR)/%.dep $(BUILDDIR)/.tag
	$(CXX) $(CXXFLAGS) -c $< -o $@
 
$(DEPS): $(BUILDDIR)/%.dep: %.$(EXT) $(BUILDDIR)/.tag
	mkdir -p $(dir $(@))
	$(CXX) $(CXXFLAGS) -MM $< -MT $@ -MT $(<:.$(EXT)=.o) -o $@
 
%.tag:
	mkdir -p $(dir $(@))
	touch $@
 
.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR)
