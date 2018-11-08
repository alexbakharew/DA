import random
import numpy as np
def getLongInt():
    l = random.randint(25,100)
    res = str()
    for i in range(l):
        res += str(random.randint(10, 99))
    return int(res)
operations = ['+', '-', '*', '/', '<', '>', '=']
testCount = 10
enum = 0
for t in range(testCount):
    filename_pattern = 'tests/{:02}'.format( enum+1 )
    with open( '{}.t'.format( filename_pattern ), 'w' ) as test_file, \
         open( '{}.a'.format( filename_pattern ), 'w' ) as answer_file:
        n = random.randint(1000, 1500)
        for i in range(n):
            n1= getLongInt()
            n2= getLongInt()
            op = random.choice(operations)

            test_file.write(str(n1) + "\n")
            test_file.write(str(n2) + "\n") 
            test_file.write(str(op) + "\n") 
            answer = str()
            if op == '+':
                answer = int(n1 + n2)
            elif op == '-':
                if n1 < n2:
                    answer = "Error"
                else:
                    answer = str(n1 - n2)
            elif op == '*':
                answer = str(n1 * n2)
            elif op == '/':
                if n2 == 0:
                    answer = "Error"
                else:
                    answer = str(int(n1 / n2))
            elif op == '^':
                if n1 == 0 and n2 == 0:
                    answer = "Error"
                else:
                    answer = str(np.power(n1, n2))
            elif op == '=':
                if n1 == n2:
                    answer = "true"
                else:
                    answer = "false"
            elif op == '>':
                if n1 > n2:
                    answer = "true"
                else:
                    answer = "false"
            elif op == '<':
                if n1 < n2:
                    answer = "true"
                else:
                    answer = "false"
            
            answer_file.write(str(answer) + "\n")
        
        test_file.close()
        answer_file.close()
    enum += 1
