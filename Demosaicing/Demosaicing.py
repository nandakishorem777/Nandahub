import rawpy
import imageio
import cv2
import numpy as np
from glob import glob


############ Section 1 #################

input_raw= 'tetons.nef'
with rawpy.imread(input_raw) as raw:
   rgb = raw.postprocess()
imageio.imwrite('tetons_original.png',rgb)

########### SubSampling ##################


### Extracting raw input values ###
input_image= rawpy.imread(input_raw)
img_proc= input_image.raw_image

### Extracting each channel ###
r_values=img_proc[::2, ::2]
b_values=img_proc[1::2, 1::2]
g_values=(img_proc[1::2, ::2]+img_proc[::2, 1::2])*0.5  ## Average G channel values ##

## Convert the values to stay between 0 and 255 ##
r_values=(r_values/float(np.max(r_values)))*255.0
g_values=(g_values/float(np.max(g_values)))*255.0
b_values=(b_values/float(np.max(b_values)))*255.0

sub_sample=cv2.merge((b_values,g_values,r_values))
cv2.imwrite("tetons_subsample.png",np.uint8(sub_sample))


############### Nearest Neighbour Demosaicing #####################

Image_nn=cv2.resize(sub_sample, None, fx=2, fy=2, interpolation = cv2.INTER_NEAREST)
cv2.imwrite('tetons_nn.png',Image_nn)

############### Bilinear Interpolation Demosaicing ################
 
Image_bl=cv2.resize(sub_sample, None, fx=2, fy=2, interpolation = cv2.INTER_LINEAR)
cv2.imwrite('tetons_bl.png',Image_bl)

############## Gunturk Method ##################################


g_values1=np.zeros([img_proc.shape[0],img_proc.shape[1]])
for rows in range(2,img_proc.shape[0]-2,1):
    for cols in range(2,img_proc.shape[1]-2,1):
          # Horizontal Gradient
          delta_h=np.abs(((img_proc[rows,cols-2]+img_proc[rows,cols+2])/2)-img_proc[rows,cols])
          # Vertical Gradient
          delta_v=np.abs(((img_proc[rows-2,cols]+img_proc[rows+2,cols])/2)-img_proc[rows,cols])
	  if delta_h>delta_v:
		g_values1[rows,cols]=(img_proc[rows-1,cols]+img_proc[rows+1,cols])/2.0
	  elif delta_h<delta_v:
		g_values1[rows,cols]=(img_proc[rows,cols-1]+img_proc[rows,cols+1])/2.0
	  else:
		g_values1[rows,cols]=(img_proc[rows-1,cols]+img_proc[rows+1,cols]+img_proc[rows,cols-1]+img_proc[rows,cols+1])/4.0


#Gunturk Method for G Channel
g_values_GM=(g_values1/float(np.max(g_values1)))*255.0
#r_values=(r_values/float(np.max(r_values)))*255.0
#b_values=(b_values/float(np.max(b_values)))*255.0

#Bilinear Method for R and B channels
r_values_nn= cv2.resize(r_values, None, fx=2,fy=2,interpolation=cv2.INTER_NEAREST)
b_values_nn= cv2.resize(b_values, None, fx=2,fy=2, interpolation=cv2.INTER_NEAREST)

#Merge the three channels
gunturk_m=cv2.merge((b_values_nn,g_values_GM,r_values_nn))
cv2.imwrite("tetons_dm.png",np.uint8(gunturk_m))


############ Windowing images to observe interpolation effect ########################
gunturk_m=np.uint8(gunturk_m)

crop_nn=Image_nn[1000:1030, 3970:4000]
crop_bl=Image_bl[1000:1030, 3970:4000]
crop_gunturk=gunturk_m[1000:1030, 3970:4000]


cv2.imwrite("cropped_nn.png",crop_nn)
cv2.imwrite("cropped_bl.png",crop_bl)
cv2.imwrite("cropped_gunturk.png",crop_gunturk)



