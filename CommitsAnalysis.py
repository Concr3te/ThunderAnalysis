#! /usr/bin/env python
import pandas as pd
import matplotlib.pyplot as plt
data = pd.read_csv('analyzedcommits.txt',header=None,names=['date','frequency'])
data.time = pd.to_datetime(data['date'], format='%Y-%m-%d')
#data.sort_values('date')
data.set_index(['date'],inplace=True)
#data.plot()

#OR 
plt.plot(data.index, data.frequency)
plt.show()