glob_mod = 1000000007


class DpPos(object):
    def __init__(self) -> None:
        self.count_on_positions = [[0 for k in range(max(0, s - 1))] for s in range(9)]
        self.global_count = 0

    def SetFirst(self, a: [int]) -> None:
        self.global_count = len(a)
        for aa in a:
            if len(self.count_on_positions[aa]) > 0:
                self.count_on_positions[aa][0] = 1


def AddNum(dp_pos: DpPos, a: [int]) -> DpPos:
    result = DpPos()
    for cur_pre_num in a:
        if cur_pre_num == 1:
            result.global_count += dp_pos.global_count
        else:
            result.count_on_positions[cur_pre_num][0] = dp_pos.global_count
            for ff in dp_pos.count_on_positions[cur_pre_num]:
                result.count_on_positions[cur_pre_num][0] -= ff
            result.global_count += result.count_on_positions[cur_pre_num][0]
            if len(result.count_on_positions[cur_pre_num]) > 1:
                for i in range(1, len(result.count_on_positions[cur_pre_num])):
                    result.count_on_positions[cur_pre_num][i] = dp_pos.count_on_positions[cur_pre_num][i - 1]
    return result


[n, m] = [int(x) for x in input().split(' ')]
a = [int(x) for x in input().split(' ')]
dp_pos = DpPos()
dp_pos.SetFirst(a)
for i in range(n - 1):
    dp_pos = AddNum(dp_pos, a)
print(dp_pos.global_count % glob_mod)
