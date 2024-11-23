#include "vector"

#ifndef SET_3_SORTINGS_H
#define SET_3_SORTINGS_H

class Sorter {
private:
    typedef std::vector<int>::iterator iterator;

    void sink(iterator heap, iterator heap_end, int i = 0);

    void merge(iterator, iterator, iterator);

    std::pair<iterator, iterator> partition(iterator left, iterator right);

    void _quick_sort(iterator left, iterator right);

    void _intro_sort(iterator left, iterator right, int recursion_depth, int heap_lvl, int insertion_lvl);

public:
    void insertion_sort(iterator begin, iterator end);

    void merge_sort(iterator begin, iterator end, int = 0);

    void heap_sort(iterator begin, iterator end);

    void quick_sort(iterator begin, iterator end);

    void intro_sort(iterator begin, iterator end);
};

typedef std::vector<int>::iterator iterator;

class ISorter {
public:
    virtual void sort(iterator, iterator) {};
};

class InsertionSorter : public ISorter {
public:
    void sort(iterator, iterator) override;
};

class MergeSorter : public ISorter {
private:
    InsertionSorter _insertion;
    int _treshold;

    static void merge(iterator, iterator, iterator);

public:
    MergeSorter() : _treshold(0) {};

    explicit MergeSorter(int treshold) : _treshold(treshold) {};
    void set_insertion_treshold(int);

    void sort(iterator, iterator) override;
};

class HeapSorter : public ISorter {
private:
    void sink(iterator, iterator, int = 0);

public:
    void sort(iterator, iterator) override;
};

class QuickSorter : public ISorter {
public:
    void _sort(iterator left, iterator right);

protected:
    static void partition(iterator &, iterator &);

public:
    void sort(iterator, iterator) override;
};

class IntroSorter : public QuickSorter {
private:
    int _heap_level;
    int _insertion_treshold;
    HeapSorter _heap;
    InsertionSorter _insertion;

    void _sort(iterator left, iterator right, int = 0);

public:
    IntroSorter() : _heap_level(0), _insertion_treshold(16) {};

    void set_insertion_treshold(int);
    void sort(iterator, iterator) override;
};


#endif //SET_3_SORTINGS_H
