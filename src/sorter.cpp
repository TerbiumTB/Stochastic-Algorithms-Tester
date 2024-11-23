#include "../include/sorter.h"
#include "random"
#include "fstream"

void Sorter::insertion_sort(iterator begin, iterator end) {
    for (auto i = begin; i < end; ++i) {
        for (auto j = i; j > begin && *(j - 1) >= *j; --j) {
            std::iter_swap(j - 1, j);
        }
    }
}

void Sorter::merge(iterator left, iterator mid, iterator right) {
    std::vector<int> merged;
    auto l = left;
    auto r = mid;
    while (l != mid && r != right) {
        if (*l <= *r) {
            merged.push_back(*l);
            ++l;
        } else {
            merged.push_back(*r);
            ++r;
        }
    }
    merged.insert(merged.end(), l, mid);
    merged.insert(merged.end(), r, right);

    std::copy(merged.begin(), merged.end(), left);
}


void Sorter::merge_sort(iterator begin, iterator end, int insertion_lvl) {
    if (end - begin <= 1) {
        return;
    }
    if (end - begin <= insertion_lvl) {
        insertion_sort(begin, end);
        return;
    }

    auto mid = begin + (end - begin) / 2;

    merge_sort(begin, mid);
    merge_sort(mid, end);

    merge(begin, mid, end);
}

void HeapSorter::sink(iterator heap, iterator heap_end, int i) {
    while (heap + 2 * i < heap_end) {
        auto j = 2 * i + 1;
        if (heap + j < heap_end && heap[j] < heap[j + 1])
            ++j;

        if (heap[j] <= heap[i])
            break;

        std::iter_swap(heap + j, heap + i);
        i = j;
    }
}

void HeapSorter::sort(iterator begin, iterator end) {
    auto heap_end = end - 1;

    for (auto i = (heap_end - begin) / 2; i >= 0; --i) {
        sink(begin, heap_end, i);
    }

    while (heap_end > begin) {
        std::swap(*begin, *heap_end);
        --heap_end;
        sink(begin, heap_end);
    }
}

void QuickSorter::partition(iterator &left, iterator &right) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<long> distrib(0, (right - left));

    auto pivot = *(left + distrib(mt));

    while (left <= right) {
        while (*left < pivot) {
            ++left;
        }
        while (*right > pivot) {
            --right;
        }

        if (left <= right) {
            std::iter_swap(left++, right--);
        }

    }

    std::swap(right, left);
}

void QuickSorter::_sort(iterator left, iterator right) {
    if (left >= right)
        return;

    auto left_pivot = left;
    auto right_pivot = right;
    partition(left_pivot, right_pivot);

    _sort(left, left_pivot);
    _sort(right_pivot, right);
}


void QuickSorter::sort(iterator begin, iterator end) {
    _sort(begin, end - 1);
}


void IntroSorter::_sort(iterator left, iterator right, int recursion_depth) {
    if (left >= right)
        return;

    if (recursion_depth == _heap_level) {
        _heap.sort(left, right + 1);
        return;
    }

    if (right - left <= _insertion_treshold) {
        _insertion.sort(left, right + 1);
        return;
    }

    auto left_pivot = left;
    auto right_pivot = right;
    partition(left_pivot, right_pivot);

    _sort(left, left_pivot, recursion_depth + 1);
    _sort(right_pivot, right, recursion_depth + 1);
}

void IntroSorter::sort(iterator begin, iterator end) {
    int recursion_depth = 0;
    _heap_level = 2 * std::round(std::log(end - begin));

    _sort(begin, end - 1, recursion_depth);
}

void MergeSorter::sort(iterator begin, iterator end) {
    if (end - begin <= 1) {
        return;
    }
    if (end - begin <= _treshold) {
        _insertion.sort(begin, end);
        return;
    }

    auto mid = begin + (end - begin) / 2;

    sort(begin, mid);
    sort(mid, end);

    merge(begin, mid, end);
}

void MergeSorter::merge(iterator left, iterator mid, iterator right) {
    std::vector<int> merged;
    auto l = left;
    auto r = mid;
    while (l != mid && r != right) {
        if (*l <= *r) {
            merged.push_back(*l);
            ++l;
        } else {
            merged.push_back(*r);
            ++r;
        }
    }
    merged.insert(merged.end(), l, mid);
    merged.insert(merged.end(), r, right);

    std::copy(merged.begin(), merged.end(), left);
}

void MergeSorter::set_insertion_treshold(int treshold) {
    this->_treshold = treshold;
}

void IntroSorter::set_insertion_treshold(int treshold) {
    this->_insertion_treshold = treshold;
}


void InsertionSorter::sort(iterator begin, iterator end) {
    for (auto i = begin; i < end; ++i) {
        for (auto j = i; j > begin && *(j - 1) >= *j; --j) {
            std::iter_swap(j - 1, j);
        }
    }
}