Exact circular pattern matching
===============================

Two data structures for finding all occurrences of *any rotation* of a pattern in a text.  Both may be used as a text index, that is, to preprocess a text for fast circular pattern matching.

CPI-II
------
This data structure is described in Illiopoulos and Rahman - "Indexing circular patterns" (2008).

To build an index for a text, call the Cpi2 constructor `Cpi2(std::string &text)`:

```
cpm::Cpi2 cpi(text);
```

Then, use the method `std::set<int> cmatch(std::string &pattern)` to match a circular pattern:

```
std::set<int> matches;
matches = cpi.cmatch(pattern);
```

Of course, `cmatch()` may be called any number of times.


Mult-V
------
This is a suffix-tree-based circular pattern index.  Its space and time performance are inferior to CPI-II's (CPI-II uses a suffix array rather than suffix tree).

Single exact circular pattern matching:
```
std::set<int> cpm(std::string text, std::string pattern)
```

Multiple exact circular pattern matching:
```
std::vector< std::set<int> > cpm(std::string text_filepath, std::vector<std::string> pattern_filepaths)
```

The definition of the latter function shows how to use this data structure as an index when not all patterns are available at the same time.
