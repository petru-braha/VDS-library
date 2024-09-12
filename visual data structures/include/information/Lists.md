0. list of defined exceptions:

| error type		| eazy		| hard		| fatal		|
|:---------------------:|:-------------:|:-------------:|:-------------:|
| unallocated space 	|		| x		| x		|
| no more memory	| x		| x 		|		|
| empty	- no data	| x		| x 		|		|
| wrong parameters	| 		| x 		|		|
| bad index		| 		| x 		|		|
| bad node		| 		| x 		|		|
| incompatible data	| x		| x 		|		|

* the occurrence of any other exception, not defined here, is a mistake

1. array errors:

| method      	| error type	| meassage		|
|:-------------:|:-------------:|:---------------------:|
| shift_left	| fatal_error	| "nothing to shift"	|
| constructor	| fatal_error	| "wrong parameters"	|
|		|		|			|
| insert	| hard_error	| "bad index"		|
| insert	| fatal_error	| "no more memory"	|
| remove	| hard_error	| "bad index"		|
| queries	| hard_error	| "no data"		|
| operator[]	| hard_error	| "unallocated space"	|
