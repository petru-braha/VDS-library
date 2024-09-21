## I. To do:
0. rbt
1. maxheap
2. minheap
3. graph
4. hash_table

- equality method
- more error checking for structures, optimisation methods, proof - robustness of testing

//------------------------------------------------

## II. The initial ideas:

0. [source of my idea](https://www.cs.usfca.edu/~galles/visualization/)
- my plan is different - i want to visualise a data structure after calling one of its methods. basically, it prints the output in an intuitive way, but not the process itself.

1. the initial implementation of the heap data structure:
- as_array: bool = false;
- as_btree: bool = true;
- there were 2 abstract classes: heap<T, as_array> and heap<T, as_btree>
- maxheap and minheap were supposed to inherit a template specialized class

- maxheap
	- as_array
	- as_btree
- minheap
	- as_array
	- as_btree

- there are 4 types of heaps and six classes
- the plan was changed because of the bugs of VS's Intellisense - inheriting template specialized classes
- there will be only two classes: maxheap<T> (represented as an array) and minheap<T> (represented as a binary tree)

2. the initial implementation of the tree data structure:

- i was avoiding creating extra data members for small classes like node.

- preprocessing - wrong
- the number of child nodes in template
	- this strategy was automatically implying that children had to have the same number of children as their parent (no more/less)
	- one solution was to define children as "node<T>*" and not "node_tree<T, nr_children>": by some verifications i realised this method was not reliable 
- the number of child nodes non-existent, just in the constructor
- the number of child nodes as a data member (x)
- there is a lot more to talk about here !!!!!!!!!!!!!!!!

- problem - node_avlt was inheriting node_bint pointers!
- solution - each class has its children
- each type of tree has its own type of node
- static polymorphism 

- trivial_tree is the most general tree that can be build; it can be considered a playground for a developer. the arity is variable, it might be complete or not
	- binary tree only if no arity is written in the constructor

//------------------------------------------------

## III. Minute questions:

0. open-close principle is the hardest to achieve

1. decision over the source code:
- based on [this](https://www.learncpp.com/cpp-tutorial/class-templates-with-member-functions/) i moved the implementation of classes from C++ files to their header 

2. discussion about what an abstract class should contain operator == and = should be implemented in the final class / instantiable classes

3. `prnt` VS `operator <<`:
- "prnt" - displays on standard output
- "operator <<" - displays where the user tells it so

4. friend functions
- instantiable classes contains them
- i will exclude (linking, intersection, ejection)

5. maxheap does not inherit array - no matching methods

6. template documentation
- class template == template<class t> class number
- template class == number<int>

7. default constructor problem
8. protected - private members
9. including files problem
0. iterator documentation
1. forget about the initialisation test. using the fixture it is not relevant

2. for each - the order of execution of the operators: "!=", "*", "++".

0. initial idea of testing: let the user test himself some values for an data structure

3. standard for comparing functions: return true if the order of two elements have to be changed


4. should the advanced data structures depend on developer-designed basic structures? - no
	- slow 
	- to much functionality
	- solution: define smaller 

5. data_structure<T> or data_structure<t> as a parameter, where t == typedef const T& t; ? 
	- data_structure<t> won't work, no casts will be done
	- solution: use data_structure<T>

6. & const does not exist

7. to or not to copy a node?
	- insert: user inserts node with existent children => mess with n
	- instance synergy: 	
	- operator =

8. interfaces can not contain data members (nodes has their own implementation ideas)
9. data structures should be 
	- independent of the base type that it stores. there is just one part of the implementation that requires more analysis: ordering of the elements. the ordering problem is based on sorting and comparisons. the convoluted types should be tested when it comes to this problem, testing them with insertions is redundant;
	- aggregate

0. getl now throws if it is empty

- modifier and specific methods, instance synergy will return reference
- typedefs are used only for constant, iterator, query, synergy

- returning reference to allow obj.method.method
- i can not allow modifying structures outside of themselves => return constant indexes/nodes
	
- before iterator class defined inside of the class that uses it

1. separated the jobs of the library into different processes 
- showcase

2. include guards over '#pragma once'
- duplicated files
- standard

3. third process (process 2 draw) achived a better understanding of mine over an error system using exceptions