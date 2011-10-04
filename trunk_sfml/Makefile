CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CXXFLAGS  := -Wall -I. -Iinclude -g

LDFLAGS   := -Wall -g
LIBS      := -lsfml-graphics

OUTPUT += programa

all: $(OUTPUT)

SRCDIR := src
OBJDIR := obj

SRCS := $(notdir $(shell ls -t $(SRCDIR)/*.cpp))
OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(SRCS))))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) 

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf

obj/StateManager.o: include/StateManager.h include/State.h
obj/log.o: include/log.h
obj/main.o: include/StateManager.h include/State.h include/Game.h include/log.h include/i18n.h
obj/StateMainMenu.o: include/State.h include/StateMainMenu.h include/log.h include/i18n.h include/JewelGroupAnim.h include/StateHowToPlay.h
obj/StateHowToPlay.o: include/State.h include/StateHowToPlay.h include/log.h include/i18n.h
obj/i18n.o: include/i18n.h
obj/Game.o: include/Game.h include/StateManager.h include/StateMainMenu.h
obj/Animation.o: include/Animation.h
obj/AnimationEquations.o: include/Animation.h
