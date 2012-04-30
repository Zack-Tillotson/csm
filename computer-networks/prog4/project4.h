//
//  project4.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#ifndef project4_h
#define project4_h

// System include files
#include <iostream>
#include <pcap/pcap.h>

// Include files specific to this project.
#include "resultsC.h"

// Include files specific to this project.
void pk_processor(u_char *, const struct pcap_pkthdr *, const u_char *);

#endif
