# Alpaca Coding Style
A coding style is necessary for most any project, especially one with a group of people working on it. Please follow these style guidelines whenever writing code for libalpaca.

It is stated in the Linux Kernel Coding Style Guidelines,
```
First off, I’d suggest printing out a copy of the GNU coding standards, and NOT read it. Burn them, it’s a great symbolic gesture.
```
I recommend doing so, to both the GNU coding standards, and aforementioned Linux Kernel Style Guide, if you have not done so already.

## Naming Convention

### Which Case to Use and When
lowerCamelCase is for use on variables, functions, and parameters.
UpperCamelCase is to be utilized on classes, typedefs, structs, and other things used as a type.
UPPER\_CASE\_SNAKE\_CASE is for macros only.

### What's In a Name?
Whether it be a variable, class, function, or something else, it should have a name that makes sense. Names should be fairly short, as overlyLongCamelCaseNamesLookVeryBadAndArentVeryReadable.
Names should describe only the purpose or representation of something, not it's type, const status, date of birth, mother's maiden name, social security number, meme reference, or any other irrelevant or otherwise accessable value. All (or most) of those have their place, but not in the name of something (ie. a type shouldnt go in the name, thats why types have names).

### Example
```Cpp
#define MAIN_ZOO_NAME "Husnoklia"
struct Zoo {
  std::string name;
  Zoo(std::string name) : name(name) {
  };
};
Zoo mainZoo(MAIN_ZOO_NAME);
```

## Indentation
Tabs should be tabs, because any decent editor can configure a tab to any length.

### Switch/Case
You should indent on both a switch statement and a case statement.
```Cpp
switch (foo) {
  case 1:
    bar();
    break;
  case 2:
    baz();
    break;
 }
 ```

### Control statements
The execution after control statements should always be on another line.
```Cpp
if (zoo == 'at the')
  goToExhibit('elephants');
```

## Spaces, Parentheses and Curly Braces
There should be no spaces at all seperating a function name and it's parameters.
There should be a space seperating a control statement and the evaluation, as well as a space seperating it from the curly brace that follows *on the same line.*
```Cpp
int foo(int bar) {
  if (bar != 4) 
    return baz(bar) * 2;
  return 0;
}

printf('%d', foo(3));
```
Additionally, there should not be spaces in between parameters or an evaluation and the parentheses encapsulating them.
Spaces should also go on either side of a binary operator, and not in between a variable and a unary operator.
```Cpp
int four = 2 + 2;
four++;
int six = ++four;
```

## Breaking
Do not break before binary or ternary operators, unless it is a ternary operator that exceeds the line length. Then, you should break before the operator itself. Break after a curly brace, placed on the same line as what comes before it. Always break after a curly brace, regardless of the length of what follows.
```Cpp
bool z(void) {
  int a = 0;
  int *b = &a;
  if (a == *b) {
    q = 5;
    return true;
  }
  q = (y(a) == 0);
}
```

## Line Length
All lines are to be kept under 80 columbs. Use the `\` character to expand a macro as necessary.
```Cpp
#define p 394949.44989595959858598598598598959858958953444444444444444444444444\
    84848
```
Tab in when continuing a line longer than 80 columbs.

## A Note on Ternary Operators
When using ternary operators, unless the evaluation into a boolean is itself a boolean, put this evaluation in parentheses, so it's likeness to an evaluation in a control statement is more easily recognized.

## Access Modifiers
Access modifiers should be on the same line as a class definition, and members should tab in from there. This is due to the case where without access modifiers, you tab in anyways for your members.

## Pointers
Pointer alignment goes toward a variable, rather than the type.
```Cpp
int *a, b, c;
```
Above is code that creates an int pointer of `a`, and `b` and `c` are ints. The pointer must therefore logically go to the right, as to prevent confusion on matters such as these.

## Namespace Indentation and the Alpaca Namespace
Namespaces always need the usual layer of indentation, except for the Alpaca namespace, which being the project namespace, would be a waste of line length to use

## Comments
A very integral part of coding, comments help others to understand not only what you're doing, but why you're doing it.

### File Boilerplates
Each and every file of C and C++ code must include at the top a boilerplate of the following format.
```Cpp
/*
 * @file fileName.cpp
 * @brief A description of the file and it's function, that can span up to
 * multiple lines if necessary
 * 
 * Copyright (C) 2017 Alpaca Tech
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
```

### Documentation
Documentation should be present and follow the following format/example in header files for all namespaces, classes, typedefs, enumerations, variables, functions, etc, as to aid in others' understanding of your code.
```Cpp
/*
 * A detailed description of the function, variable, etc, and it's purpose, and
 * it can span multiple lines. Also take note of the break following this
 * description.
 * 
 * @param exampleParam An example of documentation for a parameter, that would
 * be included for each parameter of a function that has one.
 * @param param2 Notice the single space seperating this description of the
 * purpose of this parameter from the parameter name
 * @param third A third example parameter
 * @return A description of what this returns, if it is a function and it does
 * return something
 */
```
This documentation precedes the variable/function/etc in the lines before it.

### Descriptive Comments
Comments are also used to describe the purpose of and actions performed in a chunk/line of code.
These comments should use a `//` padded by one space on either side and, if the described code is one line, should follow this line. If the designated code is more than one line or this comment causes the line to exceed the 80 columb limit, it must be inserted on a new line *before* the designated line/chunk of code. Any subsequent overflow will be put on lines following this line until both the comment is complete and all lines of it are under 80 characters.
```Cpp
// A very very very very very very very very very very very very very very very
// very very very very very very very very very long description of the int y.
int y;
bool z; // A short description of the bool z
```

## Reccomendations
If you need to know about something not listed here, then feel free to drop us an email [here](mailto:alpacatech@gmx.com).

