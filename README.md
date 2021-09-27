# workout


|file name | description |
|--------- | ----------- |
|_nth_fibonacci_number.cpp_ | Implemented a function to calculate the __nth__ number in the _fibonacci sequence_. Calculating largger(>=50) values take a longer time to compute with the standard method. This version uses _memoization_ technique to speed up computation and it works well :).|
|_grid_traveler.cpp_ | The code here return the maximum number of posible ways to travel through a grid of __m * n__. It is designed with _memoization_ technique so it returns results faster.|
|_can_sum.cpp_ | Confirms wether a target value can be generated using a given array of numbers. We may use any element of the array, as many times as preferred and consider all elements to be positve values.  If can_sum(target, v) function were a member function of a class, I would move the lines from the __range-based__ `for` to the end of the function into a new function to help clean up the implementation. I did not do it here, to prevent __forward declearation__.|
|_can_sum_r.cpp_ | This is a revised version of what is happening in _can_sum.cpp_. In this scenario, we may use only one element of the array, as many times as preferred or any pair, once.|
