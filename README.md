# Recursive Descent Parser

## Project Overview

The Recursive Descent Parser project implements a parser in C++ to convert a high-level programming language into a parse tree. The parser applies grammar rules, handles nested structures, and validates the syntax of input code using recursive descent parsing techniques. It can be used as part of a larger compiler project, eventually translating high-level code into VM code.

## Features

- Recursive descent parsing to handle complex, nested code structures.
- Syntax validation and error handling with detailed exception reporting.
- Converts high-level language tokens into a parse tree representation.
- Supports multiple grammar rules including:
  - Class declarations
  - Variable declarations
  - Subroutine definitions
  - Statements (if, while, let, do, return)
  - Expressions

## Project Structure

```
.
├── CompilerParser.cpp   # Core parser implementation
├── CompilerParser.h     # Header file for the parser
├── ParseTree.cpp        # Implementation for the ParseTree structure
├── ParseTree.h          # Header file for the ParseTree
├── Token.cpp            # Implementation for the Token class
├── Token.h              # Header file for the Token class
├── Main.cpp             # Main entry point for the program
├── Makefile             # Build script for compiling the project
```

### Main Components
- **CompilerParser**: Implements the recursive descent parsing logic, applying grammar rules to the token stream and building the parse tree.
- **ParseTree**: Data structure representing the parse tree, allowing for hierarchical storage of parsed tokens and rules.
- **Token**: Represents individual tokens in the input stream, encapsulating both the type and value of each token.
- **Main**: Entry point of the program; it initializes the parser and processes input.

## Requirements

- C++ Compiler (e.g., g++, clang++)
- Make (optional, if using the provided `Makefile`)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/recursive-descent-parser.git
   ```

2. Navigate to the project directory:
   ```bash
   cd recursive-descent-parser
   ```

3. Build the project using the `Makefile`:
   ```bash
   make
   ```

4. Run the program:
   ```bash
   ./Parser.out
   ```

## Usage

1. Prepare a high-level language source file containing the code you want to parse.

2. Run the parser on the input file:
   ```bash
   ./Parser.out <inputfile>
   ```

   Example:
   ```bash
   ./Parser.out program.jack
   ```

3. The parser will produce a parse tree representation of the input source code. If syntax errors are found, they will be reported.

## Example

Sample input (`program.jack`):
```jack
class Main {
   function void main() {
      var int x;
      let x = 10;
      do Output.printInt(x);
      return;
   }
}
```

Generated parse tree:
```
<class>
  <subroutineDec>
    <subroutineBody>
      <varDec>
      <letStatement>
      <doStatement>
      <returnStatement>
    </subroutineBody>
  </subroutineDec>
</class>
```

## Testing

The project includes sample test cases that can be used to verify the parser’s functionality. Run the following command to execute the test cases:
```bash
./Parser.out tests/testcase.jack
```
