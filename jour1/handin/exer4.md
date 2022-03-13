# Exercise 4: HTTP Client/server 

## 1. Hamlet on HTTP
This task will examin loading the website: http://i4prj.ase.au.dk/I4IKN.
This examination will be done with wireshark, 
Where wireshark will be set to recored before loading the page in the browser.
Then wiresharks filter will be suded to isolate the releavte packeds.
First DNS and then the http.
### DNS queary and response 
The dns queary 
```
13	1.573834603	10.211.55.7	10.211.55.1	DNS	75	Standard query 0xfeb8 AAAA i4prj.ase.au.dk
```
And the DNS respose

``` 
17	1.601046855	10.211.55.1	10.211.55.7	DNS	141	Standard query response 0xfeb8 AAAA i4prj.ase.au.dk SOA uniinfobloxintern02.uni.au.dk
```

### Time delay
The time delay for the DNS quaery and respose was 
$$ 1.601046855 - 1.573834603 = 0.027212251999999992 $$

### The HTTP request header
below the header resived from the website can be seen. 
Where the content is between the HTTP and the finishing \r\n
```
    HTTP/1.1 304 Not Modified\r\n
    Cache-Control: private\r\n
    Server: Microsoft-IIS/8.0\r\n
    X-AspNet-Version: 4.0.30319\r\n
    X-Powered-By: ASP.NET\r\n
    Date: Sat, 12 Mar 2022 17:54:17 GMT\r\n
    \r\n
    [HTTP response 1/2]
    [Time since request: 0.026490211 seconds]
    [Request in frame: 56]
    [Next request in frame: 394]
    [Next response in frame: 445]
    [Request URI: http://i4prj.ase.au.dk/I4IKN/bundles/modernizr?v=inCVuEFe6J4Q07A0AcRsbJic_UE5MwpRMNGcOtk94TE1]
``` 



### The HTTP request body
Following the header, the body of the website is delivered. 
From the HTTP, som information about the packed is first resived, followed by the line-based text data, where the content of the site actually resite

Here is the information as listed in wireshark. 
```
    HTTP/1.1 200 OK\r\n
    Cache-Control: private\r\n
    Content-Type: text/html; charset=utf-8\r\n
    Server: Microsoft-IIS/8.0\r\n
    X-AspNetMvc-Version: 5.2\r\n
    X-AspNet-Version: 4.0.30319\r\n
    X-Powered-By: ASP.NET\r\n
    Date: Sat, 12 Mar 2022 17:54:17 GMT\r\n
    Content-Length: 255303\r\n
    \r\n
    [HTTP response 1/2]
    [Time since request: 0.213257541 seconds]
    [Request in frame: 18]
    [Next request in frame: 391]
    [Next response in frame: 397]
    [Request URI: http://i4prj.ase.au.dk/I4IKN]
    File Data: 255303 bytes
Line-based text data: text/html (10220 lines)
```

Where the last line, Line-based text data: text/html (10220 lines), is the 10220 lines of hamlet, formattet with html. 


## 2. Installing apache2
the installtion of the apache2 server went smothly, and after it was done, it was checked if the apache server was running with the command

> sudo systemctl status apache2.service 

This confirmed that it was loaded and active, with the output containing:

```
     Loaded: loaded (/lib/systemd/system/apache2.service; enabled; vendor preset: enabled)
     Active: active (running) since Sat 2022-03-12 19:29:24 CET; 4min 0s ago
``` 
### 3. Establising a lan conection

The connection to the server was then testet with the commad telnet. 

```
ase@ubuntu:~$ telnet 10.0.0.1 80
Trying 10.0.0.1...
Connected to 10.0.0.1.
Escape character is '^]'.
GET / HTTP/1.0

HTTP/1.1 200 OK
Date: Sun, 13 Mar 2022 10:25:41 GMT
Server: Apache/2.4.41 (Ubuntu)
Last-Modified: Sat, 12 Mar 2022 18:29:22 GMT
ETag: "2aa6-5da09a048cb63"
Accept-Ranges: bytes
Content-Length: 10918
Vary: Accept-Encoding
Connection: close
Content-Type: text/html

```
Following the snippet seen above, the content of the standard index file was printet. 

## 4. Connecting to the server from the client. 

The command telnet can be used to establish the connections via the local area network. 

> telnet \<address\> \<port\>

When the connection is established, a prombt to enter a command for the sevner will apear. 
In our case, GET is our friend. 

> GET \<path/to/file\> HTTP/1.X

> GET / HTTP/1.0 
> host: 10.0.0.2

> GET / HTTP/1.1
> host: 10.0.0.2


Where, at least in 1.1 case, will add a host. 
The name / address of the client is used.



### HTTP 1.0 
The commulication between the server and the client when getting with HTTP 1.0 is seen here: 
``` 
No.	Time	Source	Destination	Protocol	Length	Info
16	3.242932398	    10.0.0.2	10.0.0.1	TCP	74	36744 → 80 [SYN] Seq=0 Win=64240 Len=0 MSS=1460 SACK_PERM=1 TSval=1871154045 TSecr=0 WS=128
17	3.242960021	    10.0.0.1	10.0.0.2	TCP	74	80 → 36744 [SYN, ACK] Seq=0 Ack=1 Win=65160 Len=0 MSS=1460 SACK_PERM=1 TSval=313594699 TSecr=1871154045 WS=128
18	3.243205239	    10.0.0.2	10.0.0.1	TCP	66	36744 → 80 [ACK] Seq=1 Ack=1 Win=64256 Len=0 TSval=1871154046 TSecr=313594699
46	13.353596113	10.0.0.2	10.0.0.1	TCP	82	36744 → 80 [PSH, ACK] Seq=1 Ack=1 Win=64256 Len=16 TSval=1871164156 TSecr=313594699 [TCP segment of a reassembled PDU]
47	13.353632645	10.0.0.1	10.0.0.2	TCP	66	80 → 36744 [ACK] Seq=1 Ack=17 Win=65152 Len=0 TSval=313604809 TSecr=1871164156
57	18.413083289	10.0.0.2	10.0.0.1	TCP	82	36744 → 80 [PSH, ACK] Seq=17 Ack=1 Win=64256 Len=16 TSval=1871169216 TSecr=313604809 [TCP segment of a reassembled PDU]
58	18.413105605	10.0.0.1	10.0.0.2	TCP	66	80 → 36744 [ACK] Seq=1 Ack=33 Win=65152 Len=0 TSval=313609869 TSecr=1871169216
61	19.564063730	10.0.0.2	10.0.0.1	HTTP	68	GET / HTTP/1.0 
62	19.564080406	10.0.0.1	10.0.0.2	TCP	66	80 → 36744 [ACK] Seq=1 Ack=35 Win=65152 Len=0 TSval=313611020 TSecr=1871170367
63	19.564276223	10.0.0.1	10.0.0.2	TCP	2962	80 → 36744 [PSH, ACK] Seq=1 Ack=35 Win=65152 Len=2896 TSval=313611020 TSecr=1871170367 [TCP segment of a reassembled PDU]
64	19.564300455	10.0.0.1	10.0.0.2	TCP	2962	80 → 36744 [PSH, ACK] Seq=2897 Ack=35 Win=65152 Len=2896 TSval=313611020 TSecr=1871170367 [TCP segment of a reassembled PDU]
65	19.564369838	10.0.0.1	10.0.0.2	TCP	2962	80 → 36744 [PSH, ACK] Seq=5793 Ack=35 Win=65152 Len=2896 TSval=313611020 TSecr=1871170367 [TCP segment of a reassembled PDU]
66	19.564392873	10.0.0.1	10.0.0.2	HTTP	2570	HTTP/1.1 200 OK  (text/html)
67	19.564518744	10.0.0.1	10.0.0.2	TCP	66	80 → 36744 [FIN, ACK] Seq=11193 Ack=35 Win=65152 Len=0 TSval=313611020 TSecr=1871170367
68	19.564559132	10.0.0.2	10.0.0.1	TCP	66	36744 → 80 [ACK] Seq=35 Ack=2897 Win=63488 Len=0 TSval=1871170367 TSecr=313611020
69	19.564559167	10.0.0.2	10.0.0.1	TCP	66	36744 → 80 [ACK] Seq=35 Ack=5793 Win=61568 Len=0 TSval=1871170367 TSecr=313611020
70	19.564724576	10.0.0.2	10.0.0.1	TCP	66	36744 → 80 [ACK] Seq=35 Ack=8689 Win=63488 Len=0 TSval=1871170367 TSecr=313611020
71	19.564724641	10.0.0.2	10.0.0.1	TCP	66	36744 → 80 [ACK] Seq=35 Ack=11193 Win=61568 Len=0 TSval=1871170367 TSecr=313611020
72	19.565069600	10.0.0.2	10.0.0.1	TCP	66	36744 → 80 [FIN, ACK] Seq=35 Ack=11194 Win=64128 Len=0 TSval=1871170368 TSecr=313611020
73	19.565093189	10.0.0.1	10.0.0.2	TCP	66	80 → 36744 [ACK] Seq=11194 Ack=36 Win=65152 Len=0 TSval=313611021 TSecr=1871170368
```
The HTTP1.1 
Number 16 til 18 are the three-way handshake between the client and server. 

At number 61, the HTTP get instrction arrive and it can be seen that the protocoll to be used is 1.0. 
Then the follwing 4 packecs are the transfer of the html file. 
Then a HTTP ok and [FIN, ACK] is recived and the transfer is finnsied.

After this, the clients sends acknolages ments for the packets and then the connection is closed imidiatly. 
Or alt least within a micro second.  
#### Closed by who?
The coonection is closed by the server. 
#### Version of apache ?
Yes, this can be seen in the HTTP OK message at 66. 
If it is unfolded, it can be seen that the version is 2.4.41. 

### HTTP 1.1

```
No.	Time	Source	Destination	Protocol	Length	Info
1	0.000000000	    10.0.0.2	10.0.0.1	TCP	74	36740 → 80 [SYN] Seq=0 Win=64240 Len=0 MSS=1460 SACK_PERM=1 TSval=1870786059 TSecr=0 WS=128
2	0.000028144	    10.0.0.1	10.0.0.2	TCP	74	80 → 36740 [SYN, ACK] Seq=0 Ack=1 Win=65160 Len=0 MSS=1460 SACK_PERM=1 TSval=313226713 TSecr=1870786059 WS=128
3	0.000238935	    10.0.0.2	10.0.0.1	TCP	66	36740 → 80 [ACK] Seq=1 Ack=1 Win=64256 Len=0 TSval=1870786059 TSecr=313226713
21	14.257228804	10.0.0.2	10.0.0.1	TCP	82	36740 → 80 [PSH, ACK] Seq=1 Ack=1 Win=64256 Len=16 TSval=1870800316 TSecr=313226713 [TCP segment of a reassembled PDU]
22	14.257270236	10.0.0.1	10.0.0.2	TCP	66	80 → 36740 [ACK] Seq=1 Ack=17 Win=65152 Len=0 TSval=313240970 TSecr=1870800316
63	22.528849980	10.0.0.2	10.0.0.1	TCP	82	36740 → 80 [PSH, ACK] Seq=17 Ack=1 Win=64256 Len=16 TSval=1870808588 TSecr=313240970 [TCP segment of a reassembled PDU]
64	22.528869488	10.0.0.1	10.0.0.2	TCP	66	80 → 36740 [ACK] Seq=1 Ack=33 Win=65152 Len=0 TSval=313249242 TSecr=1870808588
69	25.398128406	10.0.0.2	10.0.0.1	HTTP	68	GET / HTTP/1.1 
70	25.398152490	10.0.0.1	10.0.0.2	TCP	66	80 → 36740 [ACK] Seq=1 Ack=35 Win=65152 Len=0 TSval=313252111 TSecr=1870811457
71	25.398365099	10.0.0.1	10.0.0.2	TCP	2962	80 → 36740 [PSH, ACK] Seq=1 Ack=35 Win=65152 Len=2896 TSval=313252112 TSecr=1870811457 [TCP segment of a reassembled PDU]
72	25.398389806	10.0.0.1	10.0.0.2	TCP	2962	80 → 36740 [PSH, ACK] Seq=2897 Ack=35 Win=65152 Len=2896 TSval=313252112 TSecr=1870811457 [TCP segment of a reassembled PDU]
73	25.398453403	10.0.0.1	10.0.0.2	TCP	2962	80 → 36740 [PSH, ACK] Seq=5793 Ack=35 Win=65152 Len=2896 TSval=313252112 TSecr=1870811457 [TCP segment of a reassembled PDU]
74	25.398477270	10.0.0.1	10.0.0.2	HTTP	2551	HTTP/1.1 200 OK (text/html)
75	25.398671528	10.0.0.2	10.0.0.1	TCP	66	36740 → 80 [ACK] Seq=35 Ack=2897 Win=63488 Len=0 TSval=1870811458 TSecr=313252112
76	25.398671594	10.0.0.2	10.0.0.1	TCP	66	36740 → 80 [ACK] Seq=35 Ack=5793 Win=61568 Len=0 TSval=1870811458 TSecr=313252112
77	25.398732035	10.0.0.2	10.0.0.1	TCP	66	36740 → 80 [ACK] Seq=35 Ack=11174 Win=57600 Len=0 TSval=1870811458 TSecr=313252112
80	30.404531733	10.0.0.1	10.0.0.2	TCP	66	80 → 36740 [FIN, ACK] Seq=11174 Ack=35 Win=65152 Len=0 TSval=313257118 TSecr=1870811458
81	30.405217993	10.0.0.2	10.0.0.1	TCP	66	36740 → 80 [FIN, ACK] Seq=35 Ack=11175 Win=64128 Len=0 TSval=1870816464 TSecr=313257118
82	30.405268076	10.0.0.1	10.0.0.2	TCP	66	80 → 36740 [ACK] Seq=11175 Ack=36 Win=65152 Len=0 TSval=313257118 TSecr=1870816464
```

From what can be observed here, The HTTP1.1 protocol starts out, transmits and fisnsish the transmistion in the same way that the HTTP1.0 does. 
THe only execption is that the closing of the connection happens 5 seconds later. 
This is a sympton of the pipelining introduces with the 1.1 protocol, 
Allowing for handeling multiple request at a time. 
The delay of closing gives opens the window for reciving and handeling more request, where the 1.0 protocal only allows
time for one connection. 

The connection is closed by the server, 
In packed 74 HTTP/1.1 200 OK the version of appache was transferd aswell. 





## 5. Sending our own html file. 
### The html page:

This html page is naivly devoloped with three divs and 3 imgages. 
The images are supplyed by this website: [pixabay.com](https://pixabay.com/images/search/scenery/) 

```html

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Birks NGK TEST</title>
</head>
<body>
   <div><img src="img/img3.jpeg" alt="birds in the sky"></div>
   <div><img src="img/img2.jpeg" alt="fog in the hills"></div>
   <div><img src="img/img1.jpeg" alt="lake in the mountains"></div> 
</body> 
```

### examination of the new site

Wire shark is then used to exmin how the new website is transferd. 
Wireshark is stareted on server, and then the website is refreshed on the client. 

``` 
No.	Time	Source	Destination	Protocol	Length	Info
1	0.000000000	10.0.0.2	10.0.0.1	TCP	74	35178 → 80 [SYN] Seq=0 Win=64240 Len=0 MSS=1460 SACK_PERM=1 TSval=4020241694 TSecr=0 WS=128
2	0.000027566	10.0.0.1	10.0.0.2	TCP	74	80 → 35178 [SYN, ACK] Seq=0 Ack=1 Win=65160 Len=0 MSS=1460 SACK_PERM=1 TSval=1297789268 TSecr=4020241694 WS=128
3	0.000369113	10.0.0.2	10.0.0.1	TCP	66	35178 → 80 [ACK] Seq=1 Ack=1 Win=64256 Len=0 TSval=4020241694 TSecr=1297789268
``` 
Above we see the three way handshake establishing the connection. 

```
4	0.000395130	10.0.0.2	10.0.0.1	HTTP	530	GET /birk.html HTTP/1.1 
5	0.000414948	10.0.0.1	10.0.0.2	TCP	66	80 → 35178 [ACK] Seq=1 Ack=465 Win=64768 Len=0 TSval=1297789268 TSecr=4020241694
6	0.000811457	10.0.0.1	10.0.0.2	HTTP	685	HTTP/1.1 200 OK  (text/html)
```
After the connection is esbaslid, H2 request the header and H2 ansers with it. 

``` 
7	0.001151914	10.0.0.2	10.0.0.1	TCP	66	35178 → 80 [ACK] Seq=465 Ack=620 Win=64128 Len=0 TSval=4020241695 TSecr=1297789268
8	0.031909052	10.0.0.2	10.0.0.1	HTTP	477	GET /img/img3.jpeg HTTP/1.1 
9	0.031927519	10.0.0.1	10.0.0.2	TCP	66	80 → 35178 [ACK] Seq=620 Ack=876 Win=64384 Len=0 TSval=1297789299 TSecr=4020241725
10	0.032193148	10.0.0.1	10.0.0.2	HTTP	248	HTTP/1.1 304 Not Modified 
```
Then the clients asks for the first images on a new tcp connection,
witch the server gladly supllies. 
This is then followed by what apears to be two simuntaniorsly 3-three way handshake.
This is a prober exsample of pipelineing. 
```
11	0.032364183	10.0.0.2	10.0.0.1	TCP	74	35180 → 80 [SYN] Seq=0 Win=64240 Len=0 MSS=1460 SACK_PERM=1 TSval=4020241726 TSecr=0 WS=128
12	0.032364274	10.0.0.2	10.0.0.1	TCP	74	35182 → 80 [SYN] Seq=0 Win=64240 Len=0 MSS=1460 SACK_PERM=1 TSval=4020241726 TSecr=0 WS=128
13	0.032383583	10.0.0.1	10.0.0.2	TCP	74	80 → 35180 [SYN, ACK] Seq=0 Ack=1 Win=65160 Len=0 MSS=1460 SACK_PERM=1 TSval=1297789300 TSecr=4020241726 WS=128
14	0.032416726	10.0.0.1	10.0.0.2	TCP	74	80 → 35182 [SYN, ACK] Seq=0 Ack=1 Win=65160 Len=0 MSS=1460 SACK_PERM=1 TSval=1297789300 TSecr=4020241726 WS=128
15	0.032568040	10.0.0.2	10.0.0.1	TCP	66	35178 → 80 [ACK] Seq=876 Ack=802 Win=64128 Len=0 TSval=4020241726 TSecr=1297789300
16	0.032638317	10.0.0.2	10.0.0.1	TCP	66	35180 → 80 [ACK] Seq=1 Ack=1 Win=64256 Len=0 TSval=4020241726 TSecr=1297789300
17	0.032638373	10.0.0.2	10.0.0.1	TCP	66	35182 → 80 [ACK] Seq=1 Ack=1 Win=64256 Len=0 TSval=4020241726 TSecr=1297789300
```
Then the two remaining pictures are transferd by the same means.
```
18	0.033298943	10.0.0.2	10.0.0.1	HTTP	477	GET /img/img2.jpeg HTTP/1.1 
19	0.033306183	10.0.0.1	10.0.0.2	TCP	66	80 → 35178 [ACK] Seq=802 Ack=1287 Win=64128 Len=0 TSval=1297789301 TSecr=4020241727
20	0.033443563	10.0.0.2	10.0.0.1	HTTP	477	GET /img/img1.jpeg HTTP/1.1 
21	0.033462780	10.0.0.1	10.0.0.2	TCP	66	80 → 35182 [ACK] Seq=1 Ack=412 Win=64768 Len=0 TSval=1297789301 TSecr=4020241727
22	0.033598658	10.0.0.1	10.0.0.2	HTTP	248	HTTP/1.1 304 Not Modified 
23	0.033655496	10.0.0.1	10.0.0.2	HTTP	249	HTTP/1.1 304 Not Modified 
```
And as the last part of the site have been transferd, all the tcp connections are closed with ACK
and FIN, ARKS.
```
24	0.033917042	10.0.0.2	10.0.0.1	TCP	66	35178 → 80 [ACK] Seq=1287 Ack=984 Win=64128 Len=0 TSval=4020241728 TSecr=1297789301
25	0.033917090	10.0.0.2	10.0.0.1	TCP	66	35182 → 80 [ACK] Seq=412 Ack=184 Win=64128 Len=0 TSval=4020241728 TSecr=1297789301
26	5.007173688	10.0.0.1	10.0.0.2	TCP	66	80 → 35178 [FIN, ACK] Seq=984 Ack=1287 Win=64128 Len=0 TSval=1297794275 TSecr=4020241728
27	5.008244518	10.0.0.2	10.0.0.1	TCP	66	35178 → 80 [FIN, ACK] Seq=1287 Ack=985 Win=64128 Len=0 TSval=4020246701 TSecr=1297794275
28	5.008320955	10.0.0.1	10.0.0.2	TCP	66	80 → 35178 [ACK] Seq=985 Ack=1288 Win=64128 Len=0 TSval=1297794276 TSecr=4020246701
29	5.037869969	10.0.0.1	10.0.0.2	TCP	66	80 → 35182 [FIN, ACK] Seq=184 Ack=412 Win=64768 Len=0 TSval=1297794305 TSecr=4020241728
30	5.038944833	10.0.0.2	10.0.0.1	TCP	66	35182 → 80 [FIN, ACK] Seq=412 Ack=185 Win=64128 Len=0 TSval=4020246732 TSecr=1297794305
31	5.038981795	10.0.0.1	10.0.0.2	TCP	66	80 → 35182 [ACK] Seq=185 Ack=413 Win=64768 Len=0 TSval=1297794306 TSecr=4020246732
32	6.007081031	10.0.0.2	10.0.0.1	TCP	66	35180 → 80 [FIN, ACK] Seq=1 Ack=1 Win=64256 Len=0 TSval=4020247700 TSecr=1297789300
33	6.007262341	10.0.0.1	10.0.0.2	TCP	66	80 → 35180 [FIN, ACK] Seq=1 Ack=2 Win=65280 Len=0 TSval=1297795275 TSecr=4020247700
34	6.007603475	10.0.0.2	10.0.0.1	TCP	66	35180 → 80 [ACK] Seq=2 Ack=2 Win=64256 Len=0 TSval=4020247701 TSecr=1297795275
``` 

### The content of the request header
In the request header, can bee seen from the keyword GET to the escape sequence \r\n in the snippet below. 
The GET key word is followed by the requested page. 
After the esquence sequence the statistics of the packeds transfer.

```
Hypertext Transfer Protocol
    GET /birk.html HTTP/1.1\r\n
    Host: 10.0.0.1\r\n
    User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:97.0) Gecko/20100101 Firefox/97.0\r\n
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n
    Accept-Language: en-US,en;q=0.5\r\n
    Accept-Encoding: gzip, deflate\r\n
    Connection: keep-alive\r\n
    Upgrade-Insecure-Requests: 1\r\n
    If-Modified-Since: Sun, 13 Mar 2022 07:27:10 GMT\r\n
    If-None-Match: "1cf-5da147deb8c32-gzip"\r\n
    Cache-Control: max-age=0\r\n
    \r\n
    [Full request URI: http://10.0.0.1/birk.html]
    [HTTP request 1/3]
    [Response in frame: 6]
    [Next request in frame: 8]
```

### The content of the responce header

The Response can be seen from HTTP keyword to the escape sequence \r\n.
Here it can see that its the first of 3 responces. 

```
Hypertext Transfer Protocol
    HTTP/1.1 200 OK\r\n
    Date: Sun, 13 Mar 2022 07:36:27 GMT\r\n
    Server: Apache/2.4.41 (Ubuntu)\r\n
    Last-Modified: Sun, 13 Mar 2022 07:27:10 GMT\r\n
    ETag: "1cf-5da147deb8c32-gzip"\r\n
    Accept-Ranges: bytes\r\n
    Vary: Accept-Encoding\r\n
    Content-Encoding: gzip\r\n
    Content-Length: 282\r\n
    Keep-Alive: timeout=5, max=100\r\n
    Connection: Keep-Alive\r\n
    Content-Type: text/html\r\n
    \r\n
    [HTTP response 1/3]
    [Time since request: 0.000416327 seconds]
    [Request in frame: 4]
    [Next request in frame: 8]
    [Next response in frame: 10]
    [Request URI: http://10.0.0.1/birk.html]
    Content-encoded entity body (gzip): 282 bytes -> 463 bytes
    File Data: 463 bytes
Line-based text data: text/html (17 lines)
```