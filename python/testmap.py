#!/usr/bin/env python
import json
import sys
import re
import time
import os
import string
import unicodedata
from itertools import groupby

def is_ascii(s):
    return all(ord(c) < 128 for c in s)

def split_line(text, doc, page, index):
    # split the text
    pattern = '. [],;:?!()"--/\_{}'
    match_text = text
    for c in pattern:
        match_text = match_text.replace(c, ' ')
    match_text = match_text.lower()
    matches = [(m.group(0), (m.start(), m.end()-1)) for m in re.finditer(r'\S+', match_text)]
    for m in re.finditer(r'\S+', match_text):
        if(len(m.group(0))):
            temp = unicodedata.normalize('NFKD',unicode \
                             (m.group(0),"ISO-8859-1")) \
                              .encode('ascii', 'ignore')
            if(len(temp)):
                s ='%s\t%s\t%s\t%s\t%s' % (temp, 1, doc, page, index+m.start())
                print s
            

star = 0
start = 0
linec = 0
page = 0
index = 0
doc = 0

# input comes from STDIN (standard input)
for line in open("1.txt"):
    # remove leading and trailing whitespace
    # split the line into words
    linec = linec+1
    words = re.split('[. \[\],;:?!()/"--_]', line)
    if(linec%37==0):
        page=page+1
        index = 0
    for word in words:
        if(len(word)):
            if(star==0 and start==0 and word == 'Title'):
                doc = line.strip() 
            if(word=='GUTENBERG' and words[4]=='START' and words[7]=='PROJECT'):
                star = 1  
            if(word=='GUTENBERG' and words[4]=='END'and words[7]=='END'):
                start = 2
    if(star == 1): 
        start = 1 
        star = 0 
        continue
    if(start==1):
        split_line(line, doc, page, index)
    index = index+len(line)
