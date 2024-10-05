import matplotlib.pyplot as plt
import math
import numpy as np

R = 1000
C = 10**(-6)

freq_start_hz = 1
freq_stop_hz = 1e8
num_samp_per_decade = 50

freq_list = np.logspace(
    start=math.log10(freq_start_hz), 
    stop=math.log10(freq_stop_hz), 
    num=num_samp_per_decade,
    base = 10
)


magnitude = (1/(R*C) *1/np.sqrt(1 + (R*C*2*math.pi*freq_list)**2))/10e2

plt.figure("Magnitude vs Frequency")
plt.title("Magnitude vs Frequency")
plt.xlabel("Freqency")
plt.ylabel("Magnitude")
plt.yscale('log')
plt.plot(freq_list,magnitude,linestyle = '-',marker = 'o')


phase = (-np.arctan((R*C*2*math.pi*freq_list)))*(180/math.pi)

plt.figure("Phase vs Frequency")
plt.title("Phase vs Frequency")
plt.xlabel("Frequency")
plt.ylabel("Phase")
plt.xscale('log')
plt.plot(freq_list,phase,linestyle = '-',marker = 'o')


plt.show()

