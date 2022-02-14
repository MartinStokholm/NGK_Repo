### Running host test on www.tv2.dk
#### No flags
host www.tv2.dk
```
www.tv2.dk is an alias for aws-https-redirect-prod.tv2net.dk.
aws-https-redirect-prod.tv2net.dk has address 3.123.214.150
aws-https-redirect-prod.tv2net.dk has address 3.123.214.120
aws-https-redirect-prod.tv2net.dk has address 3.123.202.164
```
#### -a flag
host -a www.tv2.dk
```
Trying "www.tv2.dk"
Host www.tv2.dk not found: 4(NOTIMP)
Received 28 bytes from 127.0.0.53#53 in 24 ms
```
#### -4 flags
host -4 www.tv2.dk
```
www.tv2.dk is an alias for aws-https-redirect-prod.tv2net.dk.
aws-https-redirect-prod.tv2net.dk has address 3.123.214.150
aws-https-redirect-prod.tv2net.dk has address 3.123.214.120
aws-https-redirect-prod.tv2net.dk has address 3.123.202.164
```
#### -6 flags
host -6 www.tv2.dk
```
;; connection timed out; no servers could be reached

```
#### -d flags
host -d www.tv2.dk
```
Trying "www.tv2.dk"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 26528
;; flags: qr rd ra; QUERY: 1, ANSWER: 4, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;www.tv2.dk.			IN	A

;; ANSWER SECTION:
www.tv2.dk.		28	IN	CNAME	aws-https-redirect-prod.tv2net.dk.
aws-https-redirect-prod.tv2net.dk. 247 IN A	3.123.214.150
aws-https-redirect-prod.tv2net.dk. 247 IN A	3.123.214.120
aws-https-redirect-prod.tv2net.dk. 247 IN A	3.123.202.164

Received 121 bytes from 127.0.0.53#53 in 0 ms
Trying "aws-https-redirect-prod.tv2net.dk"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 10672
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;aws-https-redirect-prod.tv2net.dk. IN	AAAA

Received 51 bytes from 127.0.0.53#53 in 64 ms
Trying "aws-https-redirect-prod.tv2net.dk"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 26478
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;aws-https-redirect-prod.tv2net.dk. IN	MX

Received 51 bytes from 127.0.0.53#53 in 12 ms
```
