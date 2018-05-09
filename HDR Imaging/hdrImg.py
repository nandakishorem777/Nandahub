import rawpy
import imageio
import cv2
import numpy as np
from glob import glob


########### Section 2 ##################
import glob
processed=[]
new=[]
images=[] 
processed1=[]
fun=[]

#Appending the inout images in order
for f in range(0,16):
   new.append("exposure"+str(f+1)+".nef")
print len(new)

#Processing the raw images
for i in range(0,len(new)):
   images=rawpy.imread(new[i])
   fun=images.postprocess(gamma=(1,1), no_auto_bright=True, output_bps=16)
   processed.append(fun)

#Saving the processed Images to folder
print len(processed)
for n in range(0,len(processed)):
   filename = "processed_exposure%d.tiff"%(n+1)



for po in range(0,16):
    hug= cv2.imread("processed_exposure"+str(po+1)+".tiff")
    processed1.append(hug)

print len(processed1)

#Downsample the images tofor furthur processing
down_sampled= [cv2.resize(p,(0,0),fx=0.1,fy=0.1) for p in processed1]
 
## To make sure that values stay between 0 and 1##
ds_norm=[c/255.0 for c in down_sampled] 

#tk

tk=[]
for k in range(1,17,1):
   t = (1.0/2048)*(2**(k-1))
   tk.append(t)
#Weight Function

def weg_f(z):
   x= -4 *((z-0.5)**2)/(0.5**2)
   return np.exp(x)

#HDR Algorithm 

[rows,cols,ch]=ds_norm[0].shape
rd=np.zeros((rows,cols))
rn=np.zeros((rows,cols))
bd=np.zeros((rows,cols))
bn=np.zeros((rows,cols))
gd=np.zeros((rows,cols))
gn=np.zeros((rows,cols))

for l in range(len(ds_norm)):
    get_image= ds_norm[l]
    b,g,r=cv2.split(get_image)

    ##### Implementing the product and weight fucntion for each channel    
    r1=weg_f(r)
    g1=weg_f(g)
    b1=weg_f(b)
    
    r2=np.divide(r*r1,tk[l])
    g2=np.divide(g*g1,tk[l])
    b2=np.divide(b*b1,tk[l])
    

    ######Summation for each channel####
    rd= rd+r1
    rn= rn+r2

    gd= gd+g1
    gn= gn+g2
    
    bd= bd+b1
    bn= bn+b2
## HDR Image for each channel ##
I_HDR_R= np.divide(rn,rd)
I_HDR_G= np.divide(gn,gd)
I_HDR_B= np.divide(bn,bd)
     

I_HDR=cv2.merge((I_HDR_B,I_HDR_G,I_HDR_R))



 
### ToneMapping ###

I_HDR_1=I_HDR/(1.0+I_HDR)
cv2.imwrite('HDR_phototonemap.png',np.uint8(I_HDR_1*255))

### Built in Tone Mapping using Opencv ####
tonemap1 = cv2.createTonemapDurand(gamma=2.2)
res_debvec = tonemap1.process(I_HDR.astype('float32'))
res_debvec_8bit = np.clip(res_debvec*255, 0, 255).astype('uint8')

cv2.imwrite('tonemap_opencv.png',res_debvec_8bit)



