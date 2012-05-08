//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"

// ***************************************************************************
// * resultsC::resultsC
// *  Constructor for the results container class.  
// ***************************************************************************
resultsC::resultsC() {
  totalPacketCount = 0;
  c8023=0;
  cEth=0;
  cIP4=0, tIP4=0, minIP4=9999999, maxIP4=0;
  cARP=0, tARP=0, minARP=9999999, maxARP=0;
  cIP6=0, tIP6=0, minIP6=9999999, maxIP6=0;
  cEtc=0;
  cICMP=0, tICMP=0, minICMP=9999999, maxICMP=0;
  cUDP=0, tUDP=0, minUDP=9999999, maxUDP=0;
  cTCP=0, tTCP=0, minTCP=9999999, maxTCP=0;
}


// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to print all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {

  std::cout << "A total of " << totalPacketCount << " packets processed." << std::endl;
  std::cout << std::endl << "Link Layer" << std::endl;
  std::cout << c8023 << " 802.3 packets" << std::endl;
  std::cout << cEth << " Ethernet packets" << std::endl;
  std::cout << std::endl << "Network Layer" << std::endl;
  std::cout << cIP4 << " IP4 packets";
  if(cIP4 > 0) std::cout << ", Length Avg Of " << tIP4/cIP4 << ", Min Of " << minIP4 << ", Max Of " << maxIP4;
  std::cout << std::endl;
  std::cout << cARP << " ARP packets";
  if(cARP > 0) std::cout << ", Length Avg Of " << tARP/cARP << ", Min Of " << minARP << ", Max Of " << maxARP;
  std::cout << std::endl;
  std::cout << cIP6 << " IP6 packets";
  if(cIP6 > 0) std::cout << ", Length Avg Of " << tIP6/cIP6 << ", Min Of " << minIP6 << ", Max Of " << maxIP6;
  std::cout << std::endl;
  std::cout << cEtc<< " Other protocol packets" << std::endl;
  std::cout << std::endl << "Transport Layer" << std::endl;
  std::cout << cTCP << " TCP packets";
  if(cTCP > 0) std::cout << ", Length Avg Of " << tTCP/cTCP << ", Min Of " << minTCP << ", Max Of " << maxTCP;
  std::cout << std::endl;
  std::cout << cICMP << " ICMP packets";
  if(cICMP > 0) std::cout << ", Length Avg Of " << tICMP/cICMP << ", Min Of " << minICMP << ", Max Of " << maxICMP;
  std::cout << std::endl;
  std::cout << cUDP << " UDP packets";
  if(cUDP > 0) std::cout << ", Length Avg Of " << tUDP/cUDP << ", Min Of " << minUDP << ", Max Of " << maxUDP;
  std::cout << std::endl;
  std::cout << cEtcT<< " Other protocol packets" << std::endl;
}

void resultsC::inc8023() {
	c8023++;
}

void resultsC::incEthernet() {
	cEth++;
}

void resultsC::incIPv4(int l) {
	cIP4++;
	tIP4+=l;
	if(minIP4 > l) minIP4 = l;
	if(maxIP4 < l) maxIP4 = l;
}
	
void resultsC::incARP(int l){ 
	cARP++;
	tARP+=l;
	if(minARP > l) minARP = l;
	if(maxARP < l) maxARP = l;
}
	
void resultsC::incIPv6(int l){ 
	cIP6++;
	tIP6+=l;
	if(minIP6 > l) minIP6 = l;
	if(maxIP6 < l) maxIP6 = l;
}
	
void resultsC::incEtc(){ 
	cEtc++;
}
	
void resultsC::incICMP(int l){ 
	cICMP++;
	tICMP+=l;
	if(minICMP > l) minICMP = l;
	if(maxICMP < l) maxICMP = l;
}
	
void resultsC::incUDP(int l){ 
	cUDP++;
	tUDP+=l;
	if(minUDP > l) minUDP = l;
	if(maxUDP < l) maxUDP = l;
}
	
void resultsC::incTCP(int l){ 
	cTCP++;
	tTCP+=l;
	if(minTCP > l) minTCP = l;
	if(maxTCP < l) maxTCP = l;
}

void resultsC::incEtcT(){ 
	cEtcT++;
}
