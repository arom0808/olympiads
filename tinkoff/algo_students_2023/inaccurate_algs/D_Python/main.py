import re
from typing import Union


def main():
    lines = [line.rstrip() for line in open("in.txt", 'r')]
    lines = [(lines[i], lines[i + 1]) for i in range(0, len(lines), 2)]
    lines = [(line[0].replace('}{', ','), line[1]) for line in lines]
    lines = [(re.sub(re.compile('[{} ]'), '', line[0].replace('{', '')), line[1]) for line in lines]
    lines = [(line[0].split(','), line[1]) for line in lines]
    lines = [([(line[0][i], float(line[0][i + 1])) for i in range(0, len(line[0]), 2)], line[1]) for line in lines]
    lines = [(dict(line[0]), line[1]) for line in lines]
    for line in lines:
        line[0]['min_next_n_for_double'] = int(line[0]['min_next_n_for_double'])
    lines: list[tuple[dict[str, Union[float, int]], float]] = [(line[0], float(line[1].split(' ')[1])) for line in
                                                               lines]
    lines.sort(key=lambda x: x[1], reverse=True)
    out_file = open("out.txt", 'w')
    for line in lines:
        out_file.write('long double ')
        res_str = ''
        for value in line[0].items():
            if type(value[1]) is float:
                res_str += value[0] + '=' + str(value[1]) + ','
        res_str = res_str[:-1] + ';\n'
        out_file.write(res_str)
        out_file.write('std::uint32_t ')
        out_file.write('min_next_n_for_double=')
        out_file.write(str(line[0]['min_next_n_for_double']))
        out_file.write(';\n')
        out_file.write('Probability ' + str(line[1]) + '\n')


if __name__ == '__main__':
    main()

# import selenium.webdriver.common.by
# from selenium import webdriver
# from selenium.webdriver.chrome.service import Service
#
# s = Service("C:\\Program Files\\Google\\Chrome\\chromedriver.exe")
# driver = webdriver.Chrome(service=s)
# driver.get("https://ejudge.algocode.ru/cgi-bin/new-client?SID=f02851869f5d6010&action=139&prob_id=4")
# search_bar = driver.find_element(selenium.webdriver.common.by.By.NAME, 'textarea')
