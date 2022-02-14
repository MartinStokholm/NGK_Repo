### Running host test on www.australia.gov.au
#### No flags
host www.australia.gov.au
```
www.australia.gov.au is an alias for cdn.prod65.dta.adobecqms.net.
cdn.prod65.dta.adobecqms.net has address 18.64.103.66
cdn.prod65.dta.adobecqms.net has address 18.64.103.43
cdn.prod65.dta.adobecqms.net has address 18.64.103.14
cdn.prod65.dta.adobecqms.net has address 18.64.103.78
```
#### -a flag
host -a www.australia.gov.au
```
Trying "www.australia.gov.au"
Host www.australia.gov.au not found: 4(NOTIMP)
Received 38 bytes from 127.0.0.53#53 in 24 ms
```
#### -4 flags
host -4 www.australia.gov.au
```
www.australia.gov.au is an alias for cdn.prod65.dta.adobecqms.net.
cdn.prod65.dta.adobecqms.net has address 18.64.103.66
cdn.prod65.dta.adobecqms.net has address 18.64.103.43
cdn.prod65.dta.adobecqms.net has address 18.64.103.14
cdn.prod65.dta.adobecqms.net has address 18.64.103.78
```
#### -6 flags
host -6 www.australia.gov.au
```
;; connection timed out; no servers could be reached

```
#### -d flags
host -d www.australia.gov.au
```
Trying "www.australia.gov.au"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 33623
;; flags: qr rd ra; QUERY: 1, ANSWER: 5, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;www.australia.gov.au.		IN	A

;; ANSWER SECTION:
www.australia.gov.au.	49	IN	CNAME	cdn.prod65.dta.adobecqms.net.
cdn.prod65.dta.adobecqms.net. 49 IN	A	18.64.103.66
cdn.prod65.dta.adobecqms.net. 49 IN	A	18.64.103.43
cdn.prod65.dta.adobecqms.net. 49 IN	A	18.64.103.14
cdn.prod65.dta.adobecqms.net. 49 IN	A	18.64.103.78

Received 144 bytes from 127.0.0.53#53 in 0 ms
Trying "cdn.prod65.dta.adobecqms.net"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 11854
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;cdn.prod65.dta.adobecqms.net.	IN	AAAA

Received 46 bytes from 127.0.0.53#53 in 28 ms
Trying "cdn.prod65.dta.adobecqms.net"
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 42663
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;cdn.prod65.dta.adobecqms.net.	IN	MX

Received 46 bytes from 127.0.0.53#53 in 28 ms
```
