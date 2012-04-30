#
# Makefile
# Project 4
#
#  Created by Phillip Romig on 4/3/12.
#  Copyright 2012 Colorado School of Mines. All rights reserved.
#

#
# Linking the pcap library statically is not the best solution, however because the
# library is installed in the system directory but the header file is not, static
# linking ensure that we will get the library that matches our headers.
#
CXX = g++
LD = g++
CXXFLAGS = -g -I /u/wy/ys/promig3/pub/pcap/include
LDFLAGS = -g
LIBRARYS = /u/wy/ys/promig3/pub/pcap/lib/libpcap.a

#
# You should be able to add object files here without changing anything else
#
OBJ_FILES = project4.o resultsC.o

project4: ${OBJ_FILES}
	${LD} ${LDFLAGS} ${OBJ_FILES} -o project4 ${LIBRARYS}

#
# Please remember not to submit objects or binarys.
#
clean:
	rm -f core project4 ${OBJ_FILES}
