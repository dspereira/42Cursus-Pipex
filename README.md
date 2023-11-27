# 42Cursus-Pipex

This project is an integral part of the 42Lisboa curriculum and aims to implement a program capable of executing commands, replicating the functionality of a shell command line.
The objective of this project is to create a program that receives commands as arguments and connects those commands with pipes, similar to a shell. The first parameter has to be an input file, and the last one an output file.

The program is designed to be executed as follows:
```shell
./pipex infile cm1 cm2 cmd3 ... cmdn outfile
```
This is equivalent to running the following command in the shell:
```shell
< infile cm1 | cm2 | cmd3 | ... | cmdn > outfile
```

## Installation / Usage

This project is designed to work on Linux and macOS.

Clone repo:
```shell
git clone https://github.com/dspereira/42Cursus-Pipex.git pipex
```

Build:
```shell
make
```
or
```shell
make re
```

Usage example:
```shell
./pipex infile "ls -la" cat outfile
```

## License

This project is licensed under the [MIT License](https://github.com/dspereira/42Cursus-Pipex/blob/main/LICENSE).

## Contact

If you have any questions or comments about this project, please feel free to contact me at diogo.s.pereira@outlook.pt.
