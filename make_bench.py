#!/usr/bin/env python

import os
from functools import reduce
import subprocess
import signal

TIMEOUT = 60
INF = 'inf'

def main():
    signal.signal(signal.SIGALRM, timeout)

    data = [['BACKEND', 'NITEMS', 'INSERT', 'SEARCH']]

    backends = ['unsorted', 'sorted', 'bst', 'rbtree', 'treap', 'unordered']
    
    # Append all chained backends
    for lf in ['0.5', '0.75', '1.0', '5.0', '10.0', '100.0']:
        backends.append(f"chained-{lf}")

    # Append all open backends
    for lf in ['0.5', '0.6', '0.7', '0.8', '0.9', '1.0']:
        backends.append(f"open-{lf}")
 
    tests = []
    for back in backends:
        for i in range(1, 8):
            n = 10 ** i
            tests.append({'back': back, 'nitems': str(n)})

    times = {}

    for b in backends:
        times[b] = [0, 0]

    for test in tests:
        args = ['./map_bench', '-b', test['back'], '-n', test['nitems']]
        testData = [test['back'], test['nitems']]

        process = subprocess.Popen(args, stdout=subprocess.PIPE)
        print(f"./map_bench -b {test['back']} -n {test['nitems']}...")
        
        testTimes = times[test['back']]
        print(testTimes)
        if testTimes and testTimes[0] == INF and testTimes[1] == INF:
            testData.append(INF)
            testData.append(INF)
        else:
            i = 0
            while True:
                line = process.stdout.readline()
                if line:
                    line = line.rstrip().decode('ascii').split()
                    time = line[1]
                    try:
                        float(time)
                        if float(time) > TIMEOUT:
                            time = INF
                    except:
                        pass

                    testData.append(time)

                    print(f"{line[0]} {time}")
                    times[test['back']][i] = time
                    i += 1
                else:
                    break
        data.append(testData)

        print(testData)
        print()

    printTable("bench_data.txt", data)


def timeout(signum, frame):
    raise Exception("process took too long")

def widestColumn(data, index):
    return reduce(lambda maxWidth, row: len(str(row[index]))\
            if (len(str(row[index])) > maxWidth) else maxWidth, data, 0) + 2


def printRow(f, row, widths, align='>', filler=' '):
    for i in range(0, len(widths)):
        cell = '' if row is None else row[i]
        string = f'|{cell:{filler}{align}{widths[i]}}'
        f.write(string)
    f.write('|\n')


def printTable(name, data):
    widths = []
    for i in range(0, len(data[0])):
        widths.append(widestColumn(data, i))

    f = open(name, "w+")

    printRow(f, data[0], widths, align='^')
    printRow(f, None, widths, filler='-')

    for row in data[1:]:
        printRow(f, row, widths)

    f.close()


main()
