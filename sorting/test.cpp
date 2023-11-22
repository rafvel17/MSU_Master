#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <ctime>

using namespace std;

void bubbleSort(
    vector<double>::iterator first, // Beginning of array segment to sort
    vector<double>::iterator last   // After-end of array segment to sort
);
void directSort(
    vector<double>::iterator first,
    vector<double>::iterator last
);

void heapSort(
    vector<double>::iterator first,
    vector<double>::iterator last
);

void bubbleDown(
    vector<double>::iterator first, // Beginning of array segment
    size_t i,       // index of element to sieve in the array segment
    size_t n        // size of the array segment
);

void merge(
    vector<double>::iterator a0,    // Beginning of first array
    vector<double>::iterator a1,    // After-end of first array
    vector<double>::iterator b0,    // Beginning of second array
    vector<double>::iterator b1,    // After-end of second array
    vector<double>::iterator c      // Beginning of resulting array
);

void mergeSortRecursive(
    vector<double>::iterator first, // Beginning of array segment to sort
    vector<double>::iterator last,  // After-end of array segment to sort
    std::vector<double>* tmpMemory = 0  // Temporary memory to use
);

void mergeSortBottomTop(
    vector<double>::iterator first, // Beginning of array segment to sort
    vector<double>::iterator last,  // After-end of array segment to sort
    std::vector<double>* tmpMemory = 0  // Temporary memory to use
);

void printArray(
    vector<double>::iterator first,
    vector<double>::iterator last
);

int main() {
    time_t tim;
    tim = time(&tim);
    srand(int(tim));
    vector<double> a;
    while (true) {
        int n;
        cout << "n: ";
        cin >> n;
        if (n <= 0)
            break;
            
        cout << "Enter number of sorting algorithm:" << endl;
        cout << "1 BubbleSort, 2 DirectSort, 3 HeapSort," << endl;
        cout << "4 Recursive merge sort, 5 Bottom-Top merge sort" << endl;
        int sortAlg;
        cin >> sortAlg;
        
        // Generate a random array of size n
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            double x = (double(rand())/double(RAND_MAX)) * 1000.;
            a[i] = x;
        }
        cout << "Random array:" << endl;
        printArray(a.begin(), a.end());
        cout << "-------------" << endl;

        if (sortAlg == 1)
            bubbleSort(a.begin(), a.end());
        else if (sortAlg == 2)
            directSort(a.begin(), a.end());
        else if (sortAlg == 3)
            heapSort(a.begin(), a.end());
        else if (sortAlg == 4)
            mergeSortRecursive(a.begin(), a.end());
        else if (sortAlg == 5)
            mergeSortBottomTop(a.begin(), a.end());
        else
            continue;
        cout << "Sorted array:" << endl;
        printArray(a.begin(), a.end());
        cout << "-------------" << endl;
    }            
    return 0;
}

void bubbleSort(
    vector<double>::iterator a,     // Beginning of array segment to sort
    vector<double>::iterator last   // After-end of array segment to sort
) {
    bool inversions = true;
    int pass = 0;
    size_t n = last - a;
    while (inversions) {
        inversions = false;
        for (size_t i = 0; i < n-1-pass; ++i) {
            if (a[i] > a[i+1]) {
                std::swap(a[i], a[i+1]);
                inversions = true;
            }
        }
        ++pass;
    }
}

void printArray(
    vector<double>::iterator a,     // Beginning of array segment
    vector<double>::iterator last   // After-end of array segment
) {
    size_t n = last - a;
    if (n <= 1000) {
        // Print all array
        for (size_t i = 0; i < n; ++i) {
            if (i > 0) {
                // Print a delimiter
                if (i%5 == 0)
                    cout << endl;
                else
                    cout << " ";
            }
            cout << a[i];
        }
    } else {
        // The array is too big, print its beginning and end only
        // (100 first and 100 last elements)
        for (size_t i = 0; i < 100; ++i) {
            if (i > 0) {
                // Print a delimiter
                if (i%5 == 0)
                    cout << endl;
                else
                    cout << " ";
            }
            cout << a[i];
        }
        cout << endl << ". . ." << endl;
        for (size_t i = n - 100; i < n; ++i) {
            if (i > n - 100) {
                // Print a delimiter
                if (i%5 == 0)
                    cout << endl;
                else
                    cout << " ";
            }
            cout << a[i];
        }
    }
    cout << endl;
}

void directSort(
    vector<double>::iterator a,     // Beginning of array segment to sort
    vector<double>::iterator last   // After-end of array segment
) {
    size_t n = last - a;
    for (size_t i = 0; i < n-1; ++i) {
        size_t indMin = i;
        for (size_t j = i+1; j < n; ++j) {
            if (a[j] < a[indMin])
                indMin = j;
        }
        if (indMin != i)
            swap(a[i], a[indMin]);
    }
}

// void heapSort(
//     vector<double>::iterator a,     // Beginning of array segment to sort
//     vector<double>::iterator last   // After-end of array segment to sort
// ) {
//     //... to be implemented...
//     cout << "heapSort is not implemented yet..." << endl;

// }    
    
void bubbleDown(
    vector<double>::iterator a, // Beginning of array segment
    size_t i,       // index of element to sieve in the array segment
    size_t n        // size of the array segment
) {
    while (true) {
        size_t s0 = 2*i + 1;
        size_t s1 = s0 + 1;
        if (s0 >= n)
            break;
        // Define elder son
        size_t s = s0;
        if (s1 < n && a[s1] > a[s0])
            s = s1;
        if (a[i] >= a[s])
            break;
        swap(a[i], a[s]);
        i = s;
    }
}

void merge(
    vector<double>::iterator a0,    // Beginning of first array
    vector<double>::iterator a1,    // After-end of first array
    vector<double>::iterator b0,    // Beginning of second array
    vector<double>::iterator b1,    // After-end of second array
    vector<double>::iterator c      // Beginning of resulting array
) {
    while (a0 != a1 && b0 != b1) {
        if (*a0 <= *b0) {
            *c = *a0;
            ++a0;
        } else {
            *c = *b0;
            ++b0;
        }
        ++c;
    }
    
    while (a0 != a1) {
        *c = *a0;
        ++a0; ++c;
    }
    
    while (b0 != b1) {
        *c = *b0;
        ++b0; ++c;
    }
}

void mergeSortRecursive(
    vector<double>::iterator a,     // Beginning of array segment to sort
    vector<double>::iterator last,  // After-end of array segment to sort
    std::vector<double>* tmpMemory /* = 0 */   // Temporary memory to use
) {
    //... to be implemented...
    cout << "mergeSortRecursive is not implemented yet..." << endl;

}

void mergeSortBottomTop(
    vector<double>::iterator first, // Beginning of array segment to sort
    vector<double>::iterator last,  // After-end of array segment to sort
    std::vector<double>* tmpMemory /* = 0 */   // Temporary memory to use
) {
    //... to be implemented...
    cout << "mergeSortBottomTop is not implemented yet..." << endl;

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
        *(first + i) = v.at(i);
    }
    
}