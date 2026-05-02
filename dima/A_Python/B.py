import json
import urllib.error
import urllib.parse
import urllib.request
from functools import cmp_to_key


def compare(a, b):
    if a[1] < b[1]:
        return -1
    if a[1] > b[1]:
        return 1
    if a[0] < b[0]:
        return -1
    if a[0] > b[0]:
        return 1
    return 0


def magic_help(s: str, server=('127.0.0.1', 8080), match=1):
    with urllib.request.urlopen('http://' + server[0] + ':' + str(server[1]) + '/') as url:
        data = json.load(url)
        els = []
        for el in data:
            a, b = set(s), set(el['event'])
            matches = len([e for e in a if e in b])
            if matches < match:
                continue
            els.append([', '.join(el['helpers']), el['usefulness']])
        return sorted(els, key=cmp_to_key(compare))


print(magic_help('WONKA'))

# with urllib.request.urlopen('http://ip.jsontest.com/') as url:
#         data = json.loads('''[
#   {
#     "event": "WATER",
#     "helpers": [
#       "elf",
#       "golem",
#       "pixie",
#       "helga"
#     ],
#     "usefulness": 7
#   },
#   {
#     "event": "OIL",
#     "helpers": [
#       "goblin",
#       "brownie",
#       "dwarf"
#     ],
#     "usefulness": 7
#   },
#   {
#     "event": "HERDING",
#     "helpers": [
#       "brownie",
#       "hag"
#     ],
#     "usefulness": 5
#   },
#   {
#     "event": "CLEAN",
#     "helpers": [
#       "brownie",
#       "helga",
#       "figle",
#       "hag",
#       "goblin"
#     ],
#     "usefulness": 5
#   },
#   {
#     "event": "FIRE",
#     "helpers": [
#       "dwarf",
#       "pixie",
#       "elf",
#       "hag",
#       "merman"
#     ],
#     "usefulness": 3
#   }
# ]''')
