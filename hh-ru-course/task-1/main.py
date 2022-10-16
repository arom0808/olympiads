[n, m, s] = [int(num) for num in input().split(' ')]
first_resume_list, second_resume_list = [], []
for i in range(max(n, m)):
    [a, b] = input().split(' ')
    if a != '-':
        first_resume_list.append(int(a))
    if b != '-':
        second_resume_list.append(int(b))

max_result = 0
count_in_first, count_in_second = 0, 0
money_remained = s

while count_in_first < n:
    if first_resume_list[count_in_first] > money_remained:
        break
    money_remained -= first_resume_list[count_in_first]
    count_in_first += 1
while count_in_second < m:
    if second_resume_list[count_in_second] > money_remained:
        break
    money_remained -= second_resume_list[count_in_second]
    count_in_second += 1

max_result = count_in_first + count_in_second

while count_in_second < m and count_in_first > 0:
    count_in_first -= 1
    money_remained += first_resume_list[count_in_first]
    while count_in_second < m and money_remained > second_resume_list[count_in_second]:
        money_remained -= second_resume_list[count_in_second]
        count_in_second += 1
    if count_in_first + count_in_second > max_result:
        max_result = count_in_first + count_in_second

print(max_result)
