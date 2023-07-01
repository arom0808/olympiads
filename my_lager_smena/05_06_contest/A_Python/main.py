from math import ceil


def ResForThisInput(a: int, x: int, b: int, y: int, z: int):
    if a == 0:
        return ceil(b / (z // y))
    if b == 0:
        return ceil(a / (z // x))
    min_res = 1e9
    for one_x_cnt in range(0, z // x):
        one_y_cnt = (z - (one_x_cnt * x)) // y
        if one_x_cnt > a or one_y_cnt > b or (z - (one_x_cnt * x)) % y != 0:
            t_one_x_cnt, t_one_y_cnt = min(a, one_x_cnt), min(b, one_y_cnt)
            this_res = t_one_x_cnt + t_one_y_cnt + ResForThisInput(a - t_one_x_cnt, x, b - t_one_y_cnt, y, z)
            if this_res < min_res:
                min_res = this_res
        else:
            full_d_cnt = 0
            if one_x_cnt == 0:
                full_d_cnt = b // one_y_cnt
            elif one_y_cnt == 0:
                full_d_cnt = a // one_x_cnt
            else:
                full_d_cnt = min(a // one_x_cnt, b // one_y_cnt)
            ost_x_cnt, ost_y_cnt = a - (full_d_cnt * one_x_cnt), b - (full_d_cnt * one_y_cnt)
            this_res = one_x_cnt + one_y_cnt - 1
            if ost_x_cnt > 0 or ost_y_cnt > 0:
                this_res += ResForThisInput(ost_x_cnt, x, ost_y_cnt, y, z)
            if this_res < min_res:
                min_res = this_res
    return min_res


def main():
    a, x, b, y, z = map(int, input().split(' '))
    print(ResForThisInput(a, x, b, y, z))


main()
