CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		forward_list.o test_pthreads.o

LIBS =

TARGET =	test_pthreads.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
