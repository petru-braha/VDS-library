## Classes of errors:
- eazy (prints message)
- hard (prints message and throw -1)
- fatal(prints message and exit)

- how to decide which types of errors matches our needs?

```
types of errors		eazy 	hard 	fatal
1. bad index 			x
2. unallocated space 	x
3. nothing to shift 		x
4. no more memory	x	
5. wrong parameters		x	x
6. bad node		x	x
7. incompatible data    x
```

## What should we test?

1. it's indispensable to take into account the templatized system. our general design accepts any **well defined type**. thus testing arrangements of primitives has to be accompanied by verifying the same properties with special and complex types. for simplicity sake, in this project, only one complex type is used in this reasoning.

- each objective of an evaluation will be exemplified two times:
	- primitives 
	- convoluted types
- it's a must fot our structures to work well for ANY type. the default problems of each storage are:
	- initialisation
	- insert
	- remove
	- search
	- printing
	- sorting

- the only tasks dependent of the type of object are reordering(sorting) and printing. 
~ sorting problem: it's essential for the compiler and user to understand a complex type object in terms of another one. for exemple which one is greater. solution: to help the compiler "understand" i shaped data structures (that support the sort operation) to incorporate a custom function. if it is not set by the user, then by default takes the functionality of a comparison operator. this encourages the user to train the program with the correct execution process and to implement for its type the comparison operators.
~ printing problem: i made the arbitrary decision to use the "<<" operator for printing. the solution for a compound type is to implement the same operator

- it's necessary to add components that increase the difficulty of these problems, and not arbitrary ones (e. g. adding an iterator, wouldn't change how an object would behave in our situations, so coding it is a waste of time).

- a `well defined type` has:
	- diverse data members
		- only primitives, no STL containers - for easier visualisation
		- just one of each: normal type, a pointer and a reference - diverse but not agglomerate
	- relational operators (<, <=, >, >=, !=, ==) - to solve the sorting problem
	- operator << - to solve the printing problem

2. there will be a test-based header file for each data structure. we will test the following list of objectives:
* as i mentioned already: each objective for (primitives, convoluted)
	- there is a test for all constructors
	- there is a test for each specific method
	- there is a test for all constant methods
	- there is a test for all friend functions
	- there is a test for correct error prompts (assuming the only types of errors that can exist are those created by us)

## Data structures themselves:

1. implementation
- each data structure will contain the following categories:
```
private:
	- typedefs
	
protected:
	- data members
	- iterator class
	* extra utility methods
	
public:
	* extra utility data members
	- constructors 
	- iterator methods (e. g. begin, end)
	- specific methods (e. g. insert, remove)
	- constant methods (e. g. get, print)
```
2. fast access to a variable: `const type& variable`; do not do the same with the return type of a pointer function	

## Analysis of quick-sort

1. its execution depends on:
- how to choose pivot:
	- first
	- last
	- random (best)
	- median of a three (best)
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
```

2. quick sort is preferable when a random pivot is chosen, close to the mean of the partition
	- time  θ(n*lg(n))
	- space θ(lg(n))
	- smaller constant that merge sort


## Log - all my thoughts during the process:

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

2. new discover: the bug i was tallking about ealier was about VS's intellisense, c++ does great at templates

3. why maxheap does not inherit array? no matching methods

4. about node_tree class - i had multiple approaches
- preprocessing
- the number of child nodes in template
	- this strategy was automatically implying that children had to have the same number of children as their parent (no more/less)
	- one solution was to define children as "node<T>*" and not "node_tree<T, nr_children>": by some verifications i realised this method was not reliable 
- the number of child nodes non-existent, just in the constructor
- the number of child nodes as a data member (x)
- there is a lot more to talk about here !!!!!!!!!!!!!!!!

5. iterator class defined inside of the class that uses it
- no definitions of methods are allowed in header files for final types 

6. the default constructor initialise the memory
7. binary tree only if no arity is written in the constructor

8. how can i make the structures interact between them? if we are able to transform types into the data composition itself and back we solved the problem. the next question will be what would be the shape of the returned primitive? it must be primitive enough such that it can be converted back to a structure, but not the most primitive, such that we can lose functionality. think of a stack of queues of ints. to retreive the data from the stack it is enough to return the top queue, and not an block of memory with ints. transforming this into code logic: for each structure there will be a transform method whick will return a block of memory, a copy of the data cotained by the data storage.

9. trivial_tree is the most general tree that can be build; it can be considered a playground for a developer. the arity is variable, it might be complete or not

0. SOLID principles summary:
- S - single-responsability - each class has only one job
- O - open-close - open to add more, don't change existent
- L - Liskov     - behavioral subtype
- I - interface-segregation - a derived class implements and uses all its base's methods 
- D - dependency-inversion  - high-level modules should not depend on low level modules

1. operator == and = should be implemented in the final class / instantiable classes

2. prnt VS <<

3. adaptor VS tree

4. operations of dynamic sets
- queries
	- search 
	- minimum
	- maximum
	- predecessor - as value
	- successor - as value
- modifiers
	- insert
	- delete 