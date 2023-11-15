#include <iostream>
#include <vector>

using namespace std;

void swap (vector<double>&, int, int);
bool heapify (vector<double>&, int);
void maxHeapBuild (vector<double>&, size_t);
void maxHeapify (vector<double>&, size_t);
void heapSort (vector<double>::iterator first, vector<double>::iterator last);
vector<double> getArray ();
void printArray (vector<double> const &); 

int main ()
{
    vector<double> array = getArray();
    heapSort(array.begin(), array.end());
    printArray(array);
    return 0;
}





void swap (vector<double>& arr, int i, int j)
{
    double tmp = arr.at(i);
    arr[i] = arr.at(j);
    arr[j] = tmp;
} 

bool heapify (std::vector<double>& arr, int i)
{
    double max = arr.at(i);
    double left = arr.at(2*i + 1);
    double right = arr.at(2*i + 2);
    if (max < left || max < right)
    {
        if (left <= right)
            swap(arr, i, 2*i + 2);
        else 
            swap(arr, i, 2*i + 1);
        return true;
    }
    else
        return false;
}

void maxHeapBuild (std::vector<double>& arr, size_t heapSize)
{
    for (int i = heapSize / 2 - 1; i >= 0; --i)
     	heapify(arr, i);
}

void maxHeapify(vector<double>& arr, size_t heapSize)
{
    int i = 0;
    bool flag = true;
    do 
    {
        flag = heapify(arr, i);
        i++;
    }
    while ((2*i + 1 < heapSize) && flag == true);
}


void heapSort(vector<double>::iterator first, vector<double>::iterator last)
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
        first + i = iter + i;
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