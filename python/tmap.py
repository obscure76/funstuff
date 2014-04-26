#!/usr/bin/env python
import json
import sys
import re
import time
import os
import string
import unicodedata
from itertools import groupby

out = open('map-out.txt', 'w')
def is_ascii(s):
    return all(ord(c) < 128 for c in s)

def split_line(text, page):
    # split the text
    pattern = '. [],;:?!()"--/\_'
    match_text = text
    for c in pattern:
        match_text = match_text.replace(c, ' ')
    """for c in string.punctuation:
        match_text = match_text.replace(c, ' ')"""
    match_text = match_text.lower()
    matches = [(m.group(0), (m.start(), m.end()-1)) for m in re.finditer(r'\S+', match_text)]
    for m in re.finditer(r'\S+', match_text):
        if(len(m.group(0))):
            s ='%s\t%s\t%s\t%s\n' % (m.group(0), 1, page, m.start())
            #print s
            out.write(s)


page = 0
start = 0
star = 0

for line in open("1.txt"):
    words = re.split('[. \[\],;:?!()/"--_]', line)
    # print line
    for word in words:
        if(len(word)):
            if(word=='GUTENBERG' and words[4]=='START' and words[7]=='PROJECT'):
                star = 1
            if(word=='GUTENBERG' and words[4]=='END'and words[7]=='END'):
                start = 2

            temp = unicodedata.normalize('NFKD',unicode \
                                  (word,"ISO-8859-1")) \
			            	.encode('ascii', 'ignore')
            if(not(is_ascii(word))):
                if(temp == 'A'):
                    page = int(words[1]) 
                    #print words, 'page incremented'
    if(star == 1):
        start = 1
        star = 0
        continue
    if(start==2):
        sys.exit()
    if(start==1):
        if(len(line)):
            split_line(line, page)
