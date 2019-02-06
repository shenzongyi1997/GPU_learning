First, I try to copy the whole folder ./src/gpuwattch to the server



![1549441249053](C:\Users\workshop\AppData\Roaming\Typora\typora-user-images\1549441249053.png)



After that, try to make directly





![1549441290119](C:\Users\workshop\AppData\Roaming\Typora\typora-user-images\1549441290119.png)

do not know what it means, so try to use nvcc

![1549441587461](C:\Users\workshop\AppData\Roaming\Typora\typora-user-images\1549441587461.png)

Okay, so find the file in ./cacti. and there are also other missing files, also copy them.

and there are other missing files like 'visulizer.h', in gpgpu-sim/, copy too.

![1549441736564](C:\Users\workshop\AppData\Roaming\Typora\typora-user-images\1549441736564.png)

after that, it says missing file 'gpu-sim.h'

I think we do not need it now. Anyway, copy it too.

![1549441937313](C:\Users\workshop\AppData\Roaming\Typora\typora-user-images\1549441937313.png)

still ,missing files.....

There are also many other missing files. Anyway, I try to copy many of them.

But, some files in the gpgpu-sim turns out. It is all about visualizer.h . So I decide to change the file.

First, try not to include it. It is included by processor.h.

![1549442164650](C:\Users\workshop\AppData\Roaming\Typora\typora-user-images\1549442164650.png)

gzFile.... Do not know what it means,  but it is a class.Anyway, // this statement.

![1549442692701](C:\Users\workshop\AppData\Roaming\Typora\typora-user-images\1549442692701.png)

Then, it still says missing files.....So, add all the missing files no matter whether it is in gpgpu-sim/

![1549443068506](C:\Users\workshop\AppData\Roaming\Typora\typora-user-images\1549443068506.png)

Then it says cannot find file 'ROUTER.def'. Seems that this file is not in GPGPU-Sim_dev-half2 this folder.