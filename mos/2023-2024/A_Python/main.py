import pandas as pd
import numpy as np


def datef(d):
    a = d.split('.')
    return a[2] + '-' + a[1] + '-' + a[0]


inp = open('input.txt', 'r')
dates = [a.replace('\t', '\n').split('\n')[:-1] for a in inp.readlines()]
start_dates = [datef(d[0]) for d in dates]
end_dates = [datef(d[1]) for d in dates]
df = pd.DataFrame({'start_date': start_dates, 'end_date': end_dates})
df[['start_date', 'end_date']] = df[['start_date', 'end_date']].apply(pd.to_datetime)
df['diff_days'] = (df['end_date'] - df['start_date']) / np.timedelta64(1, 'D')
out = open('output.txt', 'w')
out.write('\n'.join([str(round(x)) for x in df['diff_days'].tolist()]))
