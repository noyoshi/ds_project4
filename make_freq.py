#!/usr/bin/env python

import os
from functools import reduce
import subprocess

def main():

    data = [['Backend', 'Text', 'File Size', 'Elapsed Time', 'Memory']]

    backends = ['unsorted', 'sorted', 'bst', 'rbtree', 'treap', 'unordered',\
            'chained', 'open']
 
    files = [
        {'url': 'https://www.gutenberg.org/files/219/219.txt',
            'name': 'heart_of_darkness.txt'},
        {'url': 'https://www.gutenberg.org/files/5200/5200.txt',
            'name': 'metamorphosis.txt'},
        {'url': 'https://www.gutenberg.org/files/10/10.txt',
            'name': 'bible.txt'},
        {'url': 'https://www.gutenberg.org/files/1661/1661.txt',
            'name': 'sherlock.txt'},
        {'url': 'https://www.gutenberg.org/files/6130/6130.txt',
            'name': 'iliad.txt'}
    ]

    try:
        for f in files:
            for back in backends:
                url = f['url']
                name = f['name']

                command = f"./measure ./frequencies -b {back} < texts/{name}"
                fSize = "{} B".format(os.stat(f"texts/{name}").st_size)
                testData = [back, name, fSize]

                print("{}...".format(command))

                process = os.popen(command)

                result = process.readlines()[-1].split()
                time = f"{result[0]} {result[1]}"
                mem = f"{result[2]} {result[3]}"
                print("Time:", time)
                print("Memory:", mem)
                testData.extend([time, mem])

                data.append(testData)

                print()

        printTable("freq_data.txt", data)
    except KeyboardInterrupt:
        printTable("freq_data.txt", data)


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
