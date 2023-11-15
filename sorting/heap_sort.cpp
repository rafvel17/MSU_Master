#include <iostream>
#include <vector>

using namespace std;

void swap (vector<double>&, int, int);
void heapify (vector<double>&, int, size_t);
void maxHeapBuild (vector<double>&, size_t);
void maxHeapify (vector<double>&, size_t);
void heapSort (vector<double> &, vector<double>::iterator first, vector<double>::iterator last);
vector<double> getArray ();
void printArray (vector<double> const &); 

int main ()
{
    cout << "Insert an array" << endl;
    vector<double> array = getArray();
    cout << "Choose the segment borders" << endl;
    int it1 = 0;
    int it2 = 0;
    cin >> it1 >> it2;
    heapSort(array, array.begin() + it1 - 1, array.begin() + it2 - 1);
    printArray(array);
    return 0;
}





void swap (vector<double>& arr, int i, int j)
{
    double tmp = arr.at(i);
    arr[i] = arr.at(j);
    arr[j] = tmp;
} 

void heapify (std::vector<double>& arr, int i, size_t heapSize)
{
    double max = arr.at(i);
    if (2*i + 1 < heapSize)
    {
        double left = arr.at(2*i + 1);
        if (2*i + 2 < heapSize)
        {
            double right = arr.at(2*i + 2);
            if (max < left || max < right)
            {
                if (left <= right)
                swap(arr, i, 2*i + 2);
            else 
                swap(arr, i, 2*i + 1);
            }
        }
        else if (max < left)
            {
                swap(arr, i, 2*i + 1);
            }
    }
    
}

void maxHeapBuild (std::vector<double>& arr, size_t heapSize)
{
    for (int i = heapSize / 2 - 1; i >= 0; --i)
     	heapify(arr, i, heapSize);
}

void maxHeapify(vector<double>& arr, size_t heapSize)
{
    int i = 0;
    do 
    {
        heapify(arr, i, heapSize);
        i++;
    }
    while (2*i + 1 < heapSize);
}


void heapSort(vector<double> & arr, vector<double>::iterator first, vector<double>::iterator last)
{
    std::vector<double> v;
    for (int i = 0; i <= (last - first); ++i)
        v.push_back(*(first + i));

    size_t heapSize = v.size();
    maxHeapBuild(v, heapSize);
    while (heapSize > 1)
    {
	    swap(v, 0, heapSize - 1);
	    heapSize--;
	    maxHeapify(v, heapSize);
    }
    std::vector<double>::iterator iter = v.begin();
    for (int i = 0; i <= (last - first); ++i)
    {
        arr[first-arr.begin() + i] = v.at(i);
    }
    
}

vector<double> getArray ()
{
    double elem = 0;
    vector<double> array;
    while (elem != -1)
    {   cin >> elem;
        array.push_back(elem);
    }
    return array;
}

void printArray (vector<double> const & arr)
{
    for (auto const& elem : arr)
        cout << elem << " ";
    cout << endl;
}