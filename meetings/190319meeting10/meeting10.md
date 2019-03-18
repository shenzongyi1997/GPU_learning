####	Exploration about init_mcpat

when using gdb, break point at init_mcpat, it stops when the application is at half.

the stack 

![1552907483214](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\1552907483214.png)



This is exactly the same as all the init_mcpat in the **begining**.

And I print the variable **wrapper** or **m_gpgpu_sim_wrapper**, they are same. So maybe we can ignore this issue.

####	output of modified GPUWattch

note, **gpgpusim_power_report** is derived from others. So it is blank at present.

There are some small difference, eg.

Maybe the difference is derived from some small parts, like **cycle_time** in **Processor**

But, they are mostly the same



####	nvprof

pc_sample

I think it cannot print every cycle, but can every 5 cycles.

https://docs.nvidia.com/cuda/profiler-users-guide/index.html#profiling-modes

**pc-sampling-period**

nvprof --pc-sampling-period 5 --csv --log-file cycle_nvprof_output.txt --metrics all ./a.out