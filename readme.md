# Traceroute for checking how Autonomous systems connect

## Compiling

```bash
cmake --build ./build --target tracertas
```

The program will be in ```./build/tracertas/```.

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
62.78.100.207 :AS: 16086 DNA Oyj
142.250.174.235 :AS: 15169 Google LLC
142.250.174.234 :AS: 15169 Google LLC
142.250.225.39 :AS: 15169 Google LLC
142.250.229.89 :AS: 15169 Google LLC
8.8.8.8 :AS: 15169 Google LLC

Cmd: t 8.8.4.4
192.168.126.22
192.168.126.152
172.20.38.13
172.20.38.12
62.78.100.207 :AS: 16086 DNA Oyj
142.250.169.179 :AS: 15169 Google LLC
142.250.169.178 :AS: 15169 Google LLC
142.251.53.59 :AS: 15169 Google LLC
142.250.227.83 :AS: 15169 Google LLC
8.8.4.4 :AS: 15169 Google LLC

Cmd: t csc.fi
192.168.126.22
192.168.126.152
172.20.38.15
172.20.38.14
62.78.100.207 :AS: 16086 DNA Oyj
193.110.226.20 :IX: FICIX1 IPv4v6
193.110.226.14 :IX: FICIX1 IPv4v6
193.167.244.249 :AS: 1741 CSC - Tieteen tietotekniikan keskus Oy
193.167.142.241 :AS: 1741 CSC - Tieteen tietotekniikan keskus Oy
Responses got lost after this point.

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
      |     '--62.78.100.207 :AS: 16086 DNA Oyj
      |        |
      |        +--142.250.169.179 :AS: 15169 Google LLC
      |        |  |
      |        |  '--142.250.169.178 :AS: 15169 Google LLC
      |        |     |
      |        |     '--142.251.53.59 :AS: 15169 Google LLC
      |        |        |
      |        |        '--142.250.227.83 :AS: 15169 Google LLC
      |        |           |
      |        |           '--8.8.4.4 :AS: 15169 Google LLC
      |        '--142.250.174.235 :AS: 15169 Google LLC
      |           |
      |           '--142.250.174.234 :AS: 15169 Google LLC
      |              |
      |              '--142.250.225.39 :AS: 15169 Google LLC
      |                 |
      |                 '--142.250.229.89 :AS: 15169 Google LLC
      |                    |
      |                    '--8.8.8.8 :AS: 15169 Google LLC
      '--172.20.38.15
         |
         '--172.20.38.14
            |
            '--62.78.100.207 :AS: 16086 DNA Oyj
               |
               '--193.110.226.20 :IX: FICIX1 IPv4v6
                  |
                  '--193.110.226.14 :IX: FICIX1 IPv4v6
                     |
                     '--193.167.244.249 :AS: 1741 CSC - Tieteen tietotekniikan keskus Oy
                        |
                        '--193.167.142.241 :AS: 1741 CSC - Tieteen tietotekniikan keskus Oy
Cmd: exit
$>
```

## Notes

ICMP messages need to be allowed by the firewall.

## Tests

### Building
```bash
cmake build ./build --target tracertas_test
```

### Running
```bash
cd ./build/tracertas
./tracertas_test
```
or
```bash
cd ./build
ctest
```

### Coverage report
For coverage report gcov and lcov need to be installed and the tests built using GCC. Run first the tests once and then the script.
```bash
./generateCoverageReport.sh
```
Open ```coverageReport/index.html``` in browser.
