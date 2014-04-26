import sys 
import cjson
import networkx as nx
import time
import numpy as np
from scipy.sparse import *
import numpy.matlib
import operator
import string


def parse(fname):
    train = open(fname, 'r')
    index = 0 
    abno = []
    lin = 0 
    for line in train:
        lin = lin+1
        words = line.split()
        if(int(words[0]) == 0 or int(words[0]) == 2): 
            index = index +1
            continue
        else:
           abno.append(index)
    print index , lin 

def main(argv):
    if(len(sys.argv)<2):
        print 'usage learn.py <datafile>'
    parse(sys.argv[1])
    return 0

if(__name__ == '__main__'):
    sys.exit(main(sys.argv))
