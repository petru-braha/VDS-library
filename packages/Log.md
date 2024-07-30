0. initial idea of testing:
- to have an interface

- https://stackoverflow.com/questions/12076072/how-to-run-specific-test-cases-in-googletest?
- let the user test himself some values for an data structure
- runs only one test suite ::testing::GTEST_FLAG(filter) = "*Counter*:*IsPrime*:*ListenersTest.DoesNotLeak*";//":-:*Counter*";

1. standard for comparing functions: return true if the order of two elements have to be changed

2. lists support all query operation
2. divide linked list in an abstract class to support adaptors as well : list

3. insert and delete should not do the search!!! it is based on pointers!

//-----------------------------------------------------------------------------------------

## I. The initial ideas:

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

## II. Minute-questions:

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
7. protected - private members
8. including files problem
9. iterator documentation
0. forget about the initialisation test. using the fixture it is not relevant

0. for each - the order of execution of the operators: "!=", "*", "++".

## III. To do:
1. add "compare", clear, predecessor, successor, minimum, maximum methods to all the data structures + other supported queries, testing
2. decide how we'll we use GFLW == int main() 

## IV. To review:
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