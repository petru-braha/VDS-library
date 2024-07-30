## I. S.O.L.I.D. principles summary:

- S - single-responsibility - each class has only one job
- O - open-close - open to add more, don't change existent
- L - Liskov     - behavioral subtype
- I - interface-segregation - a derived class implements and uses all its base's methods 
- D - dependency-inversion  - high-level modules should not depend on low level modules

## II. Operations of dynamic sets:

1. queries:
- return a pointer to required data or NULL if it does not exist
	- search 
	- minimum
	- maximum
	- predecessor - as value
	- successor - as value
2. modifiers:
- their parameter is a pointer
	- insert
	- delete 
```
		array   linked_list   stack   queue   maxheap   minheap   trivial_tree   avl   red_black_tree   trie   graph   collection   map
comparef	x	x
rotation	
constructors 	x	x	     

begin
end

operator =
clear

sort		x	x
insert		x	x		
remove		x	x		

search
minimum		x	x
maximum		x	x
successor	x	x
predecessor	x	x
```

## III. Structures interaction:

- if we are able to transform types into the data composition itself and back we solved the problem. the next question will be what would be the shape of the returned primitive? it must be primitive enough such that it can be converted back to a structure, but not the most primitive, such that we can lose functionality. think of a stack of queues of ints. to retrieve the data from the stack it is enough to return the top queue, and not an block of memory with ints. transforming this into code logic: for each structure there will be a transform method which will return a block of memory, a copy of the data contained by the data storage.

## IV. Analysis of quick-sort:

1. how to choose pivot:
	- first
	- last
	- random (best)
	- median of a three (best)
2. which scheme to apply:
	- Lomuto - semi-stable
		 - linked lists
	- Hoare	 - unstable
		 - bidirectionality
		 - less comparisons
```
algorithm	quick sort		merge sort		heap sort

time		O(n^2)			O(n*lg(n))		O(n*lg(n))			
space		O(n)			O(n)			O(1)
stability	unstable		stable			unstable
requirements 	none			stability		space restrictions
```
3. quick sort is preferable when a random pivot is chosen, close to the mean of the partition
	- time  θ(n*lg(n))
	- space θ(lg(n))
	- smaller constant that merge sort