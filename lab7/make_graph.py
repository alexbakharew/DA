import matplotlib.pyplot as plt
import numpy as np

PATH_TIME = "benchmark/"

def load_time(search):
    with open(PATH_TIME + search[0] + ".txt", 'r') as time_fast, \
            open(PATH_TIME + search[1] + ".txt", "r") as time_trivial, \
            open(PATH_TIME + "count", "r") as count_file :
        fast = np.array( [ float(i) for i in time_fast.read().split() ] )
        trivial = np.array( [float(i) for i in time_trivial.read().split() ] )
        count_of_elements = np.array( [ int(i) for i in count_file.read().split() ] )
    return count_of_elements, fast, trivial


if __name__ == '__main__':
    search = ["fast", "trivial"]
    
    count, fast, trivial = load_time(search)

    print(len(fast), len(trivial), len(count))
    print(fast)
    print(trivial)
    print(count)

    line_main, line_ntl = plt.plot(count, fast, 'red', count, trivial, 'blue')

    plt.title(u'Сравнение наивного алгоритма и быстрого!')

    plt.xlabel(u'Количество элементов в матрице')

    plt.ylabel(u'Время')
    plt.legend((line_main, line_ntl),
        (u'fast', u'trivial'), loc="best")
    plt.savefig( 'oneqetnil.png', format='png')
