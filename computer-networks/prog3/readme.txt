Zack Tillotson
April 4, 2012

To compile simply run make:
$ make

To run run pa2
$ ./pa2

Typical inputs I used were:
	Number of packets: 5 
	Odds of packet loss: .1
	Odds of packet corruption: .1
	Time between packets: 1000
	Widow: 5 (any)
	Timeout Value: 15
	Trace Level: 5 (any)
	Random: 5 (any)

Here is a typical run using these inputs:

[726][21:14:16]memeyou@sovietta-ubuntu:~/Documents/csm/computer-networks/prog3>./pa2 
---- * Go Back N Network Simulator Version 1.1 * ------ 

Enter number of messages to simulate: 5
Enter packet loss probability [enter 0.0 for no loss]:.1
Enter packet corruption probability [0.0 for no corruption]:.1
Enter average time between messages from sender's layer5 [ > 0.0]:1000
Enter window size [>0]:5
Enter retransmission timeout [> 0.0]:15
Enter trace level:5
Enter random seed: [>0]:5
          GENERATE NEXT ARRIVAL: creating new arrival
            INSERTEVENT: time is 0.000000
            INSERTEVENT: future time will be 1138.645589

EVENT time: 1138.645589,  type: 1, fromlayer5  entity: 0
          GENERATE NEXT ARRIVAL: creating new arrival
            INSERTEVENT: time is 1138.645589
            INSERTEVENT: future time will be 1654.835658
A recieved message to send to B
	Adding message to buffer (0 already in buffer)
	Creating packet
	Sending packet to layer 3 A->B
          TOLAYER3: packet being lost
          START TIMER: starting timer at 1138.645589
            INSERTEVENT: time is 1138.645589
            INSERTEVENT: future time will be 1153.645589

EVENT time: 1153.645589,  type: 0, timerinterrupt   entity: 0
A timeout, resending last packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 0, ack 0, check: 32           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 1153.645589
            INSERTEVENT: future time will be 1160.019166
          START TIMER: starting timer at 1153.645589
            INSERTEVENT: time is 1153.645589
            INSERTEVENT: future time will be 1168.645589

EVENT time: 1160.019166,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum passed and sequence number correct, ACKing with current sequence number and changing sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 0, ack 0, check: 0           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 1160.019166
            INSERTEVENT: future time will be 1163.712546

EVENT time: 1163.712546,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum passed, removing message from buffer and changing sequence
			Message buffer empty, waiting
          STOP TIMER: stopping timer at 1163.712546

EVENT time: 1654.835658,  type: 1, fromlayer5  entity: 0
          GENERATE NEXT ARRIVAL: creating new arrival
            INSERTEVENT: time is 1654.835658
            INSERTEVENT: future time will be 2302.804651
A recieved message to send to B
	Adding message to buffer (0 already in buffer)
	Creating packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 1, ack 0, check: 111           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 1654.835658
            INSERTEVENT: future time will be 1658.820734
          START TIMER: starting timer at 1654.835658
            INSERTEVENT: time is 1654.835658
            INSERTEVENT: future time will be 1669.835658

EVENT time: 1658.820734,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum passed and sequence number correct, ACKing with current sequence number and changing sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 1, ack 0, check: 1           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 1658.820734
            INSERTEVENT: future time will be 1666.048524

EVENT time: 1666.048524,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum passed, removing message from buffer and changing sequence
			Message buffer empty, waiting
          STOP TIMER: stopping timer at 1666.048524

EVENT time: 2302.804651,  type: 1, fromlayer5  entity: 0
          GENERATE NEXT ARRIVAL: creating new arrival
            INSERTEVENT: time is 2302.804651
            INSERTEVENT: future time will be 4248.481704
A recieved message to send to B
	Adding message to buffer (0 already in buffer)
	Creating packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 0, ack 0, check: 110           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 2302.804651
            INSERTEVENT: future time will be 2312.739830
          START TIMER: starting timer at 2302.804651
            INSERTEVENT: time is 2302.804651
            INSERTEVENT: future time will be 2317.804651

EVENT time: 2312.739830,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum passed and sequence number correct, ACKing with current sequence number and changing sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 0, ack 0, check: 0           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 2312.739830
            INSERTEVENT: future time will be 2314.664083

EVENT time: 2314.664083,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum passed, removing message from buffer and changing sequence
			Message buffer empty, waiting
          STOP TIMER: stopping timer at 2314.664083

EVENT time: 4248.481704,  type: 1, fromlayer5  entity: 0
          GENERATE NEXT ARRIVAL: creating new arrival
            INSERTEVENT: time is 4248.481704
            INSERTEVENT: future time will be 4870.632038
A recieved message to send to B
	Adding message to buffer (0 already in buffer)
	Creating packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 1, ack 0, check: 111           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4248.481704
            INSERTEVENT: future time will be 4258.280374
          START TIMER: starting timer at 4248.481704
            INSERTEVENT: time is 4248.481704
            INSERTEVENT: future time will be 4263.481704

EVENT time: 4258.280374,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum passed and sequence number correct, ACKing with current sequence number and changing sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 1, ack 0, check: 1           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4258.280374
            INSERTEVENT: future time will be 4268.012024

EVENT time: 4263.481704,  type: 0, timerinterrupt   entity: 0
A timeout, resending last packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 1, ack 0, check: 33           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4263.481704
            INSERTEVENT: future time will be 4266.674917
          START TIMER: starting timer at 4263.481704
            INSERTEVENT: time is 4263.481704
            INSERTEVENT: future time will be 4278.481704

EVENT time: 4266.674917,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum passed and sequence number correct, ACKing with current sequence number and changing sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 0, ack 0, check: 0           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4266.674917
            INSERTEVENT: future time will be 4272.009461

EVENT time: 4268.012024,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum passed, removing message from buffer and changing sequence
			Message buffer empty, waiting
          STOP TIMER: stopping timer at 4268.012024

EVENT time: 4272.009461,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum passed, removing message from buffer and changing sequence
			Message buffer empty, waiting
          STOP TIMER: stopping timer at 4272.009461
Warning: unable to cancel your timer. It wasn't running.

EVENT time: 4870.632038,  type: 1, fromlayer5  entity: 0
          GENERATE NEXT ARRIVAL: creating new arrival
            INSERTEVENT: time is 4870.632038
            INSERTEVENT: future time will be 6455.397198
A recieved message to send to B
	Adding message to buffer (-1 already in buffer)
	Creating packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 1, ack 0, check: 111           TOLAYER3: packet being corrupted
          TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4870.632038
            INSERTEVENT: future time will be 4874.711875
          START TIMER: starting timer at 4870.632038
            INSERTEVENT: time is 4870.632038
            INSERTEVENT: future time will be 4885.632038

EVENT time: 4874.711875,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum failed, ACKing with old sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 0, ack 0, check: 0           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4874.711875
            INSERTEVENT: future time will be 4882.678243

EVENT time: 4882.678243,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum failed, resending last packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 1, ack 0, check: 1           TOLAYER3: packet being corrupted
          TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4882.678243
            INSERTEVENT: future time will be 4891.816614
          START TIMER: starting timer at 4882.678243
Warning: attempt to start a timer that is already started

EVENT time: 4885.632038,  type: 0, timerinterrupt   entity: 0
A timeout, resending last packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 1, ack 0, check: 33           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4885.632038
            INSERTEVENT: future time will be 4899.923338
          START TIMER: starting timer at 4885.632038
            INSERTEVENT: time is 4885.632038
            INSERTEVENT: future time will be 4900.632038

EVENT time: 4891.816614,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum failed, ACKing with old sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 0, ack 0, check: 0           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4891.816614
            INSERTEVENT: future time will be 4893.022340

EVENT time: 4893.022340,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum failed, resending last packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 1, ack 0, check: 1           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4893.022340
            INSERTEVENT: future time will be 4901.011780
          START TIMER: starting timer at 4893.022340
Warning: attempt to start a timer that is already started

EVENT time: 4899.923338,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum passed and sequence number correct, ACKing with current sequence number and changing sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 1, ack 0, check: 1           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4899.923338
            INSERTEVENT: future time will be 4904.819483

EVENT time: 4900.632038,  type: 0, timerinterrupt   entity: 0
A timeout, resending last packet
	Sending packet to layer 3 A->B
          TOLAYER3: seq: 1, ack 0, check: 33           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4900.632038
            INSERTEVENT: future time will be 4908.508744
          START TIMER: starting timer at 4900.632038
            INSERTEVENT: time is 4900.632038
            INSERTEVENT: future time will be 4915.632038

EVENT time: 4901.011780,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Checksum passed and sequence number correct, ACKing with current sequence number and changing sequence number
	Sending packet to layer 3 B->A
          TOLAYER3: seq: 0, ack 0, check: 0           TOLAYER3: scheduling arrival on other side
            INSERTEVENT: time is 4901.011780
            INSERTEVENT: future time will be 4911.079348

EVENT time: 4904.819483,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum passed, removing message from buffer and changing sequence
			Message buffer empty, waiting
          STOP TIMER: stopping timer at 4904.819483

EVENT time: 4908.508744,  type: 2, fromlayer3  entity: 1
B recieved packet
	Calculating checksum for packet
		Wrong sequence number, assuming it is a repeated message, ignoring

EVENT time: 4911.079348,  type: 2, fromlayer3  entity: 0
A recieved ACK
	Calculating checksum
		Checksum passed, removing message from buffer and changing sequence
			Message buffer empty, waiting
          STOP TIMER: stopping timer at 4911.079348
Warning: unable to cancel your timer. It wasn't running.

EVENT time: 6455.397198,  type: 1, fromlayer5  entity: 0
          GENERATE NEXT ARRIVAL: creating new arrival
            INSERTEVENT: time is 6455.397198
            INSERTEVENT: future time will be 7560.411390
Simulator terminated at time 6455.397198400829

