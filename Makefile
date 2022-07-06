CC		:= g++
CFLAGS	:= -I/usr/local/include/opencv4 -L/usr/local/lib
OBJECTS	:=
LIBRARIES	:= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_dnn -lopencv_videoio -lopencv_imgcodecs -lopencv_img_hash
.PHONY: all clean

all: test

test:
	$(CC) $(CFLAGS) -o test test.cpp $(LIBRARIES)