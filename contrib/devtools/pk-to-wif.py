import binascii
import hashlib
import sys

def toWIF(ver, pk):
    hash1 = hashlib.sha256(binascii.unhexlify(ver + pk)).hexdigest()
    hash2 = hashlib.sha256(binascii.unhexlify(hash1)).hexdigest()
    checksum = hash2[:8]
    combined = ver + pk + checksum

    pubnum = int(combined, 16)
    pubnumlist = []
    while pubnum != 0: pubnumlist.append(pubnum % 58); pubnum /= 58
    wif = ''
    for l in ['123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'[x] for x in pubnumlist]:
        wif = l + wif
    return wif

v = sys.argv[1]
k = sys.argv[2]
rs = toWIF(v, k)
print(rs)