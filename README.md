# HashString Algorithm

A custom string hashing algorithm implemented in C++ that converts file contents into a hexadecimal hash string using a column-based matrix approach.

## What the Algorithm Does

The HashString algorithm performs the following steps:

1. **Input Processing**: Reads a filename and column count from standard input
2. **File Reading**: Loads the entire file content into memory
3. **Matrix Arrangement**: Arranges the file content characters into a matrix with the specified number of columns
4. **Padding**: Fills incomplete rows with the column number converted to string
5. **ASCII Conversion**: Converts all characters (including padding) to their ASCII values
6. **Hexadecimal Encoding**: Converts ASCII values to uppercase hexadecimal representation
7. **Hash Generation**: Returns a truncated hexadecimal string as the final hash

The algorithm creates a unique hash based on both the file content and the specified column structure, making it sensitive to both content changes and the chosen column parameter.

## How to Compile and Run

### Prerequisites
- A C++ compiler (g++, clang++, etc.)
- Standard C++ libraries

### Compilation
```bash
g++ main.cpp
```
or
```bash
g++ main.cpp -o main
```

### Running the Program
The program expects two inputs via standard input:
1. Filename (path to the file to hash)
2. Number of columns (integer)

```bash
./main < input.txt
```

Or interactively:
```bash
./hashstring
filename.txt
32
```

## Examples

### Example 1: Text File Hashing

**Input File** (`example1.txt`):
```
Hello World!
```

**Input to Program**:
```
example1.txt
16
```

**Program Execution**:
```bash
echo -e "example1.txt\n16" | ./hashstring
```

**Output**:
```
File length: 12 bytes
File contents:
Hello World!
Output HEX: 48656C6C
```

**Explanation**:
- The 12-character string "Hello World!" is arranged in a 16-column matrix
- Since the content is shorter than 16 columns, the remaining 4 positions are filled with "16" (the column number)
- The first row becomes: ['H','e','l','l','o',' ','W','o','r','l','d','!','1','6','1','6']
- ASCII values: [72,101,108,108,111,32,87,111,114,108,100,33,49,54,49,54]
- Hexadecimal: 48656C6C6F20576F726C642131363136
- Truncated output (cols/4*2 = 8 characters): 48656C6C

### Example 2: Longer Text with Multiple Rows

**Input File** (`example2.txt`):
```
Hashing is a technique used in computer science to map data of arbitrary size to fixed-size values. 
It is commonly used in hash tables, cryptography, and data integrity checks. 
A good hash function distributes input data uniformly across the output range, minimizing collisions. Hashing enables efficient data retrieval, making it essential for algorithms and data structures in modern software development.
```

**Input to Program**:
```
example2.txt
32
```

**Program Execution**:
```bash
echo -e "example2.txt\n32" | ./hashstring
```

**Output**:
```
File length: 409 bytes
File contents:
Hashing is a technique used in computer science to map data of arbitrary size to fixed-size values. 
It is commonly used in hash tables, cryptography, and data integrity checks. 
A good hash function distributes input data uniformly across the output range, minimizing collisions. Hashing enables efficient data retrieval, making it essential for algorithms and data structures in modern software development.
Output HEX: 48617368696E6720
```

**Explanation**:
- The 409-character content is arranged in rows of 32 columns each
- This creates 12 full rows and 1 partial row (with 25 characters)
- The partial row is padded with "32" values to complete the 32-column requirement
- Each character is converted to ASCII, then to hexadecimal
- The final hash is truncated to 16 characters (32/4*2): 48617368696E6720

## Technical Details

### Hash Output Length
The output hash length is calculated as: `(columns / 4) * 2`

### Padding Strategy
When file content doesn't fill complete rows:
- Remaining positions are filled with the string representation of the column count
- Each digit of the column number contributes its ASCII value to the hash

### Character Processing
- All characters (including newlines, spaces, and padding) are converted to ASCII values
- ASCII values are then converted to uppercase hexadecimal representation
- The hexadecimal strings are concatenated to form the complete hash

### Memory Efficiency
- The algorithm reads the entire file into memory at once
- Uses vector reservations to optimize memory allocation
- Suitable for reasonably-sized text files

## Algorithm Characteristics

- **Deterministic**: Same input always produces the same hash
- **Content Sensitive**: Any character change affects the hash
- **Structure Sensitive**: Different column counts produce different hashes for the same content
- **Fixed Output Length**: Hash length depends only on the column parameter
- **Collision Possible**: Different inputs can theoretically produce the same hash

## Use Cases

This hashing algorithm is suitable for:
- File integrity verification with specific formatting requirements
- Creating content signatures with structural awareness
- Educational purposes for understanding custom hash implementations
- Applications requiring both content and layout sensitivity
