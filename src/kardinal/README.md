# Kardinal

## How to compile
Kardinal only needs the basic C libraries that are typically present in any Linux based OS. Specifically, it requires stdio.h, stdlib.h, string.h and ctype.h. To compile, navigate into the kardinal directory and type
```
make
```
The compilation should not throw back any warnings.

## How to run
To evaluate a kardinal script, navigate to the folder with the kardinal executable and run the following:
```
./kardinal <path to script>
```
### Options
--version: When given as the only argument, the program will return the version number of the given kardinal executable
--debug: Has to be given after the path to input script. When given, this command will print all the internal debug messages that are typically suppressed.
