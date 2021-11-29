# Architecture and design decisions

The whole project consist of two main parts: `librexgen`, which does most of the work, and `rexgen`, which is a command line tool that provides most of the functionality two the user. In addition, `rexgen` is used to demonstrate how to use the `librexgen` API and to see if the API is sufficient and working.

![Context diagram](context.png)

# Regex and Iterators

Each regular expression is parsed into a Abstract Syntax Tree (AST) which uses the classes in the `regex` subfolder for data representation. All those classes are derived from `Regex`. Every `Regex` class provides a `iterator()` method which generates an `Iterator` (classes in the `iterator` subfolder). The `Iterator`s are responsible for generating values. There is one `Iterator`  class for every `Regex` class. For example, the `ClassRegex` generates a `ClassRegexIterator` instance.

## Iterators

### Iterator Semantics

An `Iterator` generates a unlimited list of values, which repeat after some time. The following pseudocode demonstrates the basic use of iterators:

```C++
SimpleString value;
Iterator my_iter = my_regex.iterator();

while (my_iter.next()) {
    my_iter.value(&value);
    printf("%s\n", value.c_str());
}
```

The next diagram shows the intended semantics of Iterator methods:

![Iterator semantics](iterator.drawio.svg)

# Working with Unicode

Internally, `librexgen` is working with multi byte characters for performance reasons. We use the exact same character encoding which is used for the output, so that no additional encoding must be done when generating the result strings.