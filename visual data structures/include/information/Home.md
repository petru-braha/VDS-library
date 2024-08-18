### Administrative:

- "*" == optional attribute 
- "-" == imperative attribute
- this work is intended to be used by a "client", called from now on "user". the content here is assumed to stay unchanged and to be viewed as an utility.
- "this_is_the_name_of_a_file" and `this_is_the_name_of_a_method`

## I. Configuration:

1. run the project: 
- when it will be completely done, there will exist a compiled executable in the main directory. the user has to describe which data structure is interested in and how to manipulate it.
- before any queries, the tests for the data structures will run and prove the correctness of the program.
- for the visualisation it is necessary to impose a restriction for the amount of elements to be displayed. 
- the user will choose at most ten values and until he decides to stop, he has the oportunity to use any methods available.

2. directories explained:
- "packages" directory - Google Testing files
- "visual data structure" directory
	- "include" directory 
		- GLFW headers
		- general header ("bureaucracy.h")
		- all the headers used in the implementation of the data structures (such as interfaces)
	- "lib" directory - GLFW library and its dll
	- "src" directory - just the data structures' headers
	- "test" directory - a testing file for each data structure, "pch.cpp", and main file ("test.cpp")
	- additional files - VS configuration files
- additional information
	- text files
	- diagram of classes

3. Data structure implementation header:
```
- pre-processing directives:
	- pragma
	- include
	* define

- class:
private:
	* typedefs
	
protected:
	- data members
	- iterator concept
	* auxiliar utility (e. g. left_rotation, extra data members, comparing method)
	
public:
	- constructors
		- default
		- memory
		- copy, move

	- modifier methods
		- operator =
		- clear
		- setf

	- specific methods
		* sort
		- insert
		- remove 

	- constant methods 
	- iterator methods 
	- query operations 
	- instance synergy
	- friend functions 
	
* comments:
- implementation of class methods
```

## II. Testing:

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
	* NULL-constructor - **will explain in a minute**

2. there will be a test-based header file for each data structure. we will test the following list of objectives:
* as i mentioned already: each objective for (primitives, convoluted)
- fixture: tests constructors and `operator=`
- a test for:
	- each modifier method
	- each specific method
	- all query operations
	- all friend functions
	- a test for correct error prompts (assuming the only types of errors that can exist are those created by us)
 - we will not consider tests for iterators, auxiliar utility, constant methods and errors:
 	- their correct output implies the correct execution of the program
  	- some are private members
	- constant methods are tested along with 

3. how to test:
- the test functions should be:
 	- very fast 
 	- independent
 	- repeatable
	- portable
 	- informative (a failure provides as much information about the problem as possible)
- the rules:
 	- no more than 10 linies per test
 	- test driven development 

 4. test hierarchy:
- to keep it smooth, only the default test program and namespace will be present
- a data structure -> test fixture

5. actual approach of tests:
- standard values for testing
 	- "trial_test_values.h" is composed of default lists and blocks of data
 	- those values will be used to initialize all data structures in testing
 	- having this standard improves in tracking each object to ease the debugging 
        - the goal is to test the data structure's behavior and not the values themselves -> there is no inconvenience having the same values for each test suite
        
        - for simplicity: the maximum size for all my blocks of memory and lists should be small enough 
                  - quick response time
                  - easy debug
        - types of values: negative, positive, neutral(e. g. NULL, 0), repeating, very large/small

- fixtures 
 	- one for primitives and one for convoluted type
 	- the `SetUp` method is responsable of testing
 	 	- all constructors
 	 	- operator =
 	- `TearDown` evaluates destructors
 	- used only for modifier and specific methods
- testing without fixtures 	
 	- constant methods will be tested at the same time with the specific ones
- for convoluted tests we will test just the default utilities. 

4. final config of a test suite:
- fixture for primitives
	- clear method
	- sort method
	- insert method
	- remove method
	- query operations
	- friend functions
- fixture for convoluted (only the necessary)
	- sort method
	- insert method
	- remove method

## III. Errors:

1. classes:
- easy (prints message) - used only in testing/by user
- hard (prints message and throw -1) - queries of the structure
- fatal(prints message and exit) - modifiers and constructors of the structure

2. which types of errors matches our needs?
- potential inaccuracy of programmer's logic will be treated by the first class of faults. it's not their responsibility to treat an issue of the project; they exists only for the usage of this code.
- even if queries are constant functions, they preserve a potential role for build compounded applications. in exceptional cases, they can't determine a solution and the program has to stop. allowing undefined behavior, more elaborated processes won't give the expected output. so, a "hard_error" takes care of this situation with well defined exceptions.
- the job of a "fatal_error" is to kill the process. it is not optimal for the program to exit (data leakage), but there are some stages of a data structure when it interacts with outdoor types(std::initializer_list and blocks of memory). it has no control over the behavior of those types and can not manipulate how they are allocated/aligned. so, blindly will execute the modifiers, but will ask for some 
information about itself (it has control over itself). in case of problems (unallocated memory, exceeded capacity), it exits. 
- small reminder for the user: before an modifying operation, please check if the parameter is valid. a fatal error is a handler whenever this advice is discounted; should never be called!

3. exemples:
- hard error: linked_list<> numbers; /*empty list*/ std::cout << numbers.successor(1); 
- fatal error: array<> numbers(1); numbers.insert(1); numbers.insert(1); // the second call generates a fatal handler

4. list of defined exceptions:
```
types of errors		easy 	hard 	fatal
1. unallocated space 		x	x
2. no more memory		x	x
3. empty			x	x
4. empty - shift 		x	x
5. wrong parameters		x	
6. bad index 			x	
7. bad node			x
8. incompatible data    	x	x
* the occurrence of any other exception, not defined here, is a mistake
```