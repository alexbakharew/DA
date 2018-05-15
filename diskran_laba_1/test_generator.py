import random
import string

MAX_KEY_LEN = 33
MAX_VALUE_LEN = 8

def generate_random_key():
    return "".join( [ random.choice( string.hexdigits.lower() ) for _ in range( 1, MAX_KEY_LEN ) ] )

def generate_random_value():
    return "".join( [ random.choice( string.digits ) for _ in range( 1, MAX_VALUE_LEN ) ] )

if __name__ == "__main__":
    for num in range(1, 2):
        values = list()
        output_filename = "tests/{:02d}.t".format( num )
        with open( output_filename, 'w') as output:
            for _ in range( 10000000 ):
                key = generate_random_key()
                value = generate_random_value()
                values.append( (key, value) )
                output.write( "{}\t{}\n".format(key, value) )
        # Answer.
        # values[0][0] -- key
        # values[0][1] -- value
        output_filename = "tests/{:02d}.a".format( num )
        with open( output_filename, 'w') as output:
            values = sorted( values, key=lambda x: x[0] )
            for value in values:
                output.write( "{}\t{}\n".format(value[0], value[1]) )
