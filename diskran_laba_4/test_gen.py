import sys
import random
import time

random.seed()
outputFile = open("01.a", "w")
inputtFile = open("01.t", "w")

pattern = str()
text = str()

pattern = str(random.randint(0, 100))# + " " + str(random.randint(0, 100))
inputtFile.write(pattern + "\n")

maxLine = random.randint(15, 20)

for line in range(1, maxLine):
    
    #time.sleep(1)
    #random.seed()
    
    maxWords = random.randint(15, 20)
    for i in range(1, maxWords):
        text += str(random.randint(0, 100)) + " "
    inputtFile.write(text + "\n")    
    tmpList = text.split()
    for i in range(0, len(tmpList)):
        if tmpList[i] == pattern:
            outputFile.write(str(line) + ", " + str(i + 1) + "\n")
inputtFile.write("\n")

inputtFile.close()
outputFile.close()