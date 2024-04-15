from tkinter import *

canvas_width = 500
canvas_height = 500

# def paint(event):
#     python_green = "#476042"
#     x1, y1 = (event.x - 1), (event.y - 1)
#     x2, y2 = (event.x + 1), (event.y + 1)
#     w.create_oval(x1, y1, x2, y2, fill=python_green)


master = Tk()

p1, p2, p3 = (300, 300), (300, -300), (-300, -300)
w = Canvas(master, width=500, height=500, background="white")
w.pack()

po = (0, 0)

for i in range(100000):
    w.create_rectangle(po[0], po[1], po[0] + 10, po[1] + 10, fill="blue")
    if i % 3 == 0:
        po = (po[0] + p1[0] / 2, po[1] + p1[1] / 2)
    elif i % 3 == 1:
        po = (po[0] + p2[0] / 2, po[1] + p2[1] / 2)
    else:
        po = (po[0] + p3[0] / 2, po[1] + p3[1] / 2)

mainloop()

# def main():
#     day, month, year = map(int, input().split('.'))
#     dim = 31
#     if month == 4 or month == 6 or month == 9 or month == 11:
#         dim = 30
#     elif dim == 2:
#         dim = 29 if (year % 4 == 0 and year % 100 != 0) or year % 400 == 0 else 28
#     if day < 1 or month < 1 or month > 12 or day > dim:
#         print("WRONG DATE")
#         return
#     if day == dim:
#         if month == 12:
#             day, month, year = 1, 1, year + 1
#         else:
#             day, month = 1, month + 1
#     else:
#         day += 1
#     print(('0' if day < 10 else '') + str(day) + '.' + ('0' if month < 10 else '') + str(month) + '.' + str(year))
# 
# 
# main()
