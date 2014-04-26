#!/usr/bin/env python

from operator import itemgetter
import sys

current_word = None
current_count = 0
word = None
lpage =[] 
lindex = []
page = 0
index = 0

# input comes from STDIN
for line in open('map-out.txt'):
    # remove leading and trailing whitespace
    line = line.strip()

    # parse the input we got from mapper.py
    word, count, page, index = line.split('\t', 3)

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
        lindex.append(index)
        lindex.sort()
        if(page not in lpage):
            lpage.append(page)
            lpage.sort()
    else:
        if current_word:
            # write result to STDOUT
            print '%s\t%s\t%s\t%s' % (current_word, current_count, \
                   str(lindex).strip('[]'), str(lpage).strip('[]'))
        current_count = count
        current_word = word
        lpage = []
        lindex = []
        lpage.append(page)
        lindex.append(index)

# do not forget to output the last word if needed!
if current_word == word:
    print '%s\t%s\t%s\t%s' % (current_word, current_count, \
                    str(lindex).strip('[]'), str(lpage).strip('[]'))

