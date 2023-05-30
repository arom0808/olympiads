import re

raw_str = input()
new_str = re.sub(r'c(?!(i|e|k))', r'k', raw_str)
new_str = re.sub(r'c(i|e)', r's\1', new_str)
new_str = re.sub(r'ck', r'k', new_str)
print(new_str)

# for line in sys.stdin:
#     res = re.sub(REGEX_MASK, REGEX_SUB, line)
#     print(res, end='')
