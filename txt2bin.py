print("Converting as number prefix file to binary...")

import os
path = os.path.dirname(__file__)
asnBinFilePath = path + "/asPrefixes.bin"

if not os.path.exists(asnBinFilePath):
    asnumberfile = open(path + "/asPrefixes.txt")
    asnBinFile = open(asnBinFilePath, "wb")
    for line in asnumberfile:
        cidr, asNumber = line.split()
        asNumber = int(asNumber)
        network, maskLength = cidr.split('/')
        maskLength = int(maskLength)
        
        asnBinFile.write(bytearray([
            int(network.split('.')[0]),
            int(network.split('.')[1]),
            int(network.split('.')[2]),
            int(network.split('.')[3]),
            maskLength,
            asNumber >> 24 & 0xFF,
            asNumber >> 16 & 0xFF,
            asNumber >>  8 & 0xFF,
            asNumber >>  0 & 0xFF
        ]))
