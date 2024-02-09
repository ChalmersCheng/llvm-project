STEER over Omp

## Goals

1. Schedule the task to the best conf, including frequency, running cluster, cluster width.
2. Idle power and runtime power are obtained fron static local files after benchmarks(NAS benchmark).
3. Time is obtained by calculating by MB(memory boundness), which needs to test the ticks(running time) of the highest possble frequency and lowest one, then the approximate running ticks by target MB can be obtained.

To achieve above things, below sub developing tasks should be done.

1. Inits
    - Tasks
        - Load Power model conf
        - load chip layout
        - Calculate Perf Model, in Training part
    1. Power Model
        1. local power model data               Done    Tested
    2. PTT layout
        1. local layout conf                    Done    Tested
    2. Perf Model
        1. calculate perf model by MB           Done    Tested
        
3. Frequency Tunening
    - Tasks
        1. Reset whole chips freq
        2. Tune cluster
    1. Tuning Script, by exporting data into cpu/proc
        - Tuning one core                       Done    Tested
        - Tuning cluster                        Done    Tested
        - Tuning chip                           Done    Tested
        - Reset Freq                            Done    Tested
4. Scheduling
    - Tasks
        - Schedule find-grained task
        - Schedule coarse-grained task
        - Compose find-grained task
    1. Fine-grained task, by looping cluster_id, width
        - Find Best Config(Without DVFS)        Done    Tested
    2. Coares-grained Task, by looping freq_idx, cluster_id, width
        - Find Best Config(With DVFS)           Done    Tested
    3. Fine-grained task composing              NO!!!
        - Hot to detect they are same task or not? 
            - find a buffer to store fine grain, then wait to push? how to know if more fine frain whings comming?
            - by fetching out the work queue from other kernels
            - 
5. Task Queue, Core Binding
    Reusing code from previous ERASE implementation.
6. Generaal Trainning
    - Tasks
        For each cluster
        - Run task on high freq, get time
        - Run task on low freq, get time
        - calculate mb, then fill the time_table, both dimention of freq and width
    - Tuning and running and get time， Done        Tested
    - calculate MB                      Done        Tested
    - Training the whole time_table     Done        Not Tested
    - Finish the trainning offline      No!!!
        - It could be much more convenient and powerful, reduce online training cost.
7. Profiling
    - Tasks
        - Collect time
        - Collect Energy
        - Draw Result
    1. Running time profile
        - collect running time, by cpp chrono                       Done Tested
    2. Energy profile
        - collect CPU power of every minisecond, then power * time  
    3. Profile stats plotting

## This week Progress
1. Finishing code about whole time_table training and updating, but not tested yet.
2. Reading the code about how to compose the tasks together in omp.
3. code about how the trainning part could be done offline 
    - Generate the memory boundedness offline, reducing need for online profiling and trainning
    - With that, it's somewhat simplified at the moment
    - Make more general once accessing a heterogenous platform
    - by gen_mb.sh
4. Finished profiling code from both time and energy.

