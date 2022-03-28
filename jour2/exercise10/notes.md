# Question 6
## Analyse on link layer with WireShark. Focus on MAC adresses. 

```
No.	Time	    Source	        Destination	    Protocol	Length	Info
9	1.394303147	10.9.8.1	    10.0.0.1	    ICMP	    98	    Echo (ping) request  id=0x0003, seq=1/256, ttl=63 (no response found!)
10	1.394402039	10.9.8.1    	10.0.0.1    	ICMP    	98  	Echo (ping) request  id=0x0003, seq=1/256, ttl=64 (reply in 11)
11	1.395151220	10.0.0.1    	10.9.8.1    	ICMP    	98  	Echo (ping) reply    id=0x0003, seq=1/256, ttl=64 (request in 10)
12	1.395474705	10.0.0.1    	10.9.8.1    	ICMP    	98  	Echo (ping) reply    id=0x0003, seq=1/256, ttl=63
13	6.443686006	VMware_4f:6d:17	VMware_b7:ab:ba	ARP	        60  	Who has 10.9.8.2? Tell 10.9.8.1
14	6.443686214	VMware_b7:ab:ba	VMware_4f:6d:17	ARP     	60	    10.9.8.2 is at 00:0c:29:b7:ab:ba
15	6.515741105	VMware_8e:ef:6a	VMware_b7:ab:b0	ARP     	60  	Who has 10.0.0.2? Tell 10.0.0.1
16	6.515763899	VMware_b7:ab:b0	VMware_8e:ef:6a	ARP     	42  	10.0.0.2 is at 00:0c:29:b7:ab:b0
17	6.586683393	VMware_b7:ab:b0	VMware_8e:ef:6a	ARP     	42  	Who has 10.0.0.1? Tell 10.0.0.2
18	6.586752747	VMware_b7:ab:ba	VMware_4f:6d:17	ARP     	60  	Who has 10.9.8.1? Tell 10.9.8.2
19	6.587092118	VMware_8e:ef:6a	VMware_b7:ab:b0	ARP     	60  	10.0.0.1 is at 00:0c:29:8e:ef:6a
20	6.587374676	VMware_4f:6d:17	VMware_b7:ab:ba	ARP     	60  	10.9.8.1 is at 00:0c:29:4f:6d:17
21	9.386472616	10.0.0.1    	10.9.8.1    	ICMP    	98  	Echo (ping) request  id=0x0006, seq=1/256, ttl=64 (no response found!)
22	9.386703125	10.0.0.1    	10.9.8.1    	ICMP    	98  	Echo (ping) request  id=0x0006, seq=1/256, ttl=63 (reply in 23)
23	9.387063117	10.9.8.1    	10.0.0.1    	ICMP    	98  	Echo (ping) reply    id=0x0006, seq=1/256, ttl=63 (request in 22)
24	9.387116046	10.9.8.1    	10.0.0.1    	ICMP    	98  	Echo (ping) reply    id=0x0006, seq=1/256, ttl=64
```
We notice that VMWare has this unique first part of the MAC adresses call VMWare_ which is 00:0c: when in Hex.
In the above capture from wireshark we are first sending one ping from H2 to H1, followed by one ping from H1 to H2.
As in the former exercise we see that on the transport layer the source and destination are the same through out the ping but now when we look at the link layer we can see that the source and destination is changing throughout the ping. First we have the MAC-d source to MAC-b destination (ping starting from H2), followed by MAC-b source   

Read from arp -n on R1
MAC-a: 
00:0c:29:8e:ef:6a

Read from arp -n on H1
MAC-b: 
00:0c:29:b7:ab:b0

Read from arp -n on H2
MAC-c:
00:0c:29:b7:ab:ba

Read from arp -n on R1
MAC-d:
00:0c:29:4f:6d:17

# Question 7
## Are the MAC adresses constant on the link layer, or are they changed during transfer of IP packages.

When looking at the data packages from wireShark (see above) we notice that the
source and destination for each package changes on the link layer so that a ping from H1 to H2, constists of two ?transfers?.
Where the first packeds is delevered from mac-x to mac-x, and the seconds transfer goes between mac-x and mac-x. 
Where mac-x and mac-x are both on the rounter, representing each of its adabters.

Transfers from H1 to H2 , goes frist from mac-a to mac-c, and then from mac-c to mac-d. 

Transfers from H2 to H1, goes first from mac-d to mac-b, and then two  

So they are not constant. 


 