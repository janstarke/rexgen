# Architecture and design decisions

The whole project consist of two main parts: `librexgen`, which does most of the work, and `rexgen`, which is a command line tool that provides most of the functionality two the user. In addition, `rexgen` is used to demonstrate how to use the `librexgen` API and to see if the API is sufficient and working.

![Context diagram](context.png)

# Working with Unicode

Internally, `librexgen` is working with multi byte characters for performance reasons. We use the exact same character encoding which is used for the output, so that no additional encoding must be done when generating the result strings.