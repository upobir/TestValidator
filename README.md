# TestValidator
A short library to validate tests created for competitive programming problems

## How to use

Copy the `src/TestValidator.hpp` contents and change the main function to your requirements. That's it! Change the input and output stream according to your requirement. If the input is validated then it will output validated, else it will throw exception.

#### Validating in online judge
If the input is validated then it will output validated which as is not the expected output will cause `Wrong Answer`, else it will throw exception causing `Runtime Error`. So, we are expecting `Wrong Answer` on all test cases. 

Your OJ might skip test cases if it encounters WA. Contact OJ support to solve this issue.

## Documentation
### Constructor
```cpp

Validator(std::istream &is, std::ostream &_os)
```
The Validator constructor initializes the validator, taking in input and output streams.

**Parameters:**

- is: Input stream to read data from.
- _os: Output stream for validation messages.

**Example:**
```cpp
Validator validator(std::cin, std::cout);
```

### Constraint Checkers
#### Check Number is Between a Range
```cpp
template<class T>
bool checkNumberIsBetween(T &x, T lowerLimit, T upperLimit, std::string msg = "")
```
Validates if a given number x lies between lowerLimit and upperLimit.

**Parameters:**

- x: The number to validate.
- lowerLimit: Lower bound of the range.
- upperLimit: Upper bound of the range.
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
int num = 5;
validator.checkNumberIsBetween(num, 1, 10, "Number out of range");
```
#### Check Character Matches Class
```cpp
bool checkCharMatchesClass(char &x, std::string charClass, std::string msg = "")
```
Validates if the character x matches any character in the specified charClass.

**Parameters:**

- x: Character to validate.
- charClass: String specifying valid characters.
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
char ch = 'a';
validator.checkCharMatchesClass(ch, "abc", "Invalid character");
```
#### Check String Length Between
```cpp
bool checkStringLengthBetween(std::string &x, size_t lowerLimit, size_t upperLimit, std::string msg = "")
```
Ensures the length of string x falls within the range [lowerLimit, upperLimit].

**Parameters:**

- x: String to validate.
- lowerLimit: Minimum length.
- upperLimit: Maximum length.
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
std::string str = "hello";
validator.checkStringLengthBetween(str, 3, 10);
```
#### Check Interval
```cpp
template<class T>
bool checkInterval(T &start, T &end, T lowerLimit, T upperlimit, std::string msg = "")
```
Validates that start and end represent an interval within [lowerLimit, upperLimit].

**Parameters:**

- start: Interval start.
- end: Interval end.
- lowerLimit: Minimum allowable start.
- upperLimit: Maximum allowable end.
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
int start = 1, end = 5;
validator.checkInterval(start, end, 1, 10);
```
#### Check Condition
```cpp
bool checkCondition(bool condition, std::string msg = "")
```
Validates a custom condition.

**Parameters:**

- condition: Boolean condition to check.
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
bool isValid = (x > 0);
validator.checkCondition(isValid, "Condition not met");
```

### Readers with Constraint Checker

#### Read Integer Between
```cpp
template<class T>
bool readIntegerBetween(T &x, T lowerLimit, T upperLimit, std::string msg = "")
```
`readIntegerBetween` reads an integer x and validates if the integer lies within [lowerLimit, upperLimit].

**Parameters:**

- x: Variable to store the read integer.
- lowerLimit: Lower bound of the range.
- upperLimit: Upper bound of the range.
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
int n;
validator.readIntegerBetween(n, 1, 500);
```

#### Read Interval Between
```cpp
template<class T>
bool readIntervalBetween(T &start, T &end, T lowerLimit, T upperLimit, std::string msg = "")
```
`readIntervalBetween` reads two integers, start and end, and ensures that the interval they form lies within [lowerLimit, upperLimit].

**Parameters:**
- start: Variable to store the start of the interval.
- end: Variable to store the end of the interval.
- lowerLimit: Minimum allowable start value.
- upperLimit: Maximum allowable end value.
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
int start, end;
validator.readIntervalBetween(start, end, 1, 10);
```

#### Read Character and Match Class

```cpp
bool readCharAndMatchClass(char &x, std::string charClass, std::string msg = "")
```
`readCharAndMatchClass` reads a character x and validates if it belongs to the specified charClass.

**Parameters:**
- x: Variable to store the read character.
- charClass: String specifying valid characters.
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
char ch;
validator.readCharAndMatchClass(ch, "abc", "Invalid character");
```
#### Read String Between Length and Match Class

```cpp
bool readStringBetweenLengthAndMatchClass(std::string &x, size_t lowerLimit, size_t upperLimit, std::string charClass, std::string msg = "")
```
`readStringBetweenLengthAndMatchClass` reads a string x, ensures its length falls between [lowerLimit, upperLimit], and checks that each character matches the specified charClass.

**Parameters:**
- x: Variable to store the read string.
- lowerLimit: Minimum length of the string.
- upperLimit: Maximum length of the string.
- charClass: String specifying valid characters.
msg: Custom error message if validation fails (optional).

**Example:**
```cpp
std::string str;
validator.readStringBetweenLengthAndMatchClass(str, 1, 10, "abc123");
```
### Additional Readers

#### Read Space Character

```cpp
bool readSpaceChar(std::string msg = "")
```
`readSpaceChar` reads a single whitespace character. If the next character is not a space, it reports an error.

**Parameters:**
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
validator.readSpaceChar("Expected a space character");
```
#### Read End of Line

```cpp
bool readEndOfLine(std::string msg = "")
```
`readEndOfLine` reads a newline character. If the next character is not a newline, it reports an error.

**Parameters:**
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
validator.readEndOfLine("Expected end of line");
```
#### Read End of File

```cpp
bool readEndOfFile(std::string msg = "")
```
`readEndOfFile` checks if the end of the file has been reached. If not, it reports an error.

**Parameters:**
- msg: Custom error message if validation fails (optional).

**Example:**
```cpp
validator.readEndOfFile("Expected end of file");
```





#### Read Integer in between a range
```cpp
bool readIntegerBetween(T &x, T lowerLimit, T upperLimit, std::string msg = "") 
```  
`readIntegerBetween` reads an integer `x` and validates if the said integer is between the expected range. 

<details>

<summary>Example</summary>

```cpp
int n;
validator.readIntegerBetween(n, 1, 500);
```
</details>

# Todo
- Test integer read
- Use exception
- Mistakes always consume