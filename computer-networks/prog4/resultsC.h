//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#ifndef resultsC_h
#define resultsC_h

class resultsC {
	protected:
		int totalPacketCount;
		int c8023;
		int cEth;
		int cIP4, tIP4, minIP4, maxIP4;
		int cARP, tARP, minARP, maxARP;
		int cIP6, tIP6, minIP6, maxIP6;
		int cEtc;
		int cICMP, tICMP, minICMP, maxICMP;
		int cUDP, tUDP, minUDP, maxUDP;
		int cTCP, tTCP, minTCP, maxTCP;
		int cEtcT;

	public:
		resultsC();
		void incrementPacketCount() { totalPacketCount++; };
		void displayResults();
		void inc8023();
		void incEthernet();
		void incIPv4(int l);
		void incARP(int l);
		void incIPv6(int l);
		void incEtc();
		void incICMP(int l);
		void incUDP(int l);
		void incTCP(int l);
		void incEtcT();

};

#endif
