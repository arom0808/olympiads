import re
import sys

REGEX_MASK = r'\\texttt{(([a-zA-Z]+)|([0-9]+))}'
REGEX_SUB = r'\\begin{bfseries}\1\\end{bfseries}'
for line in sys.stdin:
    res = re.sub(REGEX_MASK, REGEX_SUB, line)
    print(res, end='')