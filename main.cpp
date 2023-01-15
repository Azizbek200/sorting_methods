#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>

void Insert(int *A,int n)
{
    int i = n,temp;
    temp = A[i];

    while(i>1 && temp > A[i/2])
    {

        A[i] = A[i/2];
        i = i/2;
    }

    A[i] = temp;
}

int HeapSort(int *A,int n)
{

    for(int q=2; q<=n-1; q++)
        Insert(A, q);

    int i, j, x, temp, val;
    for(int d=n-1; d>1; d--)
    {

        val = A[1];
        x = A[d];
        A[1] = A[d];
        A[d] = val;
        i = 1;
        j = i*2;


        while(j <= d-1)
        {
            if(j < d-1 && A[j+1] > A[j])
                j = j+1;


            if(A[i] < A[j])
            {
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
                i = j;
                j = 2*j;
            }
            else
                break;
        }
    }
    return val;
}

//========================================

void Merge(int *A, int B[], int low, int mid, int high)
{
    int i = low, j = mid+1, k = low;

    while (i <= mid && j <= high)
    {
        if (A[i] < A[j])
        {
            B[k++] = A[i++];
        }
        else
        {
            B[k++] = A[j++];
        }
    }
    while (i <= mid)
    {
        B[k++] = A[i++];
    }
    while (j <= high)
    {
        B[k++] = A[j++];
    }
    for (int i=low; i<=high; i++)
    {
        A[i] = B[i];
    }
}

void MergeSort(int *A, int low, int high)
{

    if (low < high)
    {

        int mid = (high+low)/2;

        MergeSort(A, low, mid);
        MergeSort(A, mid+1, high);


        int *b = new int [high+1];
        Merge(A, b, low, mid, high);
    }
}

//========================================

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


int partition(int A[], int low, int high)
{
    int pivot = A[low];
    int i = low + 1;
    int j = high;

    while (true)
    {
        while (i <= j && A[i] <= pivot)
        {
            i++;
        }

        while (A[j] >= pivot && j >= i)
        {
            j--;
        }

          if (j < i)
        {
            break;
        }
        else
        {
            swap(&A[i], &A[j]);
        }
    }

    swap(&A[low], &A[j]);

    return j;
}

void QuickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int p = partition(A, low, high);
        QuickSort(A, low, p-1);
        QuickSort(A, p+1, high);
    }
}

//========================================

using namespace std;

int main()
{
    using chrono::nanoseconds;
    random_device rd;
    mt19937 gen(rd());

    ofstream outputFile("Output1.txt");
    outputFile << "Size              Quick                   Merge              Heap\n";
    outputFile <<"";

    uniform_int_distribution<int> dist(0, 1000);

    auto begin = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();

    nanoseconds total_heap(0), average_heap(0);
    nanoseconds total_quick(0), average_quick(0);
    nanoseconds total_merge(0), average_merge(0);

    std::cout<<"Please wait while the code is running!";
    std::cout<<std::endl;
    std::cout<<"After execution, please check the output file in project directory";
    std::cout<<std::endl;

    for (int N = 0; N < 2500; N = N + 100)
    {
        int* heap_arr = new int [N];
        int* merge_arr = new int [N];
        int* quick_arr = new int [N];
        int* temp = new int [N];

        for(int t = 0; t < 100; t++)
        {

            for(int i=0; i<N; i++)
            {
                temp[i] = dist(gen);
            }

            for(int i=0; i<N; i++)
            {
                heap_arr[i] = temp[i];
                merge_arr[i] = temp[i];
                quick_arr[i] = temp[i];
            }

            begin = std::chrono::steady_clock::now();
            HeapSort(heap_arr,N);
            end = chrono::steady_clock::now();
            nanoseconds time_heap(end - begin);
            total_heap += time_heap;

            begin = std::chrono::steady_clock::now();
            QuickSort(quick_arr, 0, N-1);
            end = chrono::steady_clock::now();
            nanoseconds time_quick(end - begin);
            total_quick += time_quick;

            begin = std::chrono::steady_clock::now();
            MergeSort(merge_arr, 0, N-1);
            end = chrono::steady_clock::now();
            nanoseconds time_merge(end - begin);
            total_merge += time_merge;
        }

        outputFile << N << "\t\t\t" << total_quick.count() / 100 << "\t\t\t"
            << total_heap.count() / 100 << "\t\t\t"
            << total_merge.count() / 100 << endl;

        delete [] merge_arr;
        delete [] heap_arr;
        delete [] quick_arr;
        delete [] temp;
    }

    return 0;
}

