Insertion sort using Linked list actually making the sorting part worse, as the searching an item in a SLL need to loop over every element until find it. The big Oh notation would be n, and as for every insertion, the element needs to compare with the former one, and there is no better way for SLL to search a node except looping, so in the worse case, for every loop of a single insertion sort, it would cause n^2 time complexity, so it would cause like n^4 times of big Oh notation. 

For DLL, it might be just a little bit easier after finding the first node because it won't need to use loop to search for the one behind it. So the big oh complexity might be n^3.

https://docs.google.com/spreadsheets/d/1Ugm2J2LXal5G4jX2WTIUbz7TLs2j_0kTHEYPE1JfRIY/edit?usp=sharing
