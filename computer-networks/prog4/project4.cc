//
//  project4.cpp
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"


// ****************************************************************************
// * pk_processor()
// *  Most of the work done by the program will be done here (or at least it
// *  it will originate here). The function will be called once for every 
// *  packet in the savefile.
// ****************************************************************************
void pk_processor(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {

	resultsC* results = (resultsC*)user;
	results->incrementPacketCount();

	int caplen = (int) pkthdr->caplen;
	
	//printf("Packet (length %d): %u\n", caplen, *packet);

	int pos = 0;

	// Link Layer
	// 6 bytes dest
	// 6 bytes src
	// 2 bytes type
	int type = packet[12] * 256 + packet[13];

	if(type <= 1536) { // Is 802.3
		results->inc8023();
	} else { // Is Ethernet II
		results->incEthernet();
	}

	pos += 14;

	bool done = false;

	// Network Layer
	int ttype = 0;
	if(type == 2048) { // IPv4
		// 1 byte version and header length
		// 1 byte flags
		// 2 bytes tot length
		int length = packet[pos + 2] * 256 + packet[pos + 3];
		ttype = packet[pos + 9];
		results->incIPv4(length);
		pos += 20;
	} else if(type == 2054) { // ARP
		int hlen = packet[pos + 4];
		int plen = packet[pos + 5];
		int length = 8 + 2 * hlen + 2 * plen;
		results->incARP(length);
		pos += length;
		done=true;
	} else if(type == 34525) { // IPv6
		int length = packet[pos + 4] * 256 + packet[pos + 5];
		ttype = packet[pos + 6];
		results->incIPv6(length);
		pos += 40;
	} else {
		done=true;
		results->incEtc();
	}

	// Transport Layer
	if(!done) {

		int tlen = pkthdr->len - pos;
		if(ttype == 6) { // TCP
			results->incTCP(tlen);
		} else if (ttype == 158) { // ICMP
			results->incICMP(tlen);
		} else if (ttype == 17) { // UDP
			results->incUDP(tlen);
		} else {
			results->incEtcT();
		}
		

	}
	
	return;

}


// ****************************************************************************
// * main()
// *  You should not have to worry about anything if you don't want to. 
// *  My code will open the file, initalize the results container class,
// *  call pk_processor() once for each packet and the finally call
// *  the displayResutls() method.
// ****************************************************************************
int main (int argc, const char * argv[])
{

  
  // **********************************************************************
  // * The program is called with a single argument, the name of the
  // * pcap save file to read.
  // **********************************************************************
  if (argc != 2) {
     std::cerr << "useage: project4 <filename>" << std::endl;
     exit(EXIT_FAILURE);
  }


  // **********************************************************************
  // * Instantiate the results class.  
  // **********************************************************************
  resultsC* results = new resultsC();



  // **********************************************************************
  // * Attempt to open the file.
  // **********************************************************************
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *PT;

  bzero(errbuf,PCAP_ERRBUF_SIZE);
  if ((PT = pcap_open_offline(argv[1],errbuf)) == NULL ) {
    std::cerr << "Unable to open pcap file: " << argv[1] << "\n"
         << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }

  if (strlen(errbuf) > 0)
    std::cerr << "Warning: pcap_open_offiline: " << pcap_geterr(PT) << std::endl;



  // **********************************************************************
  // * The dispatcher will call the packet processor once for packet
  // * in the capture file.
  // **********************************************************************
  int pk_count;
  if ((pk_count = pcap_dispatch(PT, -1, pk_processor, (u_char *)results)) < 0) {
    std::cerr << "Error calling dispatcher: " << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "Dispatcher processed " << pk_count << " packets." << std::endl;


  // **********************************************************************
  // * File your report here.
  // **********************************************************************
  results->displayResults();
  exit(EXIT_SUCCESS);
}


