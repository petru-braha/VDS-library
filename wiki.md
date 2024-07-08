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
## what should we test?

* we have to take into account the templatised system. we want our design to be as general as possible such that any well defined type (we will describe later a "well defined type") can be stored in our arrangements. in other words, testing primitives has to be accompanied by verifying the same properties with special and complex types. for the simplicity sake, i will define only one complex type, which we'll be used in our analysis.
* each objective of an evaluation will be defined two times; for:
- primitives 
- convoluted types

* primitives considered: int, char, float
* a well defined type has:
- arithmetic operators, such as : <, <=, >, >=, !=, ==, ++, -- (pre and post)

* last remark: there will be a test-based header file for each data structure. we will test the following list of objectives:
- correct initialisation
- there is a test for every specific operation
- there is a test for all the constant methods
- correct error prompts
- existance of other errors, not defined by us
- friend functions if they exist
- TO DO: to determine how many test does this project need for glfw lib and for errors!

## Data structures themselfs:
1. implementation
- each data structure will cotain the following categories of methods:
	- constructors 
	- iterator methods (e. g. begin, end)
	- specific methods (e. g. insert, remove)
	- constant methods (e. g. get, print)

2. const T& for any T, but not to the return type of a pointer function	

## log:

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

4. about node_tree class - i had multiple approaches
- the number of child nodes in template
	- this strategy was automatically implying that children had to have the same number of children as their parent (no more/less)
	- one solution was to define children as "node<T>*" and not "node_tree<T, nr_children>": by some verifications i realised this method was not reliable 
- the number of child nodes non-existent, just in the constructor
- the number of child nodes as a data member (x)

5. iterator class will now be defined inside of the class that uses it