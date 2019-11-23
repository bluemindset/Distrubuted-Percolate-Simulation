import pandas as pd
import csv
import matplotlib.pyplot as plt
import numpy as np
import statistics
from scipy.interpolate import interp1d
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


fig, ax = plt.subplots() 

x_new = np.linspace(l1600.min(), l1600.max(),500)
f = interp1d(l1600, processes)
y_smooth=f(x_new)


plt.plot(y_smooth,x_new,"-")

x_new1 = np.linspace(l600.min(), l600.max(),500)
f1 = interp1d(l600, processes, kind = "slinear")
y_smooth1=f1(x_new1)

plt.plot(y_smooth1,x_new,"-")

x_new2 = np.linspace(l100.min(), l100.max(),500)
f2 = interp1d(l100, processes)
y_smooth2=f2(x_new2)

plt.plot(y_smooth2,x_new2,"-")

plt.legend(labels)

ax.set_xlim(left =0,right=72,auto=True)
ax.set_ylim(bottom=0,top=10)


ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(1))

ax.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
ax.yaxis.set_major_locator(MultipleLocator(5))
ax.yaxis.set_minor_locator(MultipleLocator(1))


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
plt.savefig('loop1.eps',format= "eps",dpi=1000)
plt.show()
