"""
Created on Mon Apr 16 14:50:58 2018

@author: liyaxian
"""
#!/usr/bin/env python  
# -*- coding: utf-8 -*-  
import random 
from scipy.interpolate import lagrange
from mlab.releases import latest_release as matlab
 
POLYNOMIAL = 0x1021  
INITIAL_REMAINDER = 0xFFFF  
FINAL_XOR_VALUE = 0x0000  
WIDTH = 16  
TOPBIT = (1 << (WIDTH - 1))  
crcTable = {}  
  
def crcInit():  
    SHIFT = WIDTH - 8  
    for step in range(0, 256):  
        remainder = step << SHIFT  
        for bit in range(8, 0, -1):  
            if remainder & TOPBIT:  
                remainder = ((remainder << 1) & 0xFFFF) ^ 0x1021  
            else:  
                remainder = remainder << 1  
        crcTable[step] = remainder  
  
def crcFast(message, nBytes):  
    crcInit()  
    remainder = 0xFFFF  
    data = 0  
    byte = 0  
    while byte < nBytes:  
        #data = ord(message[byte]) ^ (remainder >> (WIDTH - 8))  
        data = message[byte] ^ (remainder >> (WIDTH - 8))
        remainder = crcTable[data] ^ ((remainder << 8)&0xFFFF)  
        byte = byte + 1  
          
    return hex(remainder)[2: ]  
def random_k(leng):
    mess = []
    for i in range(0,leng):
        #print(i) 0~127
        x = random.randint(0,9)
        if x<5:
            mess.append(0)
        else:
            mess.append(1)
    return mess
def get_ploynomial_px(mess,m_len,crc):
    c = []
    # group = 16
    tmp = 0
    tmp2 = 1
    mess.reverse()
    for i in range(0,m_len):
        if i%16==0 and i!=0:
            c.append(tmp);
            tmp = 0
            tmp2 = 1
        else:
            tmp += mess[i]*tmp2;
            tmp2 =2*tmp2
    crc = int(crc,16);
    c.append(crc);     #c8 c7 c6 ... c0
    c.reverse();        #c0 c1 c3 ... c8
    return c
def feature_points(num):
    # picture size 360*280
    # need change!!!!
    width = 360
    height = 280
    x = []
    for i in range(0,num+1):
        tmpx = random.randint(0,width)
        tmpy = random.randint(0,height)
        #print(tmpx,tmpy)
        tx = "%03d"%(tmpx)
        ty = "%03d"%(tmpy)
        x.append(tx+ty)
        #print(x[i])
    return x

def random_points_y(num):
    # picture size 360*280
    x = []
    for i in range(0,num+1):
        length = random.randint(40,45);
        tmpx = 0
        t0 = 1
        for j in range(0,length):
            tmp = random.randint(0,9);
            tmpx += tmp*t0
            t0 *= 10
        x.append(tmpx)
    return x
def random_points_x(num):
    # picture size 360*280
    width = 360
    height = 280
    x = []
    for i in range(0,num+1):
        tmpx = random.randint(0,width)
        tmpy = random.randint(0,height)
        tx = "%03d"%(tmpx)
        ty = "%03d"%(tmpy)
        x.append(tx+ty)
    return x

def get_pairs_y(x,c):
    y = []
    for i in x:
        tmp = 0
        tmpx = 1
        xi = int(i,10)
        for j in c:
            tmp += tmpx*j
            tmpx *= xi
        y.append(tmp)
    return y
def mix_point(x,y,randx,randy):
    x = x + randx
    y = y + randy
    length = len(x)
    for i in range(0,length):
        x[i] += ","+str(y[i])
        #print(x[i])
    random.shuffle(x)
    return x
## part 1
# random secert 
k_len = 128;
point_num = 20;
random_num = 20;
mess = random_k(k_len);
crc = crcFast(mess,k_len)
print("------ message ------")
print(mess)
print("------ CRC ------")
print(crc)
# get p(x)
c = get_ploynomial_px(mess,k_len,crc);
print("------ c_i in Polynomial P(x) ------")
print(c)
# calculate p(x)
x = feature_points(point_num)
print("------ feature point x ------")
print(x)
# get y
y = get_pairs_y(x,c)
print("------ feature point y ------")
print(y)
# add random points
randx = random_points_x(random_num)
randy = random_points_y(random_num)
print("------ random point x ------")
print(randx)
print("------ random point y ------")
print(randy)
# mix
final = mix_point(x,y,randx,randy)
print("------ final point x,y ------")
print(final)

## part 2
# pretend that x is the new feature point we got
x_int = []
for i in x:
    x_int.append(int(i))
a=lagrange(x_int,y)
print(a)
print(a(1),a(2),a(3))
print(a[0],a[2],a[3])