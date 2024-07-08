## Analysis of sorting problem

1. quick sort implementation depends on:
- how to choose pivot:
	- first
	- last
	- random (best)
	- meadian of a three (best)
- which scheme to apply:
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

- quick sort is good when we can choose a pivot that 
	- time  θ(n*lg(n))
	- space θ(lg(n))
	- smaller constant that merge sort
```

## errors defined:

* classes of errors:
- eazy (prints message)
- hard (prints message and throw -1)
- fatal(prints message and exit)

```
types of errors		eazy 	hard 	fatal
1. bad index 			x
2. unallocated space 	x
3. nothing to shift 		x
4. no more memory	x	
```


## Data structures themselfs:
1. implementation
- each data structure will cotain the following categories of methods:
	- constructors 
	- iterator methods (e. g. begin, end)
	- specific methods (e. g. insert, remove)
	- constant methods (e. g. get, print)

2. const T& for any T, but not to the return type of a pointer function	

### log:

0. the initial implementation of the heap data structure:
- as_array: bool = false;
- as_btree: bool = true;
- there were 2 abstract classes: heap<T, as_array> and heap<T, as_btree>
- maxheap and minheap were supposed to inherit a template specilised class

- maxheap
	- as_array
	- as_btree
- minheap
	- as_array
	- as_btree

- there are 4 types of heaps and six classes

- i've changed the plan because of the bugs about inheriting template specialised classes
- there will be only two classes: maxheap<T> (represented as an array) and minheap<T> represented as an btree


1. friend functions was an experiemt. they should have existed only for general classes. 
- they are not important i will exclude them from the thinking. only the array class implements those
- each header of a structure will contain a list of potential other useful functions that can be developed

2. new discover: the bug i was tallking about ealier was about intellisens c++ does great at templates

3. why maxheap does not inherit array? no matching methods
