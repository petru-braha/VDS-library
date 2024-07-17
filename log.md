# Log - all my thoughts during the process

## I. Basics:

0. [source of my idea](https://www.cs.usfca.edu/~galles/visualization/)
- my plan is different - i want to visualise a data structure after calling one of its methods. basically just print the output in an intuitive way, but not the process itself.

1. SOLID principles summary:
- S - single-responsibility - each class has only one job
- O - open-close - open to add more, don't change existent
- L - Liskov     - behavioral subtype
- I - interface-segregation - a derived class implements and uses all its base's methods 
- D - dependency-inversion  - high-level modules should not depend on low level modules

2. operations of dynamic sets:
- queries
	- search 
	- minimum
	- maximum
	- predecessor - as value
	- successor - as value
- modifiers
	- insert
	- delete 

3. how can i make the structures interact between them? if we are able to transform types into the data composition itself and back we solved the problem. the next question will be what would be the shape of the returned primitive? it must be primitive enough such that it can be converted back to a structure, but not the most primitive, such that we can lose functionality. think of a stack of queues of ints. to retrieve the data from the stack it is enough to return the top queue, and not an block of memory with ints. transforming this into code logic: for each structure there will be a transform method which will return a block of memory, a copy of the data contained by the data storage.

## II. The initial ideas:

0. the initial implementation of the heap data structure:
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

1. the initial implementation of the tree data structure:

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

## III. minute-questions:

0. open-close principle was the hardest to achieve

1. decision over the source code:
- based on [this](https://www.learncpp.com/cpp-tutorial/class-templates-with-member-functions/) i moved the implementation of classes from C++ files to their header 
- iterator class defined inside of the class that uses it

1. discussion about what an abstract class should contain operator == and = should be implemented in the final class / instantiable classes

2. `prnt` VS `operator <<`:
- "prnt" - displays on standard output
- "operator <<" - displays where the user tells it so

3. friend functions
- general classes contains them. in practice for if it does depend to specification, they are implementend for abstract
- i will exlude (merge, intersection, ejection)

4. maxheap does not inherit array - no matching methods

5. template documentation
- class template == template<class t> class number
- template class == number<int>

6. default constructor problem

8. protected - private members
9. including files problem

0. for each - the order of execution of the operators: "!=", "*", "++".
1. add clear method lists

## IV. TO DO:
1. add comparing method to all the data structures
2. add predecessor, successor, minimum, maximum methods to all the data structures + other supported queries
3. build avl, minheap, rbt, trivial_tree
- decide how we'll we use GFLW == int main() 

## V. Cronological order:
0. convoluted
1. array_sorting
2. array
3. linked_list
4. adaptor
5. stack
6. queue
7. nodes
8. tree
9. avl
0. rbt
1. maxheap
2. minheap