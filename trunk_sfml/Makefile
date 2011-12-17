CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CXXFLAGS  := -Wall -I. -Iinclude -g

LDFLAGS   := -Wall -g
LIBS      := -lsfml-graphics -lsfml-system -lsfml-window

OUTPUT += programa

all: $(OUTPUT)

SRCDIR := src
OBJDIR := obj

SRCS := $(notdir $(shell ls $(SRCDIR)/*.cpp))
OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(SRCS))))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) 

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf

# Generated using
# gcc -MM -I. -Iinclude src/* | sed 's/^\([a-zA-Z]\+.o\)/obj\/\1/g'
obj/Animation.o: src/Animation.cpp include/Animation.h include/log.h
obj/AnimationEquations.o: src/AnimationEquations.cpp include/Animation.h
obj/Board.o: src/Board.cpp include/Board.h include/log.h
obj/Game.o: src/Game.cpp include/Game.h include/StateManager.h \
 include/StateMainMenu.h include/log.h include/State.h \
 include/JewelGroupAnim.h include/Animation.h include/log.h \
 include/ResourceManager.h
obj/GameScoreBoard.o: src/GameScoreBoard.cpp include/GameScoreBoard.h \
 include/ResourceManager.h
i18n.o: src/i18n.cpp include/i18n.h include/log.h
obj/log.o: src/log.cpp include/log.h
obj/main.o: src/main.cpp include/i18n.h include/log.h include/Game.h \
 include/StateManager.h
obj/ResourceManager.o: src/ResourceManager.cpp include/ResourceManager.h \
 include/log.h include/Util.h
obj/StateGame.o: src/StateGame.cpp include/StateGame.h include/State.h \
 include/StateManager.h include/Board.h include/log.h \
 include/GameScoreBoard.h include/log.h include/ResourceManager.h \
 include/i18n.h
obj/StateHowToPlay.o: src/StateHowToPlay.cpp include/StateHowToPlay.h \
 include/log.h include/State.h include/StateManager.h include/i18n.h \
 include/ResourceManager.h include/Util.h
obj/StateMainMenu.o: src/StateMainMenu.cpp include/StateMainMenu.h \
 include/log.h include/State.h include/StateManager.h \
 include/JewelGroupAnim.h include/Animation.h include/StateHowToPlay.h \
 include/StateGame.h include/Board.h include/GameScoreBoard.h \
 include/ResourceManager.h include/i18n.h
obj/StateManager.o: src/StateManager.cpp include/StateManager.h \
 include/State.h include/StateManager.h include/log.h
obj/Util.o: src/Util.cpp include/Util.h include/log.h