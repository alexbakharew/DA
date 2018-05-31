import random
text = str()
for i in range(1, 5):
    text += " " + str(random.randint(1,100)) + " "
text += "\n"
print(text)
lst = text.split()
print(lst)