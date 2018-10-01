import random
import sys
def GenText(l, alphabet):
    text = str()
    for i in range(l):
        text += random.choice(alphabet)
    return text

inputFile = open("01.t", "w")
outputFile = open("01.a", "w")
textLen = 100
alphabet = ('a', 'b', 'c', 'd')
text = str(GenText(textLen, alphabet))# Generate text
inputFile.write(text + '\n')
pCount = random.randint(10, 20)# Generate count of patterns
for i in range(1, pCount):
    pattern = str()
    for j in range(4):
        pattern += random.choice(alphabet)
    inputFile.write(pattern + "\n")
    buf = str()
    res = text.find(pattern, 0, len(text))
    isMatch = False
    if res != -1:
        buf += str(i) + ": " #write num of pattern if we have at least one match
    while res != -1:
        if isMatch:
            buf += ", "
        isMatch = True
        buf += str(res)
        res = text.find(pattern, res + 1, len(text))
    if len(buf) != 0:
        outputFile.write(buf + "\n")
        

        