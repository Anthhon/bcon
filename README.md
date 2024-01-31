# base-converter (bcon)

This repository contains a C program that converts a given number into binary, hexadecimal, and octal representations.

## Prerequisites

To compile and run the program, you need to have a C compiler installed on your system. The program is compatible with any C compiler that supports the C99 standard.

## Usage

1. Clone the repository to your local machine.

2. Navigate to the repository directory.

3. Compile the program using the following command:

```shell
   gcc -o bcon main.c
```

Replace program_name with your desired name for the executable.

4. Run the program with the following command:

```shell
   ./bcon <number> [options]
Replace <number> with the number you want to convert.
Available options:
    -v: Enable verbose mode.
```

## Example

```shell
  $ ./bcon 42 -v
  BINARY    HEXADECIMAL    OCTAL
  101010    0x2A           52
```

## Contributing

If you find any issues or have suggestions for improvement, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. Feel free to customize the content as per your requirements.

