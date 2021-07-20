# Writing Exercises

### 1. Given an array of size 16, what is the maximum possible mixed-up-ness score? Explain why you think this (e.g., give a logical argument or provide an example)

The maximum possible mixed-up-ness (MUN) score should be when the total array is reversed. At this time every two elements are with the wrong order. So we can use C(16, 2) = 120

### 2. What is the worst-case runtime of the brute-force algorithm that you designed? Give a proof (a convincing argument) of this.

The worst case for BF is square of n as there are two nested loops in the design.

### 3. State the recurrence that results from the divide-and-conquer algorithm you designed in Part 3.
The divide part is to divide the array into half for each time, and the conquer part is to let the merge and count part work for sorting and get the value of the MUN value.
