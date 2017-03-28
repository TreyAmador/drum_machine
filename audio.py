# testing for audio diagrams
import matplotlib.pyplot as plt
from numpy import arange
from math import log
from math import sin
#import math

def sine_wave(amp):
    return [amp*sin(x) for x in arange(0,50,0.1)]

def find_extrema(wave):
    min,max = -1,1
    for point in wave:
        if point > max:
            max = point
        elif point < min:
            min = point
    return min,max

def compress(thr,ceil,p):
    return -(log(p-thr)/log(log(p-thr)/(ceil-thr)))+thr

amp = 534
c_min,c_max = -128,127
threshold = 0.8*c_max
wave = sine_wave(amp)
min,max = find_extrema(wave)
cmpr = []

for p in wave:
    if p > threshold:
        cmpr.append(compress(threshold,c_max,p))
    else:
        cmpr.append(p)


plt.figure(1)
plt.subplot(111)
plt.plot(cmpr,lw=2)
plt.show()








'''
# testing for audio diagrams
import matplotlib.pyplot as plt
from math import sin
from numpy import arange

def sine_wave(amp):
    return [amp*sin(x) for x in arange(0,50,0.1)]

def find_extrema(wave):
    min,max = -1,1
    for point in wave:
        if point > max:
            max = point
        elif point < min:
            min = point
    return min,max

def compress(wave,factor,min,c_min):
    return [(x-min)*factor+c_min for x in wave]

amp = 534
c_min,c_max = -128,127
wave = sine_wave(amp)
min,max = find_extrema(wave)
# check if max > 127 and min < -127
# if so, compress!
factor = (c_max-c_min)/(max-min)
cmpr = compress(wave,factor,min,c_min)
print(find_extrema(cmpr))

plt.figure(1)
plt.subplot(111)
plt.plot(cmpr,lw=2)
plt.show()
'''



'''

def sine_wave(amp):
    return [amp*sin(x) for x in arange(0,50,0.1)]


def find_max(wave):
    max = 1
    for point in wave:
        if point > max:
            max = point
    return max


def find_min(wave):
    min = -1
    for point in wave:
        if point < min:
            min = point
    return min


def increment_wave(wave,min):
    return [x-min for x in wave]


def decrement_wave(wav,min):
    return [x+min for x in wav]


def compress_wave(wave,factor):
    return [factor*x for x in wave]


amp = 534
c_min,c_max = -128,127

sine = sine_wave(amp)
min = find_min(sine)
incr = increment_wave(sine,min)
max = find_max(incr)
factor = (c_max-c_min) / max
cmpr = compress_wave(incr,factor)
wave = decrement_wave(cmpr,c_min)

max = find_max(wave)
min = find_min(wave)

print(max)
print(min)

plt.figure(1)
plt.subplot(111)
plt.plot(wave,lw=2)
plt.show()

'''


'''

#def spectra(min,max):
#    return [randint(min,max) for _ in range(100)]


def sine_wav(amp):
    return [amp*sin(x) for x in arange(0,50,0.1)]


max = 127
T = 0.8
Tm = T*max
sine = sine_wav(max*2)
compr = []


for sin in sine:
    if sin > Tm:
        compr.append(Tm+log(sin-Tm,1.1))
    elif sin < -Tm:
        compr.append(-Tm-log(-(sin+Tm),1.1))
    else:
        compr.append(sin)


plt.figure(1)
plt.subplot(211)
plt.plot(sine,lw=2)
plt.subplot(212)
plt.plot(compr,lw=2)
plt.show()

'''



'''

#min,max = -128,127
min,max = 0,255
wav01 = spectra(min,max)
wav02 = spectra(min,max)
wav03 = spectra(min,max)

wav123 = [x+y+z for x,y,z in zip(wav01,wav02,wav03)]

'''

'''

T = 20*math.log10(127)*0.8
R = 5
W = 4 # assumption of knee

x = [0 for _ in wav123]
Fs = 44100
Tr = 0.2
Ta = 0.05
gsi = 0
for (n,w) in enumerate(wav123):
    xdB = 20*math.log10(math.fabs(w))
    if T-(W/2) <= xdB <= T+(W/2):
        xsc = xdB + (1/R-1)*((xdB-T+(W/2))**2)/(2*W)
    elif xdB > T+(W/2):
        xsc = T+(xdB-T)/R
    else:
        xsc = xdB
    aA = math.e**(-math.log10(9)/(Fs*Ta))
    aR = math.e**(-math.log10(9)/(Fs*Tr))
    gc = xsc - xdB
    if gc > gsi:
        gs = aA*gsi+(1-aA)*gc
    else:
        gs = aR*gsi+(1-aR)*gc
    gsi = gs
    M = 0
    if xdB == 0:
        M = -xsc
    gm = gs+M
    gHn = 10**(gm/20)
    y = w*gHn
    x[n] = y

#print(x)

'''


'''

plt.figure(1)
plt.subplot(211)
plt.plot(wav123,lw=2)
plt.subplot(212)
plt.plot(x,lw=2)
plt.show()

'''

