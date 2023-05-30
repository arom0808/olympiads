now_queue = [{"id": 1, "exp": 6}, {"id": 2, "exp": 6}, {"id": 3, "exp": 6}]
is_need_add = [False, False, False]
now_process_time = 0
for quant in range(1, 1000):
    if quant == 103 or quant == 203 or quant == 303:
        print(str(quant) + ": " + str(now_queue[0]))
    now_queue[0]["exp"] -= 1
    now_process_time += 1
    if now_queue[0]["exp"] == 0:
        is_need_add[now_queue[0]["id"] - 1] = True
        now_queue.remove(now_queue[0])
        now_process_time = 0
    elif now_process_time >= 3:
        now_queue.append(now_queue[0])
        now_queue.remove(now_queue[0])
        now_process_time = 0
    for i in range(3):
        if is_need_add[i]:
            now_queue.append({"id": i + 1, "exp": 6})
            is_need_add[i] = False

# standard_ip = "192.168.0.0"
# s_standard_ip = ''.join([bin(int(x))[2:].zfill(8) for x in standard_ip.split('.')])
#
# now_ip = input()
# s_now_ip = ''.join([bin(int(x))[2:].zfill(8) for x in now_ip.split('.')])
# print(s_standard_ip)
# print(s_now_ip[:17] == s_standard_ip[:17])

# from functools import cmp_to_key
#
# raw_start_data = """brown	textured leather	1	L
# blue	smooth leather	1	L
# yellow	canvas	3	S
# yellow	waterproof canvas	3	L
# white	canvas	2	S
# black	textured leather	1	S
# black	textured leather	1	M
# blue	smooth leather	3	L
# black	smooth leather	1	M
# white	smooth leather	1	M
# white	textured leather	1	L
# red	smooth leather	1	M
# white	waterproof canvas	2	L
# red	smooth leather	1	L
# red	waterproof canvas	2	S"""
#
# raw_second_data = """black	textured leather	1	S
# black	textured leather	1	M
# black	smooth leather	1	M
# blue	smooth leather	3	L
# blue	smooth leather	1	L
# brown	textured leather	1	L
# red	waterproof canvas	2	S
# red	smooth leather	1	M
# red	smooth leather	1	L
# white	waterproof canvas	2	L
# white	canvas	2	S
# white	smooth leather	1	M
# white	textured leather	1	L
# yellow	canvas	3	S
# yellow	waterproof canvas	3	L"""
#
#
# def ColorComp(it1, it2):
#     if it1[0] < it2[0]:
#         return -1
#     elif it1[0] > it2[0]:
#         return 1
#     return 0
#
#
# def KarmaComp(it1, it2):
#     if it1[2] > it2[2]:
#         return -1
#     elif it1[2] < it2[2]:
#         return 1
#     return 0
#
#
# split_start_data = [x.split('\t') for x in raw_start_data.split('\n')]
# split_second_data = [x.split('\t') for x in raw_second_data.split('\n')]
# for s in split_start_data:
#     s[2] = int(s[2])
# for s in split_second_data:
#     s[2] = int(s[2])
# split_start_data.sort(key=cmp_to_key(KarmaComp))
# split_start_data.sort(key=cmp_to_key(ColorComp))
#
# for i in range(len(split_start_data)):
#     if split_start_data[i] != split_second_data[i]:
#         print(split_start_data[i])
#         print(split_second_data[i])
#         print()
