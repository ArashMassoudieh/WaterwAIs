# Coding conventions
This document defines general coding convention to be applied for C++ code in Infopact projects.  
The goal of this guide is to manage this complexity by describing in detail the dos and don'ts of writing C++ code.  
These rules exist to keep the code base manageable while still allowing coders to use C++ language features productively.

## Naming
Proper naming convention can give us immediate clues about what sort of thing the named entity is: a type, a variable, a function, a macro, etc., without requiring us to search for the declaration of that entity.  
Naming rules are pretty arbitrary, but consistency is very important to keep code easier to understand.

## General Naming Rules
Names should be descriptive; abbreviations and acronyms are OK as long as they make sense and are clear and unambiguous in context.  
- We should make names as descriptive as possible, within reason.  
- We shouldn't worry about saving horizontal space as it is far more important to make code immediately understandable by a new reader.
- Do not abbreviate by eliding vowels within a word (e.g., creat, scrpt, mtch). and do not misspell words.

Examples:

Good names:
```
int price_count_reader;    // No abbreviation.
int num_errors;            // "num" is a widespread convention.
int num_dns_connections;   // Most people know what "DNS" stands for.
int lstm_size;             // "LSTM" is a common machine learning abbreviation.
int xfer;                  // Commonly understood to mean "transfer"
int i;                     // Almost always an iteration variable.
```

Bad names:
```
int cnt;            // Count? Can't? Something else? Confusing.
int frms;           // Forms? Frames? Just spell out the word!
int suppleir;       // Spelled incorrectly!
```

Template parameters should follow the naming style for their category:  
- type template parameters should follow the rules for type names
- non-type template parameters should follow the rules for variable names (See below).

## File Names

Filenames should be mixed case and can include underscores (_), though most of the time those will not be necessary.

Examples:
```
    MyUsefulClass.cpp
    MyUsefulClass_STB.cpp
    MyUsefulClass_Impl.cpp
    MyUsefulClass_Test.cpp
```

C++ files should end in .cpp and header files should end in .h. Files that rely on being textually included at specific points should end in .inc (see also the section on self-contained headers).

We shouldn't use filenames that already exist in OS system folders like `/usr/include`, such as db.h.

In general, we should make our filenames very specific.
For example, use HttpServerLogs.h rather than Logs.h. A very common case is to have a pair of files called, e.g., FooBar.h and FooBar.cpp, defining a class called FooBar.

## Type Names
Type names start with a capital letter and have a capital letter for each new word, with no underscores: MyExcitingClass, MyExcitingEnum.

The names of all types — classes, structs, type aliases, enums, and type template parameters — use the same naming convention.  
Type names should start with a capital letter and have a capital letter for each new word and use no underscores.

Examples:
```
// classes and structs
class UrlTable { ...
class UrlTableTester { ...
struct UrlTableProperties { ...
 
// typedefs
typedef hash_map<UrlTableProperties *, std::string> PropertiesMap;
 
// using aliases
using PropertiesMap = hash_map<UrlTableProperties *, std::string>;
 
// enums
enum UrlTableErrors { ...
```

## Variable Names
The names of variables (including function parameters) and data members are all lowercase, with underscores between words.  
Private data members additionally have trailing underscores.  
For instance: a_local_variable, a_data_member, a_data_member_with_underscore_.

### Common Variable Names
Use lowercase, optionally with underscores. 

Examples:
```
std::string table_name;  // OK - uses underscore.
std::string tablename;   // OK - all lowercase.
std::string tableName;   // Bad - mixed case.
```

## Struct/Class Data Members
We should prefer designing small classes dedicated for a certain purpose with few data members and small, dedicated functions.
When we do this consistently, it becomes very easy to know what is a data member and what is not.

To distinguish private and protected data members from other/local variables, let's use a trailing underscore.  
But do not use underscores for public data members (for example, those within data-only aggregated members). 
Let's be consistent within a class definition!

Examples:
```
struct TableData {
    std::string table_name;  // OK. Public data member.
    std::string tablename;   // OK. Public data member.
};
```

```
class TableInfo {
    ...
private:
    std::string table_name_;  // OK - underscore at end. Private data member.
    std::string tablename_;   // OK. Private data member.
};
```

This rule guarantees a high level of consistency since only very rare circumstances will result in a class
or struct having both private and public data members.  
Simple aggregate types will not have underscores on their data members, while more complicated types that
use encapsulation will have underscores on their data members.

## Function Names
Regular functions have mixed case; setters and getters may be named like variables.

Functions should start with a lower case letter and have a capital letter for each new word:
```
addTableEntry()
deleteUrl()
openFileOrDie()
```

Another option is to use underscores to separate words:
```
add_table_entry()
delete_url()
open_file_or_die()
```
We just need to be consistent within a class definition!


Setters and getters (get and set functions) may be named like variables. They often correspond to actual member variables, but this is not required.  
For example, `int count()` and `void set_count(int count)`.


## Namespace Names
Namespaces should be named like types. However, it is OK to use detail as a sub-namespace name, as this is a common convention to indicate that outside code should not reach into them and that their internals should not appear in documentation.

## Enumerator Names
Enumerators (for both scoped and unscoped enums) should be named like types.

Preferably, the individual enumerators should be named like types. The enumeration name, (State), is a type, and therefore mixed case.
```
enum class State {
    Unknown,
    On,
    Off
};
```
We should use "enum class" unless there is an exceptionally good reason to use traditional unscoped enum. Do not needlessly set values explicitly. Do not prefix all the names. Do not "typedef enum":

```
typedef enum {         // Bad: uses enum instead of enum class
    STATE_UNKNOWN = 0, // Bad: needlessly, and redundantly, sets value of first element
    STATE_ON,          // Bad: prepends each name with STATE_
    STATE_OFF          // Bad: named like a macro
} State;               // Bad: "typedef enum"
```

## Macro Names

In general, with modern C++ we should define a macro only in very rare cases.
However, if they are absolutely needed, then they should be named with all capitals and underscores.

```
#define ROUND(x) ...
#define PI_ROUNDED 3.0
```
If a macro is only good within a certain scope, #undef it at the end of that scope.

## Exceptions to Naming Rules

If we are naming something that is analogous to an existing C or C++ entity then you can follow the existing naming convention scheme.

- bigopen() - function name, follows form of open()
- sparse_hash_map - STL-like entity; follows STL naming conventions
- LONGLONG_MAX - a constant, as in INT_MAX

## Comments
Comments are absolutely vital to keeping code readable. The following rules describe what you should comment and where.  
But we should keep in mind that while comments are very important, the best code is self-documenting.  
Giving proper and self-explanatory names to types and variables is much better than using obscure names that you must explain through comments.

When writing comments, don't hesitate to write more rather than less. The next contributor who will thank you for writing comments may be you some time later!


### File Comments
If a .h declares multiple abstractions, the file-level comment should broadly describe the contents of the file, and how the abstractions are related. A one or two sentence file-level comment may be sufficient.  
The detailed documentation about individual abstract interfaces belongs to those interfaces, not at the file level.

### Class Declarations
Every non-obvious class declaration should have an accompanying comment that describes what it is for and how it should be used.

The class comment should provide enough information to know how and when to use the class, as well as any additional considerations necessary to correctly use the class.  
Document the thread synchronization assumptions the class makes, if any. If an instance of the class can be accessed by multiple threads, please document the rules for multithreaded use.

The class comment is often a good place for a small example code snippet demonstrating a simple and focused usage of the class.

### Function Declarations
If it is not obvious what the function does then it should have a comment describing what it does and how to use it.

Typical comments:
- What the inputs and outputs are.
- If the function is re-entrant. What are its synchronization assumptions?

Additional types of things to mention at the function declaration:
- Whether any of the arguments can be a null pointer.
- For class member functions: whether the object remembers reference arguments beyond the duration of the method call, and whether it will free them or not.
- If the function allocates memory that the caller must free.
- If there are any performance implications of how a function is used.


However, we shouldn't be unnecessarily verbose or state the completely obvious.

### Global Variables
All global variables should have a comment describing what they are, what they are used for, and (if unclear) why they need to be global.

### In-Code Comments
Tricky or complicated code blocks should have comments before them. 

Examples:
```
// Divide result by two, taking into account that x
// contains the carry from the add.
for (int i = 0; i < result->size(); i++) {
    x = (x << 8) + (*result)[i];
    (*result)[i] = x >> 1;
    x &= 1;
}
```

Also, non-obvious lines should get a comment at the end of the line.

```
// If we have enough memory, mmap the data portion too.
mmap_budget = max<int64>(0, mmap_budget - index_->length());
if (mmap_budget >= data_size_ && !MmapData(mmap_chunk_bytes, mlock))
    return; // Error already logged.
```

## Formatting
Coding style and formatting are pretty arbitrary, but a project is much easier to follow if everyone uses the same style. 
Some of the rules may take some time to get used to, but it is important that all project contributors follow the style rules so that they can all read and understand everyone's code easily.

## Line Length
It is suggested, but not required, to wrap code at 80 characters (widely accepted guideline in open source community).  
Code that has too many long lines can be difficult to read, especially when comparing code side-by-side or reading on smaller screens.  

It is perfectly fine for the occasional line to go beyond 80 characters, as long as it helps readability. However, if too many lines extend beyond this limit, it may indicate a problem with code structure:  
either too much nesting or attempting to accomplish too much per-line. Consider breaking your code up into more concise expressions, statements, and/or functional blocks.

## Spaces vs. Tabs
We use only spaces, and indent 4 spaces at a time.
Tabs are allowed only where they are mandatory (e.g., in Makefiles), but not in C++ code. 
We should set text editors to insert spaces when the tab key is pressed.

## Function Declarations and Definitions
Return type on the same line as function name, parameters on the same line if they fit.  
Wrap parameter lists which do not fit on a single line as you would wrap arguments in a function call.

Functions look like this:
```
ReturnType ClassName::functionName(Type par_name1, Type par_name2) {
    doSomething();
    ...
}
```

If you have too much text to fit on one line:
```
ReturnType ClassName::reallyLongFunctionName(Type par_name1, Type par_name2,
                                             Type par_name3) {
    doSomething();
    ...
}
```
or if you cannot fit even the first parameter:
```
ReturnType LongClassName::reallyReallyReallyLongFunctionName(
        Type par_name1,  // 8 space indent
        Type par_name2,
        Type par_name3) {
    doSomething();  // 4 space indent
    ...
}
```

Some important notes:
 - Choose good parameter names.
 - A parameter name may be omitted only if the parameter is not used in the function's definition.
 - If you cannot fit the return type and the function name on a single line, break between them.
 - If you break after the return type of a function declaration or definition, do not indent.
 - The open parenthesis is always on the same line as the function name.
 - There is never a space between the function name and the open parenthesis.
 - There is never a space between the parentheses and the parameters.
 - The open curly brace is always on the end of the last line of the function declaration, not the start of the next line.
 - The close curly brace is either on the last line by itself or on the same line as the open curly brace.
 - There should be a space between the close parenthesis and the open curly brace.
 - All parameters should be aligned if possible.
 - Default indentation is 4 spaces.
 - Wrapped parameters have a double (8 space) indent.
 
 Unused parameters that are obvious from context may be omitted:
 ```
 class Foo {
public:
    Foo(Foo&&);
    Foo(const Foo&);
    Foo& operator=(Foo&&);
    Foo& operator=(const Foo&);
    void setTimeout(std::chrono::milliseconds);
};
 ```
We shouldn't use void as a parameter:  
```
int foo(void); // Bad. Do  not use (void) here
```
Unused parameters that might not be obvious should comment out the variable name in the function definition:
```
class Shape {
public:
    virtual void rotate(double radians) = 0;
};
 
class Circle : public Shape {
public:
    void rotate(double radians) override;
};
 
void Circle::rotate(double /*radians*/) {}
```
```
// Bad - if someone wants to implement later, it's not clear what the
// variable means.
void Circle::rotate(double) {}
```

## Lambda Expressions
We should format parameters and lambda bodies as for any other function, and capture lists like other comma-separated lists.

For by-reference captures, we should not leave a space between the ampersand (&) and the variable name.
```
int x = 0;
auto x_plus_n = [&x](int n) -> int { return x + n; }
```
Short lambdas may be written inline as function arguments.
```
std::set<int> blacklist = {7, 8, 9};
std::vector<int> digits = {3, 9, 1, 8, 4, 7, 1};
digits.erase(std::remove_if(digits.begin(), digits.end(), [&blacklist](int i) {
                 return blacklist.find(i) != blacklist.end();
             }),
             digits.end());
```
Skip parenthesis if the lambda takes no parameters.
```
auto func = [](){ return value; }; // Bad. Leave parens out.
```
Skip the trailing return type except when readability is significantly enhanced in rare cases, or if the compiler requires it.
```
auto func = [] -> int { return value; } // Bad. Trailing return type unnecessary.
```

## Function Calls
We should either write the call all on a single line, wrap the arguments at the parenthesis, or start the arguments on a new line double-indented by 8 spaces and continue at that 8 space indent.  
In the absence of other considerations, we should use the minimum number of lines, including placing multiple arguments on each line where appropriate.

Function calls have the following format:
```
bool result = doSomething(argument1, argument2, argument3);
```
If the arguments do not all fit on one line, they should be broken up onto multiple lines, with each subsequent line aligned with the first argument.
We should not add spaces after the open bracket or before the close bracket:
```
bool result = doSomething(averyveryveryverylongargument1,
                          argument2, argument3);
```
Arguments may optionally all be placed on subsequent lines with a 8 space indent:
```
if (...) {
    bool result = doSomething(
            argument1, argument2,  // 8 space indent
            argument3, argument4);
    ...
}
```
We should put multiple arguments on a single line to reduce the number of lines necessary for calling a function unless there is a specific readability problem.  

If having multiple arguments in a single line decreases readability due to the complexity or confusing nature of the expressions that make up some arguments, we should try creating variables that capture those arguments in a descriptive name:
```
int my_heuristic = scores[x] * y + bases[x];
bool result = doSomething(my_heuristic, x, y, z);
```
Or put the confusing argument on its own line with an explanatory comment:
```
bool result = doSomething(scores[x] * y + bases[x],  // Score heuristic.
                          x, y, z);
```
If there is still a case where one argument is significantly more readable on its own line, then put it on its own line. The decision should be specific to the argument which is made more readable.

Sometimes arguments form a structure that is important for readability. In those cases, we may format the arguments according to that structure:
```
// Transform the widget by a 3x3 matrix.
my_widget.transform(x1, x2, x3,
                    y1, y2, y3,
                    z1, z2, z3);
```

## Conditionals
We should not put spaces inside parentheses. The if and else keywords belong on separate lines.
```
if (condition) {  // no spaces inside parentheses
    ...  // 4 space indent.
} else if (...) {  // The else goes on the same line as the closing brace.
    ...
} else {
    ...
}
```
Note that in all cases we should have a space between the if and the open parenthesis.  
We should also have a space between the close parenthesis and the curly brace, if we are using one.
```
if(condition) {   // Bad - space missing after IF.
if (condition){   // Bad - space missing before {.
if(condition){    // Doubly bad.
if (condition) {  // Good - proper space after IF and before {.
```
Short conditional statements may be written on one line if this enhances readability. We may use this only when the line is brief and the statement does not use the else clause.
```
if (x == 1) return std::make_unique<Foo>();
if (x == 2) return std::make_unique<Bar>();
```
This is not allowed when the if statement has an else:
```
// Not allowed - IF statement on one line when there is an ELSE clause
if (x) doThis();
else doThat();
```
In general, curly braces are not required for single-line statements, but they are allowed if someone likes them; conditional or loop statements with complex conditions or statements may be more readable with curly braces.
Some projects require that an if must always have an accompanying brace.
```
if (condition)
    doSomething();  // 4 space indent.
 
if (condition) {
    doSomething();  // 4 space indent.
}
```
However, if one part of an if-else statement uses curly braces, the other part must too:
```
// Not allowed - curly on IF but not ELSE
if (condition) {
    foo;
} else
    bar;
 
// Not allowed - curly on ELSE but not IF
if (condition)
    foo;
else {
    bar;
}
```
```
// Curly braces around both IF and ELSE required because
// one of the clauses used braces.
if (condition) {
    foo;
} else {
    bar;
}
```

## Loops and Switch Statements
Switch statements may use braces for blocks. We should annotate non-trivial fall-through between cases. Braces are optional for single-statement loops. Empty loop bodies should use either empty braces or continue.  
`case` blocks in `switch` statements can have curly braces or not, depending on your preference. If we do include curly braces they should be placed as shown below.

If not conditional on an enumerated value, switch statements should always have a default case (in the case of an enumerated value, the compiler will warn us if any values are not handled). If the default case should never execute, we shoud treat this as an error.  
Example:
```
switch (var) {
case 0: {
    ...    // 4 space indent
    break;
}
case 1: {
    ...
    break;
}
default: {
    assert(false);
}
}
```
Fall-through from one case label to another must be annotated using the `[[fallthrough]]` attribute. This should be placed at a point of execution where a fall-through to the next case label occurs.  
A common exception is consecutive case labels without intervening code, in which case annotation is not needed.
```
switch (x) {
case 41:  // No annotation needed here.
case 43:
    if (dont_be_picky) {
        [[fallthrough]];
    } else {
        closeButNoCigar();
        break;
    }
case 42:
    doSomethingSpecial();
    [[fallthrough]];
default:
    doSomethingGeneric();
    break;
}
```
Braces are optional for single-statement loops.
```
for (int i = 0; i < max_loops; ++i)
    printf("I love you\n");
 
for (int i = 0; i < max_loops; ++i) {
    printf("I take it back\n");
}
```
Empty loop bodies should use either an empty pair of braces or continue with no braces, rather than a single semicolon.
```
while (condition) {
  // Repeat test until it returns false.
}
for (int i = 0; i < max_loops; ++i) {}  // Good - one newline is also OK.
while (condition) continue;  // Good - continue indicates no logic.
```
```
while (condition);  // Bad - looks like part of do/while loop.
```

## Pointer and Reference Expressions
We shouldn't use spaces around period or arrow. Pointer operators do not have trailing spaces.

The following are examples of correctly-formatted pointer and reference expressions:
```
x = *p;
p = &x;
x = r.y;
x = r->y;
```
Note that:

    There are no spaces around the period or arrow when accessing a member.
    Pointer operators have no space after the * or &.

When declaring a pointer variable or argument, we may place the asterisk adjacent to either the type or to the variable name:
```
// These are fine, space preceding.
char *c;
const std::string &str;
 
// These are fine, space following.
char* c;
const std::string& str;
```
We should do this consistently within a single file, so, when modifying an existing file, let's use the style in that file.

We may declare multiple variables in the same declaration, but it should be avoided if any of those have pointer or reference decorations because such declarations are easily misread.
```
// Fine if helpful for readability.
int x, y;
int x, *y;  // Disallowed - no & or * in multiple declaration
char * c;  // Bad - spaces on both sides of *
```
```
const std::string & str;  // Bad - spaces on both sides of &
```
## Boolean Expressions
When we have a boolean expression that is longer than the standard line length, we should be consistent in how we break up the lines.

In this example, the logical AND operator is always at the end of the lines:
```
if (this_one_thing > this_other_thing &&
        a_third_thing == a_fourth_thing &&
        yet_another && last_one) {
    ...
}
```
Note that when the code wraps in this example, both of the && logical AND operators are at the end of the line although wrapping all operators at the beginning of the line may also be used.  
We may insert extra parentheses if they help to increase readability when used appropriately. 

## Return Values
We should not surround the `return` expression with parentheses if there is no special need.

Use parentheses in `return expr;` only where you would use them `in x = expr;`.
```
return result;                  // No parentheses in the simple case.
// Parentheses OK to make a complex expression more readable.
return (some_long_condition &&
        another_condition);
```
```
return (value);                // Bad. We wouldn't write var = (value);
return(result);                // Bad. return is not a function!
```

## Variable and Array Initialization

Our choice of `=`, `()`, or `{}`.

We may choose between `=`, `()`, and `{}`; the following are all correct:
```
int x = 3;
int x(3);
int x{3};
std::string name = "Some Name";
std::string name("Some Name");
std::string name{"Some Name"};
```
We should be careful when using a braced initialization list `{...}` on a type with an `std::initializer_list` constructor. 
A nonempty braced-init-list prefers the std::initializer_list constructor whenever possible.  
Note that empty braces `{}` are special, and will call a default constructor if available. To force the non-`std::initializer_list` constructor, we should use parentheses instead of braces.
```
std::vector<int> v(100, 1);  // A vector containing 100 items: All 1s.
std::vector<int> v{100, 1};  // A vector containing 2 items: 100 and 1.
```

Also, the brace form prevents narrowing of integral types. This can prevent some types of programming errors.
```
int pi(3.14);  // OK -- pi == 3.
int pi{3.14};  // Compile error: narrowing conversion.
```

## Class/Struct Format
Sections in `public`, `protected` and `private` order.

The basic format for a class definition (without comments) is:
```
class MyClass : public OtherClass {
public:
    MyClass();
    explicit MyClass(int var);
    ~MyClass() {}
 
    void some_function();
    void some_function_that_does_nothing() {
    }
 
    void set_some_var(int var) { some_var_ = var; }
    int some_var() const { return some_var_; }
 
private:
    bool someInternalFunction();
 
    int some_var_;
    int some_other_var_;
};
```

When defining an abstract interface, we should put the virtual destructor first:
```
struct MyInterface {
    virtual ~MyInterface() = default;
 
    virtual void foo() const = 0;
    virtual int bar() = 0;
};
```
We should not declare "`typedef struct`". This is NOT necessary in C++:
```
typedef struct { // Bad: do not declare 'typedef struct'
    int a;
    double b;
} Foo;
```

When using structs (and classes), skip the class-key, except in cases involving forward declarations:
```
void func(struct Bar*); // Bad: leave 'struct' out
```

Things to note:
- Any base class name should be on the same line as the subclass name.
- The `public:`, `protected:`, and `private:` keywords should not be indented.
- Except for the first instance, these keywords should be preceded by a blank line. This rule is optional in small classes.
- We should not leave a blank line after these keywords.
- The public section should be first, followed by the protected and finally the private section.

## Constructor Initializer Lists
Constructor initializer lists can be all on one line or with subsequent lines double-indented 8 spaces.

The acceptable formats for initializer lists are:
```
// When everything fits on one line:
MyClass::MyClass(int var) : some_var_{var} {
    do_something();
}

// If the signature and initializer list are not all on one line,
// you must wrap before the colon and indent 8 spaces:
MyClass::MyClass(int var)
        : some_var_{var}, some_other_var_{var + 1} {
    do_something();
}
 
// When the list spans multiple lines, put each member on its own line
// and align them:
MyClass::MyClass(int var)
        : some_var_{var},             // 8 space indent
          some_other_var_{var + 1} {  // lined up
    do_something();
}
 
// Same as above, but puts the comma at the beginning of each line.
// Both ways are acceptable, but ***be consistent***.
MyClass::MyClass(int var)
        : some_var_{var}              // 8 space indent
        , some_other_var_{var + 1} {  // lined up
    do_something();
}
 
// As with any other code block, the close curly can be on the same
// line as the open curly, if it fits.
MyClass::MyClass(int var)
        : some_var_{var} {}
```

## Namespace Formatting
We should not indent the contents of namespaces.

Namespaces do not add an extra level of indentation. 
Example:
```
namespace Project {
 
void foo() { // Correct.  No extra indentation within namespace.
    ...
}
 
} // namespace Project
```
We shoud not indent within a namespace.
```
namespace Project {
    namespace Library {
        namespace Feature {
 
            // Wrong! Runaway indentation!
            void foo() {
                ...
            }
 
        } // namespace Feature
    } // namespace Library
} // namespace Project
```

**Exception:** If a namespace scope is very small, such that it fits in a small fraction of a page on-screen and helps it stand out, it may be indented for readability.
```
namespace { // anonymous
    constexpr auto max_wait_duration = 60s;
    constexpr auto poll_frequency = 5_Hz;
} // anonymous namespace
```

When declaring nested namespaces, we should put each namespace on its own line. Likewise, we should close each namespace on its own line.
```
namespace foo {
namespace bar {
    ...
} // namespace bar
} // namespace foo
```

## Horizontal Whitespace
Use of horizontal whitespace depends on location. We should never put trailing whitespace at the end of a line.

### General
```
void f(bool b) { // Open braces should always have a space before them.
    ...
int i = 0; // Semicolons usually have no space before them.
// Spaces inside braces for braced-init-list are optional.  If you use them,
// put them on both sides!
int x[] = { 0 };
int x[] = {0};
 
// Spaces around the colon in inheritance and initializer lists.
class Foo : public Bar {
public:
    // For inline function implementations, put spaces between the braces
    // and the implementation itself.
    Foo(int b) : Bar(), baz_(b) {} // No spaces inside empty braces.
    void reset() { baz_ = 0; } // Spaces separating braces from implementation.
    ...
```

Adding trailing whitespace can cause extra work for others editing the same file, when they merge, as can removing existing trailing whitespace.  
So, we should not introduce trailing whitespace. We should also remove it if we're already changing that line, or do it in a separate clean-up operation (preferably when no-one else is working on the file).

### Loops and Conditionals
```
if (b) {          // Space after the keyword in conditions and loops.
} else {          // Spaces around else.
}
while (test) {}   // No space inside parentheses.
switch (i) {      // Space after the keyword in switch statements.
for (int i = 0; i < 5; ++i) {
// Range-based for loops always have a space before and after the colon.
for (auto x : counts) {
    ...
}
switch (i) {      // Space after the keyword in switch statements.
case 1:           // No space before colon in a switch case.
    ...
case 2: break;    // Use a space after a colon if there's code after it.
```

### Operators
```
// Assignment operators always have spaces around them.
x = 0;
 
// Other binary operators usually have spaces around them, but it's
// OK to remove spaces around factors.  Parentheses should have no
// internal padding.
v = w * x + y / z;
v = w*x + y/z;
v = w * (x + z);
 
// No spaces separating unary operators and their arguments.
x = -5;
++x;
if (x && !y)
    ...
```

### Templates and Casts
```
// No spaces inside the angle brackets (< and >), before
// <, or between >( in a cast
std::vector<std::string> x;
y = static_cast<char*>(x);
 
// DO NOT put spaces between closing angle brackets:
std::unique_ptr<std::vector<std::string>> good;
std::unique_ptr<std::vector<std::string> > bad; // obsolete as of C++11
```

### Vertical Whitespace
We should minimize use of vertical whitespace unless it improves readability.

Basic guidelines:
- We should not put more than one or two blank lines between functions.
- Blank lines at the beginning or end of a function very rarely help readability.
- Blank lines inside a chain of if-else blocks may well help readability.

***
This code convention is a simplified version of the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html),
used under [CC BY](https://creativecommons.org/licenses/by/3.0/)