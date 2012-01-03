CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CXXFLAGS  := -Wall -I. -Iinclude -g

LDFLAGS   := -Wall -g
LIBS      := -lsfml-graphics -lsfml-system -lsfml-window

OUTPUT += programa

all: $(OUTPUT)

HDRDIR := include
SRCDIR := src
OBJDIR := obj

HDRS := $(notdir $(shell ls $(HDRDIR)/*.h))
SRCS := $(notdir $(shell ls $(SRCDIR)/*.cpp))
OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(SRCS))))

DEPSFILE := depsfile

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) 

deps: $(SRCDIR)/*.cpp $(HDRDIR)/*.h
	gcc -MM -I. -Iinclude src/* | sed 's/^\([a-zA-Z]\+.o\)/obj\/\1/g' > depsfile

-include $(DEPSFILE)

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf

# Generated using
# gcc -MM -I. -Iinclude src/* | sed 's/^\([a-zA-Z]\+.o\)/obj\/\1/g'
