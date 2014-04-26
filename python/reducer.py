#!/usr/bin/env python

from operator import itemgetter
import sys

current_word = None
current_count = 0
word = None
lpage = []
lindex = {}
index = 0
page = 0

# input comes from STDIN
for line in sys.stdin:
    # remove leading and trailing whitespace
    line = line.strip()

    # parse the input we got from mapper.py
     #word, count = line.split('\t', 1)
    if(len(line.split('\t'))<4):
        continue
    word, count, page, index = line.split('\t', 4)

    # convert count (currently a string) to int
    try:
        count = int(count)
        page = int(page)
        index = int(index)
    except ValueError:
        # count was not a number, so silently
        # ignore/discard this line
        continue

    # this IF-switch only works because Hadoop sorts map output
    # by key (here: word) before it is passed to the reducer
    if current_word == word:
        current_count += count
        if(page not in lpage):
            lpage.append(page)
            lindex[page]=[]
            lpage.sort()
        lindex[page].append(index)
        lindex[page].sort()
    else:
        if current_word:
            # write result to STDOUT
             #print '%s\t%s' % (current_word, current_count)
            print '\n\n'
            print '%s\t%s' % (current_word, current_count)
            for row in range(len(lpage)):
                print lpage[row]
                print lindex[lpage[row]]
        current_count = count
        current_word = word
        lpage = []
        lindex = {}
        lpage.append(page)
        lindex[page]=[]
        lindex[page].append(index)

# do not forget to output the last word if needed!
if current_word == word:
    #    print '%s\t%s' % (current_word, current_count)
    print '\n\n'
    print '%s\t%s' % (current_word, current_count)
    for row in range(len(lpage)):
        print lpage[row]
        print lindex[lpage[row]]
    #print '%s\t%s\t%s\t%s' % (current_word, current_count, \
                        #str(lindex).strip('[]'), str(lpage).strip('[]'))

