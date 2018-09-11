import sys
import random
import string

def get_random_key():
    return random.choice( string.ascii_letters )

actions = ["+", "?", "-"]
test_file_name = "tests/01"
output_file = open("tests/01.t", 'w')
answer_file = open("tests/01.a", 'w')
for _ in range(30):
    keys = dict()
    for _ in range(20):
            action = random.choice( actions )
            if action == "+":
                key_1 = get_random_key()
                key_2 = get_random_key()
                key_3 = get_random_key()
                key_4 = get_random_key()
                key = key_1 + key_2 + key_3 + key_4
                value = random.randint( 1, 1000 )
                output_file.write("+ {0} {1}\n".format( key, value ))
                key = key.lower()
                answer = "Exist"
                if key not in keys:
                    answer = "OK"
                    keys[key] = value
                answer_file.write( "{0}\n".format( answer ) )
            elif action == "?":
                search_exist_element = random.choice( [ True, False ] )
                key = random.choice( [ key for key in keys.keys() ]) if search_exist_element and len( keys.keys() ) > 0 else get_random_key()
                output_file.write( "{0}\n".format( key ) )
                key = key.lower()
                if key in keys:
                    answer = "OK: {0}".format( keys[key] )
                else:
                    answer = "NoSuchWord"
                answer_file.write( "{0}\n".format( answer ) )
            elif action == "-":
                delete_exist_element = random.choice( [ True, False ] )
                key = random.choice( [ key for key in keys.keys() ] ) if search_exist_element and len( keys.keys() ) > 0 else get_random_key()
                output_file.write("- {0}\n".format(key))
                key = key.lower()
                if key in keys:
                    answer = "OK"
                    keys.pop(key)
                else:
                    answer = "NoSuchWord"
                answer_file.write( "{0}\n".format(answer))