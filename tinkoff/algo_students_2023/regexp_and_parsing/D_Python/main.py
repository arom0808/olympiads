import re
import sys

REGEX_MASK = r'\$v_(([a-zA-Z0-9])|((?:\{)([a-zA-Z0-9]+)(?:\})))\$'
REGEX_SUB = r'v[\2\4]'
for line in sys.stdin:
    res = re.sub(REGEX_MASK, REGEX_SUB, line)
    print(res, end='')
