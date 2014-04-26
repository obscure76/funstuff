import sys
import re
import os
import string
from itertools import groupby

count = 0
for line in open('1.txt'):
    count = count + 1
    pattern = '. [],;:?!()"--_'
    if(len(line)):
        print line
        for c in pattern:
    	    line = line.replace(c, ' ')
        for c in pattern:
            line = line.replace(c, ' ')
        print line
        line = line.lower()
        matches = [(m.group(0), (m.start(), m.end()-1)) for m in re.finditer(r'\S+', line)]
        print matches
    if(count == 8):
        sys.exit(0)
    
    


