#!usr/bin/python
import os
import json
import sys
import string
import re
import time
cout = 0
test = 0


def split_line(text):
    # split the text
    words = re.split('[. \[\],;:?!()/"--_]', text)
    #print words
    exclude = set(string.punctuation)
    for word in words:
        if(len(word)):
	   if(word=='GUTENBERG' and words[4]=='START'):
	       print 'START'
	       time.sleep(2)
	       return 1
	   if(word=='GUTENBERG' and words[4]=='END'):
	       return 2
    return 0
start = 0
for line in open("1.txt"):
    print line
    test = split_line(line)
    if(test == 1):
       start=1
    elif(test == 2):
       start =2
    if(start==1):
    #start hadoop processing
	cout = cout+1
    elif(start==2):
    #stop hadopp processing
	print 'END'
	sys.exit(0)



