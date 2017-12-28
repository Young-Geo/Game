CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Game.o

LIBS =

TARGET =	Game.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
