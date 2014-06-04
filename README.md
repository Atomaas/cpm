Exact circular pattern matching
===============================

Two data structures for finding all occurrences of any rotation of a pattern.  Both may be used to index a text for multiple-pattern matching.

CPI-II
------
This is a suffix-array-based data structure described in Illiopoulos and Rahman - "Indexing circular patterns" (2008).

Build an index:

```
cpm::Cpi2 cpi2_index(text);
```

Match a circular pattern:

```
std::set<int> matches;
matches = cpi2_index.cmatch(pattern);
```

Of course, `cmatch()` may be called any number of times.


Mult-V
------
This is a suffix-tree-based circular pattern index.  Its space and time performance are inferior to CPI-II's.

Build an index:

```
cpm::Cpi2 cpi2_index(text);
```

Match a circular pattern:

```
std::set<int> matches;
matches = cpi2_index.cmatch(pattern);
```
