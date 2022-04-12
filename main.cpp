// program do zadania 3 z SPD - Algorytm NEH
#include <iostream>
#include <fstream>
#include <string>


int cmax(int N, int M, int *P, int *X) //funkcja licząca długość wykonywania zadań
{
	int Cmax[M+1]={0};

	for (int n = 0; n < N; n++)
		for (int m = 1; m <= M; m++)
			Cmax[m] = std::max(Cmax[m],Cmax[m-1]) + P[(m-1)+X[n]*M];
	
	return Cmax[M];
}



void weights(int N, int M, int* P, int* X)
{
	int Weight[N]={0};

	for (int i = 0; i < N; i++)	 //przypisanie wagi każdemu zadaniu
		for (int a = 0; a < M; a++)
			Weight[i] += P[i * M + a];
		
	
	for (int i = 0; i < N - 1; i++)		//sortowanie zadań wagami
		for (int a = 0; a < N - 1; a++)
			if (Weight[a] < Weight[a + 1])
			{
				std::swap(Weight[a], Weight[a + 1]);
				std::swap(X[a], X[a + 1]);
			}
}


int algorithm_NEH(int N, int M, int* P, int* X)
{
	weights(N,M,P,X);

    int position;
    int Cmax;
    
	for (int a = 0; a < N; a++)		
	{
		position = INT16_MIN;
        Cmax = INT32_MAX;

		for (int i = a; i >= 0; i--)
		{
			int tmp = cmax(a+1, M, P, X);
			if (Cmax >= tmp)
			{
				Cmax = tmp;
				position = i;
			}

			if (i!=0)
				std::swap(X[i], X[i - 1]);
			
		}

		for (int i = 0; i < position; i++)
			std::swap(X[i], X[i + 1]);
	}
	return cmax(N, M, P, X);
}


int main()
{
	int N, M; // N - number of tasks, M - number of machines
	int x;    // this variable keep cmax
    int y;

    std::ifstream data("data.txt");
    std::string tmp;
  
    while(tmp!="data.001:")
        data>>tmp;
    


		data >> N;
        data >> M;

        int P[N*M];
        int X[N];

   
		for (int j = 0; j < N * M; j++)		
			data >> P[j];                   //reading all data from file

		for (int j = 0; j < N; j++)
			X[j] = j;                       

		
        x= cmax(N, M, P, X);
        y=algorithm_NEH(N, M, P, X);
		std::cout<<" Cmax: "<<x<<", algorytm NEH: "<< y<<std::endl;
	

	data.close();	
    return 0;	
}
    






