import pandas as pd
import csv
import matplotlib.pyplot as plt
import numpy as np
import statistics

from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)



dynamics = ["d1","d2","d4","d8","d16","d32","d64"]
guided = ["g1","g2","g4","g8","g16","g32","g64"]
static = ["s1","s2","s4","s8","s16","s32","s64"]
labels = ["Dynamic","Static", "Guided"]

fields = ["loop1", "loop2"];

davg = np.array([])
dstd = np.array([])
drange = np.array([])

savg = np.array([])
sstd = np.array([])
srange = np.array([])

gavg = np.array([])
gstd = np.array([])
grange = np.array([])

min_d = 10 
min_s = 10 
min_g = 10
max_s = 0 
max_d = 0 
max_g = 0  
for loop in dynamics:
	data= pd.read_csv('Results/'+loop, sep='\t',header= None, names=fields)
	##############################################################LOOP 1############################
	loop1 = data.loc[:,"loop1"]
	loop1 =  loop1.to_numpy()
	loop1 = np.delete(loop1, 0)
	step = float(5) / 39 
	time = np.arange(1.,6., step)
	loop1 = np.array(loop1)
	loop1 = loop1.astype(float)
	###############################################################################################
	###############################################################################################
	max_= np.amax(loop1)
	min_ = np.amin(loop1)
	if (min_d>min_):
		min_d = min_
	if (max_d<max_):
		max_d = max_	
	avg_ = statistics.mean(loop1)
	std_ = statistics.stdev(loop1)
	range_ = max_d-min_d
	davg =  np.append(davg,avg_)
	dstd = np.append(dstd,std_)
	drange = np.append(drange,max_- min_)


for loop in static:
	data= pd.read_csv('Results/'+loop, sep='\t',header= None, names=fields)
	##############################################################LOOP 1############################
	max_= np.amax(loop1)
	min_ = np.amin(loop1)
	loop1 = data.loc[:,"loop1"]
	loop1 =  loop1.to_numpy()
	loop1 = np.delete(loop1, 0)
	step = float(5) / 39 
	time = np.arange(1.,6., step)
	loop1 = np.array(loop1)
	loop1 = loop1.astype(float)
	###############################################################################################
	###############################################################################################
	if (min_s>min_):
		min_s = min_
	if (max_s<max_):
		max_s = max_	
	avg_ = statistics.mean(loop1)
	std_ = statistics.stdev(loop1)
	range_ = max_s-min_s
	savg =  np.append(savg,avg_)
	sstd = np.append(sstd,std_)
	srange = np.append(srange,max_- min_)



for loop in guided:
	data= pd.read_csv('Results/'+loop, sep='\t',header= None, names=fields)
	##############################################################LOOP 1############################
	max_= np.amax(loop1)
	min_ = np.amin(loop1)
	loop1 = data.loc[:,"loop1"]
	loop1 =  loop1.to_numpy()
	loop1 = np.delete(loop1, 0)
	step = float(5) / 39 
	time = np.arange(1.,6., step)
	loop1 = np.array(loop1)
	loop1 = loop1.astype(float)
	###############################################################################################
	###############################################################################################
	if (min_g>min_):
		min_g = min_
	if (max_g<max_):
		max_g = max_	
	avg_ = statistics.mean(loop1)
	std_ = statistics.stdev(loop1)
	range_ = max_g-min_g
	gavg =  np.append(gavg,avg_)
	gstd = np.append(gstd,std_)
	grange = np.append(grange,max_- min_)


print("\n\nG AVG")
print(gavg)
print (np.amax(gavg))
print (np.amin(gavg))
print("\n\nD AVG")
print(davg)
print (np.amax(davg))
print (np.amin(davg))
print("\n\nS AVG")
print(savg)
print (np.amax(savg))
print (np.amin(savg))

print("\n\nSTD")
print(dstd)
print(gstd)
print(sstd)

print("\n\nRange")
print (np.amax(grange))
print (np.amax(drange))
print (np.amax(srange))

print (np.amin(grange))
print (np.amin(drange))
print (np.amin(srange))

fig, ax = plt.subplots() 

#ax.errorbar([1,2],[avg,2],range,linestyle ='-' ,elinewidth=0.5,capsize =5,capthick=0.5,ecolor= "red", c= "black", marker=".")
# #ax.errorbar([1,2],[avg,2],ste,linestyle ='-' ,elinewidth=0.5,capsize =5,capthick=0.5,ecolor= "red", c= "black", marker=".")

points = [1,2,4,8,16,32,64]
# #Plot the graph
plt.errorbar(points,davg,dstd,fmt = "r",linestyle="solid",linewidth = 1,elinewidth=0.5,capsize =3,capthick=1.5,ecolor="r",marker=".")
plt.errorbar(points,savg,sstd,fmt = "k",linestyle="dotted",linewidth = 1,elinewidth=0.5,capsize =3,capthick=1.5,ecolor= "k",marker=".")
plt.errorbar(points,gavg,gstd,fmt = "g",linestyle="dashed",linewidth = 1,elinewidth=0.5,capsize =3,capthick=1.5,ecolor= "g",marker=".")
plt.legend(labels)

ax.set_xlim(left =0,right=65,auto=True)
ax.set_ylim(bottom=0.4,top=0.6)


ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(1))

ax.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
ax.yaxis.set_major_locator(MultipleLocator(0.025))
ax.yaxis.set_minor_locator(MultipleLocator(0.005))


ax.tick_params(which='minor', length=3, color='black',width=1)
ax.tick_params(which='major', length=10, color='black',width=1.5)

plt.ylabel('Time\nSeconds (s)')
plt.xlabel('Scheduler Chunk Size (N)')
ax.xaxis.set_major_locator(MultipleLocator(10))
ax.xaxis.set_minor_locator(MultipleLocator(1))

# Turn on the minor TICKS, which are required for the minor GRID
ax.grid(which='minor', linestyle=':', linewidth=0.2, color='black')
ax.grid(which='major', linestyle='--', linewidth=0.2, color='red')
ax.grid()
plt.savefig('loop1.eps',format= "eps",dpi=1000)
plt.show()
