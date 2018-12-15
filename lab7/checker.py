from random import choice
import sys
import random

MAX_SIZE_MATRIX = 5000
MIN_SIZE_MATRIX = 1
COUNT_OF_TESTS = 15
#поправить
KIND_OF_DIG = [0, 1, 0, 0, 0, 0, 0] 


def generate_matrix(n, m):
	matrix = []
	for i in range(n):
		line = []
		for j in range(m):
			line.append( choice(KIND_OF_DIG) )
		matrix.append(line)
	return matrix


def find_max_matrix(matrix, n, m):
	ans = 0
	for i in range(n):
		for j in range(m):
			right = m
			down = n
			if matrix[i][j] == 0: 
				x = i
				y = j
				while (x < down and matrix[x][y] == 0):
					while (y < right and matrix[x][y] == 0):
						y += 1
					right = y
					x += 1
					ans = max( ans, (x - i)*(y - j) )
					y = j
	return ans




if __name__ == '__main__':
	
	for enum in range( COUNT_OF_TESTS ):
		test_file_name = "tests/{:02d}".format( enum + 1 )
		with open( "{0}.t".format( test_file_name ), 'w' ) as output_file, \
			open( "{0}.txt".format( test_file_name ), "w" ) as answer_file:
			MIN_SIZE_MATRIX *= 2
			n = random.randint(MIN_SIZE_MATRIX, MIN_SIZE_MATRIX + 1)
			m = random.randint(MIN_SIZE_MATRIX, MIN_SIZE_MATRIX + 1)
			output_file.write( "{}\t{}\n".format(n, m) )
			matrix = generate_matrix(n, m)

			#Print matrix
			for i in matrix:
				for j in i:
					output_file.write( str(j) )
				output_file.write( "\n" )

			answer_file.write( str(find_max_matrix(matrix, n, m)) )

