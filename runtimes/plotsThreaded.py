import pandas as pd
import csv
import matplotlib.pyplot as plt
import numpy as np
import statistics

from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)



threads = ["1","2","4","6","8","12","16"]

fields = ["loop1", "loop2"];
dstd = np.array([])
d2std = np.array([])
davg = np.array([])
ddavg = np.array([])
d2avg = np.array([])
dd2avg = np.array([])

labels = ["loop1()", "loop2()","Ideal"];

for loop in threads:
	data= pd.read_csv('Loop/threads'+loop, sep='\t',header= None, names=fields)
	##############################################################LOOP 1############################
	loop1 = data.loc[:,"loop1"]
	loop1 =  loop1.to_numpy()
	loop1 = np.delete(loop1, 0)
	loop1 = np.array(loop1)
	loop1 = loop1.astype(float)
	
	###############################################################################################
	###############################################################################################
	
	avg_ = statistics.mean(loop1)
	std_ = statistics.stdev(loop1)
	davg =  np.append(davg,avg_)
	dstd = np.append(dstd,std_)
	
runT1 = davg[0]
for avg in davg:
	ddavg = np.append(ddavg,runT1/avg)
print("\n\nG AVG")
print(ddavg)





for loop in threads:
	data= pd.read_csv('Loop/threads'+loop, sep='\t',header= None, names=fields)
	##############################################################LOOP 1############################
	loop1 = data.loc[:,"loop2"]
	loop1 =  loop1.to_numpy()
	loop1 = np.delete(loop1, 0)
	loop1 = np.array(loop1)
	loop1 = loop1.astype(float)
	
	###############################################################################################
	###############################################################################################
	
	avg_ = statistics.mean(loop1)
	std_ = statistics.stdev(loop1)
	d2avg =  np.append(d2avg,avg_)
	d2std = np.append(d2std,std_)
	
runT1 = d2avg[0]
for avg in d2avg:
	dd2avg = np.append(dd2avg,runT1/avg)
print("\n\nG AVG")
print(dd2avg)
dd2avg = np.insert(dd2avg, 0,0)
ddavg = np.insert(ddavg, 0,0)









fig, ax = plt.subplots() 

#ax.errorbar([1,2],[avg,2],range,linestyle ='-' ,elinewidth=0.5,capsize =5,capthick=0.5,ecolor= "red", c= "black", marker=".")
# #ax.errorbar([1,2],[avg,2],ste,linestyle ='-' ,elinewidth=0.5,capsize =5,capthick=0.5,ecolor= "red", c= "black", marker=".")

points = [0,1,2,4,6,8,12,16]
# #Plot the graph
plt.plot(points,ddavg,color= "r",linestyle="solid",linewidth = 1,marker=".")
plt.plot(points,dd2avg,color= "b",linestyle="solid",linewidth = 1,marker=".")
plt.plot(points,points,color= "black",linestyle="--",linewidth = 1,marker=".")


plt.legend(labels)



ax.set_xlim(left =0,right=20,auto=True)
ax.set_ylim(bottom=0,top=20)



ax.yaxis.set_major_locator(MultipleLocator(1))
ax.yaxis.set_minor_locator(MultipleLocator(0.5))


ax.tick_params(which='minor', length=3, color='black',width=1)
ax.tick_params(which='major', length=10, color='black',width=1.5)

plt.ylabel('Speed Up Factor')
plt.xlabel('Number of Threads (N)')
ax.xaxis.set_major_locator(MultipleLocator(5))
ax.xaxis.set_minor_locator(MultipleLocator(1))

# Turn on the minor TICKS, which are required for the minor GRID
ax.grid(which='minor', linestyle=':', linewidth=0.2, color='black')
ax.grid(which='major', linestyle='--', linewidth=0.2, color='red')
ax.grid()

plt.show()
