CC = g++

CFLAGS = -w -Wall -O2
SRCS = least_square.cpp  

PROG = least_square

OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

	$(./PROG)
