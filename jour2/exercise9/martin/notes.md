# Question 3

One the screen dump below is shown that H1 and H2 are pinging eachother continiously

![](screenDumps\ex9_ping_h1_to_h2_thorugh_r1.jpg)

# Question 4

To analyse the communication between H1 and H2 we change so they only ping eachoter once. On the R1 machine we can then open wireshark and see the packages shown below: 

![](screenDumps\ex9_ping_h1_to_h2_thorugh_r1_wiresharkCapture.jpg)

The lines highlighted are ping from H1 to H2. 
The lines not highlited are the ping from H2 to H1.

# Question 5

Looking at the data packet
Ping from H2 to H1 going through R1

```
No.	Time	Source	Destination	Protocol	Length	Info
7	1.683791618	10.9.8.1	10.0.0.1	ICMP	100	Echo (ping) request  id=0x000b, seq=1/256, ttl=64 (no response found!)
8	1.683808348	10.9.8.1	10.0.0.1	ICMP	100	Echo (ping) request  id=0x000b, seq=1/256, ttl=63 (reply in 9)
9	1.684517066	10.0.0.1	10.9.8.1	ICMP	100	Echo (ping) reply    id=0x000b, seq=1/256, ttl=64 (request in 8)
10	1.684523654	10.0.0.1	10.9.8.1	ICMP	100	Echo (ping) reply    id=0x000b, seq=1/256, ttl=63
```


We see in line 7 and 8 two requests looking like its comming straight from H1 to H2 twice.
We see in line 9 and 10 two replyes looking like again its comming straight from H2 back to H1 twice.

However what is actually happening is that the first request is going to R1, and then R1 is forwarding the request to H2. 
Similar is the process for the reply, where the first reply is going from H2 to R1, and then from R1
back to H1. 

Ping fom H1 to H2 going through R1

```
No.	Time	Source	Destination	Protocol	Length	Info
12	3.826602380	10.0.0.1	10.9.8.1	ICMP	100	Echo (ping) request  id=0x000f, seq=1/256, ttl=64 (no response found!)
13	3.826615339	10.0.0.1	10.9.8.1	ICMP	100	Echo (ping) request  id=0x000f, seq=1/256, ttl=63 (reply in 14)
14	3.826781421	10.9.8.1	10.0.0.1	ICMP	100	Echo (ping) reply    id=0x000f, seq=1/256, ttl=64 (request in 13)
15	3.826785441	10.9.8.1	10.0.0.1	ICMP	100	Echo (ping) reply    id=0x000f, seq=1/256, ttl=63

```

the above packages show the exact same thing just from the H1 point of view. 

So in conclusion, we see that the IP stays the same through out the ping transfer and is simple just forwarded through. 