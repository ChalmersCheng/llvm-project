# STEER-based OpenMP Taskloop

## Abstract
The STEER (Symmetry-Aware Energy-Efficient Task Scheduler) framework, as proposed by Jing Chen, represents a novel approach towards optimizing task scheduling on cluster-based multicore architectures. Incorporating considerations such as asymmetry in chip design, Dynamic Voltage and Frequency Scaling (DVFS), and task granularity, STEER aims to enhance both energy efficiency and performance metrics.

## Platform Description:
The present study evaluates the STEER scheduler on an asymmetric cluster-based platform, the NVIDIA Jetson TX2, featuring a Dual-Core Denver CPU and a Quad-core A57 Core configuration.

## Test Results:

Performance enhancements are observed when comparing the basic OpenMP taskloop against the STEER taskloop on various application scenarios.
Energy consumption comparisons provide valuable insights into the efficacy of the STEER scheduler.
Conclusion:
The STEER framework demonstrates a nuanced approach towards core-level tuning for multitasking scenarios, resulting in improved energy efficiency and performance.

## Code Explanation:
Below is the function call stack, functions __steerx_taskloop_mapping and __steerx_task_finish responsible for the scheduling and training for STEER.


- __kmpc_taskloop
    - __kmp_taskloop
        - __steerx_taskloop_mapping: This function facilitates the determination of optimal core, width, and frequency settings based on power and performance models, as elaborated in [cite]. Additionally, inline comments provide further insights.
        - __kmp_taskloop_linear
            - __kmp_omp_taskloop_task
            - __kmp_task_start
            - __steerx_task_finish: This function updates the model timetable post-task execution, contributing to improved task execution predictions. Details regarding model training and time updating mechanisms are embedded within this function.

The computational overhead incurred by the taskloop mapping process may lead to an overall increase in time consumption.

## Tools:
Located under the directory /openmp/tools/, the following tools are utilized:

- RAPL (Running Average Power Limit): Facilitates energy profiling through power sampling at various time intervals, providing insights into power consumption dynamics.
- CPU Set: Consists of scripts for setting core frequencies, offering flexibility in adjusting cluster or core frequencies to default or targeted values.
- MB (Memory Boundness): Essential for predicting runtime at different frequencies, obtained through the execution of gen_all_mb.sh and gen_mb.sh scripts.

## Test Cases:
Address: llvm-project/openmp/tests
Current test cases including matrix memory copy, Fibonacci sequence generation, Jacobi, matrix multiplication, and mixed tasks case.

## Implementation Steps:
1. Generate Performance Model
2. Generate Power Model
3. Configure PTT layout file, 
4. Export relevant file addresses to environmental variables.
5. Update chip information defination in the kmp.h header file.
6. Recompile the openmp runtime library and use the new compiled libompd.so.


## Future Work:


1. Energy profiling still has problems to solved. Currently it does not work on AMD. So as the final power profiling on Jetson TX2 is not 
2. The STEER scheduler is currently implemented solely on the OpenMP taskloop pragma. Future endeavors could explore its adaptation to other scheduling primitives to cater to diverse computational scenarios.

## References

- Chen, J., Manivannan, M., Goel, B., Abduljabbar, M., & Pericàs, M. (2022). STEER: Asymmetry-aware Energy Efficient Task Scheduler for Cluster-based Multicore Architectures. In *2022 IEEE 34th International Symposium on Computer Architecture and High Performance Computing (SBAC-PAD)* (pp. 326-335). IEEE. doi:10.1109/SBAC-PAD55451.2022.00043
