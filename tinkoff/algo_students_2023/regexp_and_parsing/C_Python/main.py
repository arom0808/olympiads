import re
import sys

REGEX_MASK = r'\\circle\{\((\d+),(\d+)\)'
REGEX_SUB = r'\\circle{(\2,\1)'
for line in sys.stdin:
    res = re.sub(REGEX_MASK, REGEX_SUB, line)
    print(res, end='')
