# exersice 2
## question 1
ping -c 1 10.0.0.2 on H1 to ping H2
```
ase@ubuntu:~$ ping 10.0.0.^C
ase@ubuntu:~$ ping -c 1 10.0.0.2
PING 10.0.0.2 (10.0.0.2) 56(84) bytes of data.
```

## qustion 2 

ping -c -10 10.0.0.2
```
ase@ubuntu:~$ ping -c 10 10.0.02
PING 10.0.02 (10.0.0.2) 56(84) bytes of data.
64 bytes from 10.0.0.2: icmp_seq=1 ttl=64 time=0.599 ms
64 bytes from 10.0.0.2: icmp_seq=2 ttl=64 time=1.01 ms
64 bytes from 10.0.0.2: icmp_seq=3 ttl=64 time=1.06 ms
64 bytes from 10.0.0.2: icmp_seq=4 ttl=64 time=1.06 ms
64 bytes from 10.0.0.2: icmp_seq=5 ttl=64 time=1.03 ms
64 bytes from 10.0.0.2: icmp_seq=6 ttl=64 time=0.428 ms
64 bytes from 10.0.0.2: icmp_seq=7 ttl=64 time=1.11 ms
64 bytes from 10.0.0.2: icmp_seq=8 ttl=64 time=0.722 ms
64 bytes from 10.0.0.2: icmp_seq=9 ttl=64 time=0.653 ms
64 bytes from 10.0.0.2: icmp_seq=10 ttl=64 time=0.707 ms

--- 10.0.02 ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 9070ms
rtt min/avg/max/mdev = 0.428/0.837/1.105/0.229 ms
```
## question 3

```
ase@ubuntu:~$ ping -c 1 www.google.com
PING www.google.com (142.250.179.164) 56(84) bytes of data.
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=1 ttl=128 time=29.7 ms

--- www.google.com ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 29.685/29.685/29.685/0.000 ms
```
Time is 29.685


-----
## qustion 4 
-----
ping -c 10 www.google.com is called

```
PING www.google.com (142.250.179.164) 56(84) bytes of data.
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=1 ttl=128 time=30.5 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=2 ttl=128 time=37.3 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=3 ttl=128 time=30.3 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=4 ttl=128 time=30.4 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=5 ttl=128 time=29.7 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=6 ttl=128 time=36.8 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=7 ttl=128 time=36.3 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=8 ttl=128 time=38.8 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=9 ttl=128 time=37.1 ms
64 bytes from ams15s41-in-f4.1e100.net (142.250.179.164): icmp_seq=10 ttl=128 time=30.4 ms

--- www.google.com ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 9018ms
rtt min/avg/max/mdev = 29.660/33.754/38.808/3.559 ms
```
the minimum 29.669 
The avg time is 33.747 
The max time is 38.808
the max deviation 3.559


## qustion 5

### 5.1 Pinging
```
ase@ubuntu:~$ ping -c 1 wwww.tv2.dk
ping: wwww.tv2.dk: Name or service not known
```
It appears that pinging is not supported.

### 5.2 
Finding our own IP with host -H
```
ase@ubuntu:~$ hostname -I
192.168.44.128 10.0.0.1 

``` 
Identifing our SYN and the SYC, ACH, and the time between them.

```
7	0.698303972	192.168.44.128	10.83.252.23	TCP	74	36480 → 443 [SYN] Seq=0 Win=64240 Len=0 MSS=1460 SACK_PERM=1 TSval=2515601345 TSecr=0 WS=128
8	0.701008276	10.83.252.23	192.168.44.128	TCP	60	443 → 36480 [SYN, ACK] Seq=0 Ack=1 Win=64240 Len=0 MSS=1460
9	0.701034020	192.168.44.128	10.83.252.23	TCP	54	36480 → 443 [ACK] Seq=1 Ack=1 Win=64240 Len=0
```
the thime between them is 
$$ [SYC, ACK] - [ACK] = 0.701 - 0.698 = 0.002705304 $$


 The 3 way handskae is allso cool, and illustatrede with the SYN from us, the SYN, ACK from AU, and our ACK to AU. 
```
Confirming that we are speaking with AU
ase@ubuntu:~$ host 10.83.252.23
23.252.83.10.in-addr.arpa domain name pointer auinstallation48v6.cs.au.dk.
23.252.83.10.in-addr.arpa domain name pointer typo3.au.dk.
23.252.83.10.in-addr.arpa domain name pointer cepdisc.au.dk.
23.252.83.10.in-addr.arpa domain name pointer ced.au.dk.
```






## qustion 6 

```
ase@ubuntu:~$ host www.australia.gov.au
www.australia.gov.au is an alias for cdn.prod65.dta.adobecqms.net.
cdn.prod65.dta.adobecqms.net has address 18.64.103.78
cdn.prod65.dta.adobecqms.net has address 18.64.103.66
cdn.prod65.dta.adobecqms.net has address 18.64.103.43
cdn.prod65.dta.adobecqms.net has address 18.64.103.14
```
From the terminal we find the IPs of www.australia.gov.au. 

In wireshark we can find the three-way hand shake. 
```
7	0.182429071	192.168.44.128	18.64.103.43	TCP	74	57228 → 443 [SYN] Seq=0 Win=64240 Len=0 MSS=1460 SACK_PERM=1 TSval=3899355100 TSecr=0 WS=128
9	0.217609102	18.64.103.43	192.168.44.128	TCP	60	443 → 57228 [SYN, ACK] Seq=0 Ack=1 Win=64240 Len=0 MSS=1460
10	0.217711228	192.168.44.128	18.64.103.43	TCP	54	57228 → 443 [ACK] Seq=1 Ack=1 Win=64240 Len=0
```
Here we can see the time from our request to and the respose from Ausstrila.gov.au. 
$$ 0.217 - 0.182 = 0.035180031 $$

## questions 7 

The difrence between the time alculated in 5 og 6. 
$$  0.035180031 - 0.002705304 = 0,032474727 $$ 























