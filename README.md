# workout


|file name | description |
|--------- | ----------- |
|_nth_fibonacci_number.cpp_ | Implemented a function to calculate the __nth__ number in the _fibonacci sequence_. Calculating largger(>=50) values take a longer time to compute with the standard method. This version uses _memoization_ technique to speed up computation and it works well :).|
|_grid_traveler.cpp_ | The code here return the maximum number of posible ways to travel through a grid of __m * n__. It is designed with _memoization_ technique so it returns results faster.|
|_can_sum.cpp_ | Confirms wether a target value can be generated using a given array of numbers. We may use any element of the array, as many times as preferred and consider all elements to be positve values.  If can_sum(target, v) function were a member function of a class, I would move the lines from the __range-based__ `for` to the end of the function into a new function to help clean up the implementation. I did not do it here, to prevent __forward declearation__.|
|_can_sum_r.cpp_ | This is a revised version of what is happening in _can_sum.cpp_. In this scenario, we may use only one element of the array, as many times as preferred or any pair, once.|
|_how_sum.cpp_ | Displays one of the combination(s) used in generating the target sum as in the __can_sum.cpp__ file.|
|_best_sum.cpp_ | This version of the `can_sum` function show the first shortest possible combination for generating the target sum.|
|_can_construct.cpp_ | Trying to construct a target string from an array of given words. We can use each word in the array, as many times as needed.|
|_count_construct.cpp_ | Building on __can_construct.cpp__, we find the maximum number of ways the target string can be constructed.|
|_all_construct.cpp_ | Also progressing on __count_construct.cpp__, displays all the possible ways of constructing the target string, an empty list otherwise.|
|_missing_number.cpp_ | Finding the missing number in a given integer array of 1 to 100.|
|_insertion_sort.cpp_ | Implements an insertion sort algorithm - elements in the container will be arranged in ascending order.|
|_swap_without_temp.cpp_ | Swapping two numbers or char types without introducing a third variable. __Updated__ function `swap_without_temp` to support `std::string`s.|