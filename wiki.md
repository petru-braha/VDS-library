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