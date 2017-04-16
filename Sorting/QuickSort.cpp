/*
    Quick sort
    ----------
    An efficient, comparison-based, in-place, divide and conquer sorting algorithm. It picks
    an element as pivot, partitions the given array around the picked pivot, recursively
    calls itself on those partitions and then merges them after sorting.
    Statistically, for large data sets, it amounts to be the fastest sorting algorithm.

    Time complexity
    ---------------
    Worst case: O(N^2), where N is the number of elements.
    Average case: O(N * log(N)).

    Space complexity
    ----------------
    O(1).
*/

#include <cstdlib>      // rand(), srand()
#include <ctime>        // time()
#include <iostream>
#include <vector>

#include "SortingUtils.hpp"

using namespace std;

size_t partition(vector<int>& values, const size_t start, const size_t end, const int order) {
    // choose a random index between start & end
    size_t random_index = start + (rand() % (end - start + 1));

    // swap the value there with the first value in given range
    swap(values[random_index], values[start]);

    // make that value the pivot element
    int pivot = values[start];

    size_t i = start + 1;
    for (size_t j = start + 1; j <= end; j++)  {
        /*
            place elements which are less than the pivot on one side,
            and those which are greater on the other
        */
        if (order * values[j] < order * pivot) {
            swap(values[i], values[j]);
            i++;
        }
    }

    // place the pivot in its proper place
    swap(values[start], values[i-1]);

    return i-1;     // pivot's index
}

void quick_sort(vector<int>& values, const int start, const int end, const int order, const bool to_show_state) {
    if (start < end) {
        size_t pivot_index = partition(values, start, end, order);

        // sort values to the left of pivot
        quick_sort(values, start, pivot_index-1, order, to_show_state);

        // sort values to the right of pivot
        quick_sort(values, pivot_index+1, end, order, to_show_state);

        if (to_show_state)
            display_state(values);
    }
}

int main() {
    size_t size;
    get_input_size(size);

    vector<int> values(size);
    get_input_values(values, size);

    int order;
    string order_text;
    get_order(order, order_text);

    bool to_show_state;
    get_whether_to_show_state(to_show_state);

    srand(time(0));     // seed PRNG
    quick_sort(values, 0, size-1, order, to_show_state);

    cout << "\nThe values in " << order_text << " order are:\n";
    display_state(values);

    return 0;
}
