import matplotlib.pyplot as plt
from pylab import *
from matplotlib.font_manager import FontProperties

font = FontProperties(fname='/home/yiming/.local/share/fonts/simsun.ttc', size=14)
names=['32K','64K','128K','256K','512K','1M','2M','4M','8M','16M','32M']
x=range(len(names))
y=[0.999970,0.999939,0.994542,0.796548,0.706105,0.688724,0.688724,0.688724,0.688236,0.688236,0.688236]

plt.ylim(0.5,1.1)
plt.plot(x, y, marker='o', mec='r', mfc='w',label=u'miss rate')
plt.legend()
plt.xticks(x,names)
plt.xlabel('cache 大小',fontproperties=font)
plt.ylabel('miss rate')
plt.title('miss rate随大小变化(trace 2 assoc=1)',fontproperties=font)
plt.savefig('miss_rate-cache_size.png')
plt.show();

names=['1','2','4','8','16','32']
x=range(len(names))
y=[0.688724,0.697994,0.699427,0.702415,0.703787,0.702903]

plt.ylim(0.65,0.75)
plt.plot(x, y, marker='o', mec='r', mfc='w',label=u'miss rate')
plt.legend()
plt.xticks(x,names)
plt.xlabel('assoc 大小',fontproperties=font)
plt.ylabel('miss rate')
plt.title('miss rate随assoc变化(trace 2)',fontproperties=font)
plt.savefig('miss_rate-assoc.png')
plt.show();

