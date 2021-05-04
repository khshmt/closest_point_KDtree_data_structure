CC = g++
CFLAGS = -g -Wall
SRCS = closest_point.cpp
PROG = closest_point

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
