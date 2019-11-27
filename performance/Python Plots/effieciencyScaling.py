import pandas as pd
import csv
import matplotlib.pyplot as plt
import numpy as np
import statistics

from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)



labels = ["L:1000, rho:0.5","L:5000, rho:0.5","L:10000, rho:0.5","Ideal"];
runtimes1 = np.array([0.02617,0.00684,0.00364,0.00203,0.00120,0.00085,0.00078,0.00073,0.00073,0.00078])
runtimes2 = np.array([0.66124,0.16992,0.08736,0.04694,0.02661,0.01618,0.01289,0.01080,0.01044,0.01004])
runtimes3 = np.array([2.63948,0.67885,0.35390,0.19349,0.10279,0.06447,0.04930,0.04010,0.03804,0.03568])
processes = np.array([1,4,8,16,32,64,100,140,160,200])

runtimes1 = np.true_divide(0.02617, runtimes1)
runtimes2 = np.true_divide(0.66124, runtimes2)
runtimes3 = np.true_divide(2.63948, runtimes3)

runtimes1 = np.true_divide(runtimes1, processes)
runtimes2 = np.true_divide(runtimes2, processes)
runtimes3 = np.true_divide(runtimes3, processes)

fig, ax = plt.subplots() 

plt.plot(processes,runtimes1,"o-",marker="*")
plt.plot(processes,runtimes2,"o-",marker="*")
plt.plot(processes,runtimes3,"o-",marker="*")
plt.plot(processes,processes,"o--",marker="*")


plt.legend(labels)

ax.set_xlim(left =0,right=210,auto=True)
ax.set_ylim(bottom=0,top=1)


ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(5))

ax.yaxis.set_major_locator(MultipleLocator(0.1))
ax.yaxis.set_minor_locator(MultipleLocator(0.05))


ax.tick_params(which='minor', length=3, color='black',width=1)
ax.tick_params(which='major', length=10, color='black',width=1.5)

plt.ylabel( "Efficiency")
plt.xlabel("Number of Processes")
ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(1))

# Turn on the minor TICKS, which are required for the minor GRID
ax.grid(which='minor', linestyle=':', linewidth=0.2, color='black')
ax.grid(which='major', linestyle='--', linewidth=0.2, color='red')
ax.grid()
plt.savefig('loop1.eps',format= "eps",dpi=1000)
plt.show()
