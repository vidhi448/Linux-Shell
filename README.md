# Linux-Shell
Course: Operating System

Designed a basic linux shell that can handle  internal and external commands and their options using standard C libraries.

Following 10 commands have been implemented with 3 options each-

### Internal Commands 
1. cd - System call used -chdir()
   1. Options: 
       1. -L - force symbolic links to be followed: resolve symbolic links in DIR after processing instances of `..'
       2. --help - Display the help and exits
   2. Errors:
       1. If the directory is not present error will be printed that “No such file or directory”
       2. If option is not present then error will be printed “No such option or directory or file”
2. echo:
   1. Options:
       1. -n - do not output the trailing newline
       2. -E - disable interpretation of backslash escapes (default)
   2.  Errors:
       1. If no argument is passed to echo error will be printed that “Argument required
3. history:
   1. Options -
      1. -c clear the history list by deleting all of the entries
      2. -d delete the history entry at position OFFSET.
   2. Errors -
      1. If Option is not present, then error will be printed that “Option not present”
      2. If in -d option the offset is not present, then error will be Printed that “Offset Entered is Wrong”.
4. pwd - System call used - getcwd()
   1. Options -
      1. -L print the value of $PWD if it names the current working directory
      2. -P print the physical directory, without any symbolic links
      3. --help Display the help and exits
   2. Errors -
      1. If Option is not present, then error will be printed tha“Option not found
5. exit - System call used - exit()
    1. Options -
        1. exit [n] - Exits the shell with a status of N.
        2. --help - Display the help and exits
### External Commands
6. ls - System call used - scandir()
    1. Options -
        1. -a - do not ignore entries starting with ‘.’
        2. -m - fill width with a comma separated list of entries
        3. -1 - list one file per line.
    2. Errors -
        1. arguments are not enough.
        2. There is no such file or directory as the path given as argument
7. cat - function used fgets()
    1. Options -
        1. -n - number all output lines
        2. -E - display $ at end of each line
    2. Errors -
        1. file don’t exists.
        2. User doesn’t have access to the file
8. date -
    1. Options -
        1. -u - print or set Coordinated Universal Time (UTC)
        2. --help - Display the help and exits
    2. Errors -
        1. If Option is not present, then error will be printed that “No such Option”
9. rm - System call used - remove()
    1. Options -
        1. -i - prompt before every removal (asks whether you want to remove the file)
        2. --help - Display the help and exits
    2. Errors -
        1. file don’t exists.
        2. Given path is a directory.
        3. User doesn’t have access to the file.
10. mkdir - System call used - mkdir()
    1. Options -
        1. -v - prints a message for each created directory
        2. --help - Display the help and exits
    2. Errors -
        1. The named file exists.
        2. The parent directory resides on a read-only file system.
        3. A component of the path prefix is not a directory.

# Run Command
make
