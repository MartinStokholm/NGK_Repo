# exersize 3 


In this exersize we will examine the DNS-protocol with the cmd HOST. 
(The command nslookup can be used on non-unix systems, with at the time of writing where not avaible). 

Just running host in the terminal will display the options that the host cmd can take. 
This is illustrted here: Use only the
```
ase@ubuntu:~/NGK_Repo$ host 
Usage: host [-aCdilrTvVw] [-c class] [-N ndots] [-t type] [-W time]
            [-R number] [-m flag] hostname [server]
       -a is equivalent to -v -t ANY
       -A is like -a but omits RRSIG, NSEC, NSEC3
       -c specifies query class for non-IN data
       -C compares SOA records on authoritative nameservers
       -d is equivalent to -v
       -l lists all hosts in a domain, using AXFR
       -m set memory debugging flag (trace|record|usage)
       -N changes the number of dots allowed before root lookup is done
       -r disables recursive processing
       -R specifies number of retries for UDP packets
       -s a SERVFAIL response should stop query
       -t specifies the query type
       -T enables TCP/IP mode
       -U enables UDP mode
       -v enables verbose output
       -V print version number and exit
       -w specifies to wait forever for a reply
       -W specifies how long to wait for a reply
       -4 use IPv4 query transport only
       -6 use IPv6 query transport only

```

The settings used to test different DNS protocols have been chosen by one part randomeness and one part "i belive i have heard about this before". 

The host cmd will be ran with different flags
- -4 : Use only the ipv4 for query transport
- -6 : Use only the ipv6 for query transport
- -a : "all" 
- -d : printing debugging traceings

three websites are tested www.google.com, www.tv2.dk and www.australia.gov.au. 

## conclutions from the test

### noflags

Google returns a simple ip when the host is called vanilla on www.google.com. 
Where the two others returns their DNS alias and a series of ips for that alias. 
A best guess is that google has thier own DNS server and dont have a need for alias. 


### -a 

All three websits returned "host \<website\> not found: 4(notimp)". 

### -4 

-4 returns the exact same result as host with no flags. This makes sense since we are looking up the IP4 connected to the domain in the DNS. 

### -6 

The connection to all websites timed out when IPV6 was used to transmit the request. This probably indicates something we will learn later in the couse. 

### -d 

Gives a long detailed answer, that, agian, we might be able to interprete later in the course. 

## The tests

The test have been automated with the following shell script

```shell 
#!/bin/bash
function code {
    echo "$@"
    echo '```'  
    $@
    echo '```'
}
echo "## Running host test on "$1""  > "$2"
echo '### No flags' >> "$2"
echo No flags test. 
code host "$1" >> "$2"
echo '### -a flag' >> "$2"
echo -a flag test
code host -a "$1" >> "$2"
echo '### -4 flags' >> "$2"
echo -4 flag test
code host -4 "$1" >> "$2"
echo '### -6 flags' >> "$2"
echo -6 flag test
code host -6 "$1" >> "$2"
echo '### -d flags' >> "$2"
echo -d flag test
code host -d "$1" >> "$2"
```

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



