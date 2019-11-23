import pandas as pd
import csv
import matplotlib.pyplot as plt
import numpy as np
import statistics

from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)





labels = ["L:100, rho:0.5", "L:600, rho:0.5", "L:1600, rho:0.5", "L:3100, rho:0.5"];
runtimes = np.array([])
speedup = np.array([])
processes = np.array([1,4,12,36,72])

l100 = np.array([0.033,0.014,0.009,0.008,0.011])
ls100 = np.array([0.010,0.005,0.001,0.002,0.001])

l600 = np.array([1.152,0.366,0.192,0.126,0.193])
ls600 = np.array([0.010,0.0010,0.003,0.001,0.10])

l1600 = np.array([9.706,2.927,1.412,0.866,0.944])
ls1600 = np.array([0.001,0.002,0.03,0.002,0.002])

l3100 = np.array([44.038,12.851,5.899,3.633,3.080])
ls3100 = np.array([0.02,0.02,0.08,0.002,0.07])

l=np.array([1,0.333/0.01, 1.152/0.192, 9.706/0.866,44.038/ 3.080])



fig, ax = plt.subplots() 

plt.errorbar(processes,l,ls100,fmt = "co",linestyle="dashed",linewidth = 1,elinewidth=0.5,capsize =3,capthick=1.5,ecolor= "k",marker=".")


plt.legend(labels)

ax.set_xlim(left =0,right=72,auto=True)
ax.set_ylim(bottom=0,top=15)


ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(1))

ax.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
ax.yaxis.set_major_locator(MultipleLocator(5))
ax.yaxis.set_minor_locator(MultipleLocator(1))


A = "L = 100", "L = 600","L = 1600","L = 3100"
B = "RHO = 0.5", "RHO = 0.5","RHO = 0.5","RHO = 0.5"
for xy in zip(A,B):                                       # <--
    ax.annotate('(%s, %s)' % xy, xy=xy, textcoords='data') # <--

ax.tick_params(which='minor', length=3, color='black',width=1)
ax.tick_params(which='major', length=10, color='black',width=1.5)

plt.ylabel( "Speed UP")
plt.xlabel("Number of Processes")
ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(1))

# Turn on the minor TICKS, which are required for the minor GRID
ax.grid(which='minor', linestyle=':', linewidth=0.2, color='black')
ax.grid(which='major', linestyle='--', linewidth=0.2, color='red')
ax.grid()

plt.show()
