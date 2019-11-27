import pandas as pd
import csv
import matplotlib.pyplot as plt
import numpy as np
import statistics

from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)


labels = ["L:100", "L:400", "L:800", "L:1600","L:3200","L:6400"];
runtimes = np.array([])
speedup = np.array([])
processes = np.array([1,4,8,16,32,64])

weak= np.array([0.49,1.46,2.67, 5.61, 14.63,40.88])
ideal= np.array([0.49,0.49,0.49,0.49,0.49,0.49])


fig = plt.figure()
ax = fig.add_subplot(111)

plt.plot(processes,weak, "-*" 	)
plt.plot(processes,ideal, "-*" 	)
labels2 = ["Grid Size","Ideal"];

plt.legend(labels2)

ax.set_xlim(left =0,right=70,auto=True)
ax.set_ylim(bottom=0,top=200)

ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(1))

ax.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
ax.yaxis.set_major_locator(MultipleLocator(10))
ax.yaxis.set_minor_locator(MultipleLocator(5))



for x,y,z in zip(processes,weak,labels):
	ax.annotate(z, (x-1,y+7))
ax.tick_params(which='minor', length=3, color='black',width=1)
ax.tick_params(which='major', length=10, color='black',width=1.5)

plt.ylabel( "Runtime (Milliseconds)")
plt.xlabel("Number of Processes")
ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(1))

# Turn on the minor TICKS, which are required for the minor GRID
ax.grid(which='minor', linestyle=':', linewidth=0.2, color='black')
ax.grid(which='major', linestyle='--', linewidth=0.2, color='red')
plt.grid()

plt.show()
