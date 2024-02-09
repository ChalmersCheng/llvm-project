#include <stdio.h>
#include <omp.h>
#include <string>
#include <chrono>
#include <iostream>


int main(int argc, char *argv[]){

  omp_set_dynamic(0);     // Explicitly disable dynamic teams
  omp_set_num_threads(4);
  printf("%d\n", omp_get_num_threads());
  int tasks = 100;
  int size = 1000;
  
  
  if (argc >= 3){
  
  	tasks = std::stoi(argv[1]);
  	size = std::stoi(argv[2]); 
  	
  }
  
  double **inMatrix = (double**)malloc(size * sizeof(double*));
  for (int i = 0; i < size; i++){
        inMatrix[i] = (double*)malloc(size * sizeof(double));
  }


  double **outMatrix = (double**)malloc(size * sizeof(double*));
  for (int i = 0; i < size; i++){
        outMatrix[i] = (double*)malloc(size * sizeof(double));
  }

  double maxDiff;
  int count = 0;
  for (int i = 0; i < size; i++)
  	for (int j = 0; j < size; j++)
            inMatrix[i][j] = (double)++count;
  
    std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  auto start1_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(start);
  auto epoch1 = start1_ms.time_since_epoch();


#pragma omp parallel
    {
    #pragma omp single
        {
        	for(int task_it = 0; task_it < tasks; task_it++){
			#pragma omp taskloop
			{
				for (int x = 0; x < size; x++) {
				    for (int y = 0; y < size; y++) {

				    // Start with "self" value
					double sum = inMatrix[x][y];
					int divisor = 1;

				  // Add the neighbors' values to average calculation
					if (x > 0)     { sum += inMatrix[x - 1][y]; divisor++; }
					if (x < size - 1) { sum += inMatrix[x + 1][y]; divisor++; }
					if (y > 0)     { sum += inMatrix[x][y - 1]; divisor++; }
					if (y < size - 1) { sum += inMatrix[x][y + 1]; divisor++; }

				  // Calculate new value, difference, and update maxDiff
					outMatrix[x][y] = sum / ((double)divisor);
					double diff = abs(inMatrix[x][y] - outMatrix[x][y]);
					if (diff > maxDiff) maxDiff = diff;
				    }
				}
			}
			#pragma omp taskwait
			// Swap in and out
        		double** tmp = inMatrix;
     			inMatrix = outMatrix;
       		outMatrix = tmp;
		}
	}
   }
end = std::chrono::system_clock::now();
  auto end1_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(end);
  auto epoch1_end = end1_ms.time_since_epoch();
  std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << epoch1.count() << "\t" <<  epoch1_end.count() << ", execution time: " << elapsed_seconds.count() << "s. "<< std::endl;

	
   printf("tasks=%d,size=%d\n", tasks, size);
}
