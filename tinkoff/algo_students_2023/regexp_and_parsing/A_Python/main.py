import re
import sys

REGEX_MASK = r'a+bb+c+'
REGEX_SUB = r'QQQ'

for line in sys.stdin:
    res = re.sub(REGEX_MASK, REGEX_SUB, line)
    print(res, end='')
