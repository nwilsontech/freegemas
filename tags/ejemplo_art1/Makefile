CXXFLAGS := -Wall -g -I. -Igosu `gosu/bin/gosu-config --cxxflags`
LDFLAGS  := -Wall `gosu/bin/gosu-config --libs --cxxflags` 
LIBS     := gosu/lib/libgosu.a

OUTPUT += juego

all: $(OUTPUT)

SRCS += main.cpp 

OBJS += $(addsuffix .o,$(basename $(SRCS)))

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) 

libgosu:
	cd gosu/linux && ./configure && make

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf

main.o: juego.h
