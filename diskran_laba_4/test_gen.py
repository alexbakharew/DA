import sys
import random
import time


inputtFile = open("1t.txt", "w")

pattern = str()


random.seed()
pattern = str(random.randrange(10)) + " " + str(random.randrange(10))
inputtFile.write(pattern + "\n")

random.seed()
Lines = int(1000)

for line in range(Lines):
    Words = int(50)
    text = str()
    for i in range(Words):
        random.seed()
        text += str(random.randrange(10)) + " " + str(random.randrange(10)) + " " + str(random.randrange(10)) + " " + str(random.randrange(10))
    inputtFile.write(text + "\n")    
#     tmpList = text.split()
#     for i in range(line, len(tmpList)):
#         if tmpList[i] == pattern:
#             outputFile.write(str(line) + ", " + str(i + 1) + "\n")
# inputtFile.write("\n")

inputtFile.close()