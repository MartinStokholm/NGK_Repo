## Running host test on www.google.com
### No flags
host www.google.com
```
www.google.com has address 172.217.21.164
www.google.com has IPv6 address 2a00:1450:400f:80b::2004
```
### -a flag
host -a www.google.com
```
Trying "www.google.com"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 42146
;; flags: qr rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 4, ADDITIONAL: 8

;; QUESTION SECTION:
;www.google.com.			IN	ANY

;; ANSWER SECTION:
www.google.com.		19	IN	AAAA	2a00:1450:400f:803::2004
www.google.com.		17	IN	A	142.250.74.100

;; AUTHORITY SECTION:
google.com.		50344	IN	NS	ns4.google.com.
google.com.		50344	IN	NS	ns1.google.com.
google.com.		50344	IN	NS	ns2.google.com.
google.com.		50344	IN	NS	ns3.google.com.

;; ADDITIONAL SECTION:
ns1.google.com.		121616	IN	A	216.239.32.10
ns2.google.com.		302065	IN	A	216.239.34.10
ns3.google.com.		171142	IN	A	216.239.36.10
ns4.google.com.		15035	IN	A	216.239.38.10
ns1.google.com.		330109	IN	AAAA	2001:4860:4802:32::a
ns2.google.com.		132450	IN	AAAA	2001:4860:4802:34::a
ns3.google.com.		153544	IN	AAAA	2001:4860:4802:36::a
ns4.google.com.		133720	IN	AAAA	2001:4860:4802:38::a

Received 324 bytes from 192.168.1.1#53 in 28 ms
```
### -4 flags
host -4 www.google.com
```
www.google.com has address 172.217.21.164
www.google.com has IPv6 address 2a00:1450:400f:80b::2004
```
### -6 flags
host -6 www.google.com
```
;; connection timed out; no servers could be reached
```
### -d flags
host -d www.google.com
```
Trying "www.google.com"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 43553
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;www.google.com.			IN	A

;; ANSWER SECTION:
www.google.com.		276	IN	A	172.217.21.164

Received 48 bytes from 192.168.1.1#53 in 12 ms
Trying "www.google.com"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 32729
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;www.google.com.			IN	AAAA

;; ANSWER SECTION:
www.google.com.		10	IN	AAAA	2a00:1450:400f:80b::2004

Received 60 bytes from 192.168.1.1#53 in 7 ms
Trying "www.google.com"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 59557
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 1, ADDITIONAL: 0

;; QUESTION SECTION:
;www.google.com.			IN	MX

;; AUTHORITY SECTION:
google.com.		60	IN	SOA	ns1.google.com. dns-admin.google.com. 428184630 900 900 1800 60

Received 82 bytes from 192.168.1.1#53 in 93 ms
```
