# our first makefile - version 3
#-------------------------------
IDIR =./source
CFLAGS = -g -Wall -pg 
#LDFLAGS=-L/home/pham/Downloads/opus/celt-standard/libcelt/.libs /home/pham/Downloads/opus/celt-standard/libcelt/.libs/*.o -L/home/pham/Downloads/libogg-1.3.0/src/.libs /home/pham/Downloads/libogg-1.3.0/src/.libs/*.o /home/pham/Downloads/opus/celt-standard/tools/wav_io.o
#OBJECTS= celt_enc.o celt.o bands.o cwrs.o entcode.o entdec.o entenc.o kissfft.o mathops.o mdct.o modes.o pitch.o plc.o 

PROG= /Test/encoder /Test/decoder /Test/signalcompare
LIBS= ../source/silklib.a ../../celt/libcelt/.libs/libcelt0.a -lm
CONFIG= -DHAVE_CONFIG_H


CC=gcc
#INCLUDE= -I../src_common/ -I../interface/ -I../../celt/libcelt/
INCLUDE= -I. -I../interface/ -I../src_FIX/ -I../src_SigProc_FIX/ -I../../celt/libcelt/ -I../src_common/

all: /source/silklib.a
	
/source/silklib.a:
	make -C src_common
	make -C src_FIX
	make -C src_SigProc_FIX
	make -C source
	make -C Test	
clean:
	rm *.o 
	rm -C source
	
	
