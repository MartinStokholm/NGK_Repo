### Running host test on www.google.com
#### No flags
host www.google.com
```
www.google.com has address 142.250.179.164
```
#### -a flag
host -a www.google.com
```
Trying "www.google.com"
Host www.google.com not found: 4(NOTIMP)
Received 32 bytes from 127.0.0.53#53 in 24 ms
```
#### -4 flags
host -4 www.google.com
```
www.google.com has address 142.250.179.164
```
#### -6 flags
host -6 www.google.com
```
;; connection timed out; no servers could be reached

```
#### -d flags
host -d www.google.com
```
Trying "www.google.com"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 45542
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;www.google.com.			IN	A

;; ANSWER SECTION:
www.google.com.		74	IN	A	142.250.179.164

Received 48 bytes from 127.0.0.53#53 in 0 ms
Trying "www.google.com"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 22139
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;www.google.com.			IN	AAAA

Received 32 bytes from 127.0.0.53#53 in 12 ms
Trying "www.google.com"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 10348
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;www.google.com.			IN	MX

Received 32 bytes from 127.0.0.53#53 in 48 ms
```
