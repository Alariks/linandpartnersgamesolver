// C++ program to print all permutations using
// Heap's algorithm
#include <iostream>
#include <cmath>
#include <ctime>
#include <thread>

#define N 1 //Change to 1 for full (cumulative, with 16 threads) 16! search

using namespace std;

float wpRInverseBxWpXminus4ByWpRwithoutSqrtInverted[16];
float wpRInverseByWpYminus4ByWpRwithoutSqrtInverted[16];

float maxSimpleScore = 0;

void initPreCompute()
{
    int wpXminus4PreComputed[16];
    int wpYminus4PreComputed[16];
    float wpRwithoutSqrtPreComputed[16];
    float wpRPreComputed[16];
    float wpRwithoutSqrtInvertedPreComputed[16];
    float wpRInverseByWpXminus4[16];
    float wpRInverseByWpYminus4[16];

    for(int i =0; i<16; i++)
    {
        wpXminus4PreComputed[i] = (i%4)*2+1 - 4;
        wpYminus4PreComputed[i] = (i/4)*2+1 - 4;
        wpRPreComputed[i] = sqrt(pow(wpXminus4PreComputed[i],2) + pow(wpYminus4PreComputed[i],2));
        wpRwithoutSqrtPreComputed[i] = pow(wpRPreComputed[i],2);
        wpRwithoutSqrtInvertedPreComputed[i] = 1/wpRwithoutSqrtPreComputed[i];
        wpRInverseByWpXminus4[i] = (1/wpRPreComputed[i])*wpXminus4PreComputed[i];
        wpRInverseByWpYminus4[i] = (1/wpRPreComputed[i])*wpYminus4PreComputed[i];
        wpRInverseBxWpXminus4ByWpRwithoutSqrtInverted[i] = wpRInverseByWpXminus4[i] * wpRwithoutSqrtInvertedPreComputed[i];
        wpRInverseByWpYminus4ByWpRwithoutSqrtInverted[i] = wpRInverseByWpYminus4[i] * wpRwithoutSqrtInvertedPreComputed[i];
    }
}

void printArr(float a[]) //Prints the array
{
    float Fx = 0;
    float Fy = 0;
    //float wpF = 0;

    for(int pos = 0;pos<16;pos++)
    {
        //wpF = a[pos] / wpRwithoutSqrtPreComputed[pos];
        //wpF = a[pos] * wpRwithoutSqrtInvertedPreComputed[pos];

        //Fx += wpF * wpRInverseByWpXminus4[pos];
        //Fy += wpF * wpRInverseByWpYminus4[pos];

        Fx += a[pos] * wpRInverseBxWpXminus4ByWpRwithoutSqrtInverted[pos];
        Fy += a[pos] * wpRInverseByWpYminus4ByWpRwithoutSqrtInverted[pos];
    }

    float simpleScore = Fx*Fx + Fy*Fy; //Modified for faster execution. Result is only calculated below - if the score is a record. Actual line: float score = sqrt(Fx*Fx + Fy*Fy);
    if(simpleScore >= maxSimpleScore)
    {
        maxSimpleScore = simpleScore;

        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        std::cout << std::ctime(&end_time);

        for (int i=0; i<16; i++)
            cout << a[i] << " ";
        printf("\n");

        printf("Fx: %f\n", Fx);
        printf("Fy: %f\n", Fy);
        printf("Max Score: %f\n\n", sqrt(simpleScore)*100);
    }
}

void heapPermutation(float a[], int size) // Generating permutation using Heap Algorithm
{
    if (size == 1) // if size becomes 1 then prints the obtained permutation
    {
        printArr(a);
        return;
    }

    for (int i=0; i<size; i++)
    {
        heapPermutation(a,size-1);

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

    float wpMass[16] = {1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75}; //Change to 16
    int n = sizeof wpMass/sizeof wpMass[0];

    float t1[16] = {1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75};
    float t2[16] = {4.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5};
    float t3[16] = {4.5,4.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25};
    float t4[16] = {4.25,4.5,4.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4};
    float t5[16] = {4,4.25,4.5,4.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75};
    float t6[16] = {3.75,4,4.25,4.5,4.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5};
    float t7[16] = {3.5,3.75,4,4.25,4.5,4.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25};
    float t8[16] = {3.25,3.5,3.75,4,4.25,4.5,4.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3};
    float t9[16] = {3,3.25,3.5,3.75,4,4.25,4.5,4.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75};
    float t10[16] = {2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,1,1.25,1.5,1.75,2,2.25,2.5};
    float t11[16] = {2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,1,1.25,1.5,1.75,2,2.25};
    float t12[16] = {2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,1,1.25,1.5,1.75,2};
    float t13[16] = {2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,1,1.25,1.5,1.75};
    float t14[16] = {1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,1,1.25,1.5};
    float t15[16] = {1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,1,1.25};
    float t16[16] = {1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,1};
    thread one (heapPermutation, t1, n-N);
    thread two (heapPermutation, t2, n-N);
    thread three (heapPermutation, t3, n-N);
    thread four (heapPermutation, t4, n-N);
    thread five (heapPermutation, t5, n-N);
    thread six (heapPermutation, t6, n-N);
    thread seven (heapPermutation, t7, n-N);
    thread eight (heapPermutation, t8, n-N);
    thread nine (heapPermutation, t9, n-N);
    thread ten (heapPermutation, t10, n-N);
    thread eleven (heapPermutation, t11, n-N);
    thread twelve (heapPermutation, t12, n-N);
    thread thirteen (heapPermutation, t13, n-N);
    thread fourteen (heapPermutation, t14, n-N);
    thread fifteen (heapPermutation, t15, n-N);
    thread sixteen (heapPermutation, t16, n-N);
    one.join();
    two.join();
    three.join();
    four.join();
    five.join();
    six.join();
    seven.join();
    eight.join();
    nine.join();
    ten.join();
    eleven.join();
    twelve.join();
    thirteen.join();
    fourteen.join();
    fifteen.join();
    sixteen.join();

    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    std::cout << std::ctime(&end_time);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Total Time: " << elapsed_secs;
    return 0;
}
