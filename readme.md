# Traceroute for checking how Autonomous systems connect

## Compiling

```bash
cmake --build ./build
```

```tracertas``` is the actual program.
```tracertas_test``` runs the unit tests.

## Commands

```t [IP or host name]``` traceroute

```s``` show routes as a tree

```exit```

## Example

```
$> tracertas.exe
Cmd: t 8.8.8.8
192.168.126.22
192.168.126.152
172.20.38.13
172.20.38.12
62.78.100.207
142.250.174.235
142.250.174.234
142.250.225.39
142.250.229.89
8.8.8.8

Cmd: t 8.8.4.4
192.168.126.22
192.168.126.152
172.20.38.13
172.20.38.12
62.78.100.207
142.250.169.179
142.250.169.178
142.251.53.59
142.250.227.83
8.8.4.4

Cmd: t csc.fi
192.168.126.22
192.168.126.152
172.20.38.15
172.20.38.14
62.78.100.207
193.110.226.20
193.110.226.14
193.167.244.249
193.167.142.241

Cmd: s
This computer
|
'--192.168.126.22
   |
   '--192.168.126.152
      |
      +--172.20.38.13
      |  |
      |  '--172.20.38.12
      |     |
      |     '--62.78.100.207 : AS 16086 DNA Oyj
      |        |
      |        +--142.250.169.179 : AS 15169 Google LLC
      |        |  |
      |        |  '--142.250.169.178 : AS 15169 Google LLC
      |        |     |
      |        |     '--142.251.53.59 : AS 15169 Google LLC
      |        |        |
      |        |        '--142.250.227.83 : AS 15169 Google LLC
      |        |           |
      |        |           '--8.8.4.4 : AS 15169 Google LLC
      |        '--142.250.174.235 : AS 15169 Google LLC
      |           |
      |           '--142.250.174.234 : AS 15169 Google LLC
      |              |
      |              '--142.250.225.39 : AS 15169 Google LLC
      |                 |
      |                 '--142.250.229.89 : AS 15169 Google LLC
      |                    |
      |                    '--8.8.8.8 : AS 15169 Google LLC
      '--172.20.38.15
         |
         '--172.20.38.14
            |
            '--62.78.100.207 : AS 16086 DNA Oyj
               |
               '--193.110.226.20
                  |
                  '--193.110.226.14
                     |
                     '--193.167.244.249 : AS 1741 CSC - Tieteen tietotekniikan keskus Oy
                        |
                        '--193.167.142.241 : AS 1741 CSC - Tieteen tietotekniikan keskus Oy
Cmd: exit
$>
```

## Notes

ICMP messages need to be allowed by the firewall.
