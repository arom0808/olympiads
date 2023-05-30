f = open("out_100.txt", 'r')
o_t = open("py_out_100.txt", 'w')
o_t.write(' '.join([str(i) for i in range(0, 100)][1:]))
o_t.write('\n')
# [print(f.readline().rstrip('\n')) for i in range(0, 201)]
o_t.write(' '.join([str(int(f.readline().rstrip('\n')) / 50) for _ in range(0, 100)][1:]))
