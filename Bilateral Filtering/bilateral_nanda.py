
import rawpy
import imageio
import cv2
import os
import matplotlib.pyplot as plt
import math

import numpy as np
from glob import glob
import numpy as np

##################### Bilateral Filtering #####################################

################## 3.1 ######################### 
input_image= cv2.imread("babyelephant.jpg")
Gaussian_Blur=cv2.GaussianBlur(input_image,(3,3),0)
cv2.imwrite("Gaussian_blur.png",Gaussian_Blur)


################## 3.2 #########################

#Split the image into 3 channels
b,g,r= cv2.split(input_image)# wrong ly done as rgb by nanda
b= np.float32(b)
g=np.float32(g)
r=np.float32(r)
sig=50.0
gam=50.0
Bilateral_image= np.zeros((640,640,3))
#w1=np.zeros((5,5))
#w2=np.zeros((5,5))
#w3=np.zeros((5,5))
for q in range (2,638):
    for w in range (2,638):
        wr=0.0
        wg=0.0
        wb=0.0
        Norm_r =0.0
        Norm_g =0.0
        Norm_b =0.0
        for e in range (q-2,q+2):
            for  t in range (w-2,w+2):
                 #Red Channel
                 wr=(1/(2*math.pi*pow(sig,2)))*(np.exp(-((q-e)**2+(w-t)**2)/(2.0*(sig**2))))*(np.exp(-((r[q,w]-r[e,t])**2)/(2.0*(gam**2))))
                 Bilateral_image[q,w,0]= Bilateral_image[q,w,0]+r[e,t]*wr
                 Norm_r=Norm_r+wr
                 #Green Channel
                 wg=(1/(2*math.pi*pow(sig,2)))*(np.exp(-((q-e)**2+(w-t)**2)/(2.0*(sig**2))))*(np.exp(-((g[q,w]-g[e,t])**2)/(2.0*(gam**2))))
                 Bilateral_image[q,w,1]= Bilateral_image[q,w,1]+g[e,t]*wg
                 Norm_g=Norm_g+wg
                 #Blue Channel
                 wb=(1/(2*math.pi*pow(sig,2)))*(np.exp(-((q-e)**2+(w-t)**2)/(2.0*(sig**2))))*(np.exp(-((b[q,w]-b[e,t])**2)/(2.0*(gam**2))))
                 Bilateral_image[q,w,2]= Bilateral_image[q,w,2]+b[e,t]*wb
                 Norm_b=Norm_b+wb
        #Filtered Image for each channel
        Bilateral_image[q,w,0]= Bilateral_image[q,w,0]/Norm_r
        Bilateral_image[q,w,1]= Bilateral_image[q,w,1]/Norm_g       
        Bilateral_image[q,w,2]= Bilateral_image[q,w,2]/Norm_b

cv2.imwrite('bilateral_nanda.jpg', cv2.cvtColor(np.uint8( Bilateral_image),cv2.COLOR_BGR2RGB))
  
