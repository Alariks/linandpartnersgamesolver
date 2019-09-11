// C++ program to print all permutations using
// Heap's algorithm
#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>

#define N 4 //Change to 0 for full 16! search

using namespace std;

float wpMass[16] = {1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75};

int wpXminus4PreComputed[16];
int wpYminus4PreComputed[16];
float wpRPreComputed[16];
float wpFPreComputed[16][16];
float testx[16];
float testy[16];
float FxPreComputed[16][16];
float FyPreComputed[16][16];
//float FxPreComputed2Items[8][16][16];
//float FyPreComputed2Items[8][16][16];
float FxPreComputed4Items[4][16][16][16][16];
float FyPreComputed4Items[4][16][16][16][16];

float maxSimpleScore = 0;

void initPreCompute()
{
    for(int i=0; i<16; i++) {
        wpXminus4PreComputed[i] = (i%4)*2+1 - 4;
        wpYminus4PreComputed[i] = (i/4)*2+1 - 4;
        wpRPreComputed[i] = sqrt( pow(wpXminus4PreComputed[i],2) + pow(wpYminus4PreComputed[i],2) );
        testx[i] = (1/wpRPreComputed[i]) * wpXminus4PreComputed[i];
        testy[i] = (1/wpRPreComputed[i]) * wpYminus4PreComputed[i];
        for(int j=0; j<16; j++) {
            wpFPreComputed[i][j] = wpMass[j] / pow(wpRPreComputed[i],2);
            FxPreComputed[i][j] = wpFPreComputed[i][j]/wpRPreComputed[i] * wpXminus4PreComputed[i];
            FyPreComputed[i][j] = wpFPreComputed[i][j]/wpRPreComputed[i] * wpYminus4PreComputed[i];
        }
    }

    /*
    for(int i=0; i<16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                if(i%2==0){
                    FxPreComputed2Items[i/2][j][k] = FxPreComputed[i][j] + FxPreComputed[i + 1][k];
                    FyPreComputed2Items[i/2][j][k] = FyPreComputed[i][j] + FyPreComputed[i + 1][k];
                }
            }
        }
    }
    */

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                for (int l = 0; l < 16; l++) {
                    for (int m = 0; m < 16; m++) {
                        if(i%4==0){
                            FxPreComputed4Items[i/4][j][k][l][m] = FxPreComputed[i][j] + FxPreComputed[i + 1][k] + FxPreComputed[i + 2][l] + FxPreComputed[i + 3][m];
                            FyPreComputed4Items[i/4][j][k][l][m] = FyPreComputed[i][j] + FyPreComputed[i + 1][k] + FyPreComputed[i + 2][l] + FyPreComputed[i + 3][m];
                        }
                    }
                }
            }
        }
    }

}

void printArr(int a[],int n) //Prints the array
{
    float Fx = 0;
    float Fy = 0;

    /*
    for(int pos = 0;pos<16;pos++) //Change to 16
    {
        //Fx += wpFPreComputed[pos][a[pos]]/wpRPreComputed[pos] * wpXminus4PreComputed[pos];
        //Fy += wpFPreComputed[pos][a[pos]]/wpRPreComputed[pos] * wpYminus4PreComputed[pos];

        //Fx += wpFPreComputed[pos][a[pos]] * testx[pos];
        //Fy += wpFPreComputed[pos][a[pos]] * testy[pos];

        Fx += FxPreComputed[pos][a[pos]];
        Fy += FyPreComputed[pos][a[pos]];
    }
    //Fx = FxPreComputed[0][a[0]] + FxPreComputed[1][a[1]] + FxPreComputed[2][a[2]] + FxPreComputed[3][a[3]] + FxPreComputed[4][a[4]] + FxPreComputed[5][a[5]] + FxPreComputed[6][a[6]] + FxPreComputed[7][a[7]] + FxPreComputed[8][a[8]] + FxPreComputed[9][a[9]] + FxPreComputed[10][a[10]] + FxPreComputed[11][a[11]] + FxPreComputed[12][a[12]] + FxPreComputed[13][a[13]] + FxPreComputed[14][a[14]] + FxPreComputed[15][a[15]];
    //Fy = FyPreComputed[0][a[0]] + FyPreComputed[1][a[1]] + FyPreComputed[2][a[2]] + FyPreComputed[3][a[3]] + FyPreComputed[4][a[4]] + FyPreComputed[5][a[5]] + FyPreComputed[6][a[6]] + FyPreComputed[7][a[7]] + FyPreComputed[8][a[8]] + FyPreComputed[9][a[9]] + FyPreComputed[10][a[10]] + FyPreComputed[11][a[11]] + FyPreComputed[12][a[12]] + FyPreComputed[13][a[13]] + FyPreComputed[14][a[14]] + FyPreComputed[15][a[15]];
    */
    /*
    for(int pos = 0;pos<8;pos++)
    {
        Fx += FxPreComputed2Items[pos][a[pos*2]][a[pos*2+1]];
        Fy += FyPreComputed2Items[pos][a[pos*2]][a[pos*2+1]];
    }
    */

    for(int pos = 0;pos<4;pos++)
    {
        Fx += FxPreComputed4Items[pos][a[pos*4]][a[pos*4+1]][a[pos*4+2]][a[pos*4+3]];
        Fy += FyPreComputed4Items[pos][a[pos*4]][a[pos*4+1]][a[pos*4+2]][a[pos*4+3]];
    }

    /*
    Fx = FxPreComputed4Items[0][a[0]][a[1]][a[2]][a[3]] + FxPreComputed4Items[1][a[4]][a[5]][a[6]][a[7]] + FxPreComputed4Items[2][a[8]][a[9]][a[10]][a[11]] + FxPreComputed4Items[3][a[12]][a[13]][a[14]][a[15]];
    Fy = FyPreComputed4Items[0][a[0]][a[1]][a[2]][a[3]] + FyPreComputed4Items[1][a[4]][a[5]][a[6]][a[7]] + FyPreComputed4Items[2][a[8]][a[9]][a[10]][a[11]] + FyPreComputed4Items[3][a[12]][a[13]][a[14]][a[15]];
    */

    float simpleScore = Fx*Fx + Fy*Fy; //Modified for faster execution. Result is only calculated below if the score is a record. Actual line: float score = sqrt(Fx*Fx + Fy*Fy);
    if(simpleScore>maxSimpleScore){ //9.684544 for over 311.2
        maxSimpleScore=simpleScore;

        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        std::cout << std::ctime(&end_time);

        for (int i=0; i<n; i++)
            cout << a[i] << " ";
        printf("\n");
        printf("Max Score: %f\n\n", sqrt(simpleScore)*100);
    }
}

void heapPermutation(int a[], int size, int n) // Generating permutation using Heap Algorithm
{
    if (size == 1) // if size becomes 1 then prints the obtained permutation
    {
        printArr(a, n);
        return;
    }

    for (int i=0; i<size; i++)
    {
        heapPermutation(a,size-1,n);

        if (size%2==1) // if size is odd, swap first and last element
            swap(a[0], a[size-1]);

        else // If size is even, swap ith and last element
            swap(a[i], a[size-1]);
    }
}

int main() // Driver code
{
    clock_t begin = clock();

    initPreCompute();

    int index[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int n = sizeof wpMass/sizeof index[0];

    heapPermutation(index, n-N, n);

    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    std::cout << std::ctime(&end_time);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Total Time: " << elapsed_secs;

    return 0;
}
