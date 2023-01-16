## RPNS
Reverse Polish Notation Script is a (**heavily WIP**) scripting language. To run, provide a source file to the `rpns` command
#### How it works
There are five main operations currently, those being:
- `+` Add top two numbers on the stack
- `-` Subtract top two numbers on the stack
- `*` Multiply top two numbers on the stack
- `/` Divide top two numbers on the stack
- `%` Modulo top two numbers on the stack

There are also three main conditionals, those being:
- `=` Check for equality
- `<` Check for greater number
- `>` Check for lesser number

To push values onto the stack, simply write out the value you want to push. Then, if you want to<br> do math, simply use a operator, and the result of the operation will be pushed to the <br>stack. To print out the result, use the `.` command.
#### Conditionals/Loops
In order to execute a conditional block, the most recent conditional statement must have<br>evaluated to `TRUE`.
##### IF statement syntax
To start an `if` statement, simply use the `if` keyword, and to end an `if` block use <br>the `endif` keyword.
##### WHILE statement syntax
To start a `while` statement, use the `while` keyword, and to end a `while` block use the<br> `endwhile` keyword.
