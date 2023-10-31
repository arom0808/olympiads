res = set()
for a in range(1, 8):
    for b in range(1, 8):
        for c in range(1, 8):
            for d in range(1, 8):
                m = min(a * 1000 + b * 100 + c * 10 + d, b * 1000 + c * 100 + d * 10 + a,
                        c * 1000 + d * 100 + a * 10 + b, d * 1000 + a * 100 + b * 10 + c)
                res.add(m)
print(res)
