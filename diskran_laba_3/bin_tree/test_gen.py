import random
file = open("01.t", "w+")
for i in range(20000000):
    n = random.randint(-10000, 10000)
    file.write(str(n) + "\n")
file.close()
