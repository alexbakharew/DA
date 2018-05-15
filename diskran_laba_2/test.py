
# -*- coding: utf-8 -*-
import sys
import random
import string

def get_random_key():
    return random.choice( string.ascii_letters )

if __name__ == "__main__":
    # Проверяем, что передали 1 аргумент.
    if len(sys.argv) != 2:
        print( "Usage: {0} <count of tests>".format( sys.argv[0] ) )
        sys.exit(1)
    
    count_of_tests = int( sys.argv[1] )

    actions = ["+", "?", "-"]
    test_file_name = "tests/01"
    output_file = open("tests/01.t", 'w')
    answer_file = open("tests/01.a", 'w')
    for _ in range(10000):
        keys = dict()
            # Для каждого файла генерируем от 1 до 100000 тестов.
        for _ in range(1000):
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
                    # Если в нашем словаре уже есть такой ключ, то ответе должно быть 
                    # сказано, что он существует, иначе --- успешное добавление.
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