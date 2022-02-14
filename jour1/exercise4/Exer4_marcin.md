# Hello world

* We connect to http://i4prj.ase.au.dk/I4IKN using Mozilla Firefox
* To check which IP address we communicate with we can
    * compare text from http packets to the website text
    * check the first HTTP request after TCP handshakes
    * filter http.host in Wireshark and check the packets 

[comment]: <Unused (Screendumps/sample_http_content.png)> 

![](Screendumps/DNS_query.png)

To check http header request, we check the http GET/ packet

![](Screendumps/WS_HTTPrequestHeader.png)