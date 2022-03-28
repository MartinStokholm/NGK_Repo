# Task 1 
After adding an extra network adabter to R1, and configureing the network settings on alle the machines, H1 and H2 is ping from R1 

## ping from R1 to H1
```shell
ase@ubuntu:~$ ping -c 1 10.0.0.1
PING 10.0.0.1 (10.0.0.1) 56(84) bytes of data.
64 bytes from 10.0.0.1: icmp_seq=1 ttl=64 time=0.350 ms

--- 10.0.0.1 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.350/0.350/0.350/0.000 ms
```
## ping from R1 to H2
```
ase@ubuntu:~$ ping -c 1 10.9.8.1
PING 10.9.8.1 (10.9.8.1) 56(84) bytes of data.
64 bytes from 10.9.8.1: icmp_seq=1 ttl=64 time=0.957 ms

--- 10.9.8.1 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.957/0.957/0.957/0.000 ms
```

# task 2. 

In this exercise we configure router to forward ips
```shell
ase@ubuntu:~$ cat /proc/sys/net/ipv4/ip_forward
0
ase@ubuntu:~$ sudo sysctl -w net.ipv4.ip_forward=1 
[sudo] password for ase: 
net.ipv4.ip_forward = 1
ase@ubuntu:~$ cat /proc/sys/net/ipv4/ip_forward
1
```



# Task 3

In this exercise, the connection between the two H machines is confirmed, with a ping between them. 

