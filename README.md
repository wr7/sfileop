# sfileop
sfileop (simple file operation) is two simple command-line tools to read (sread) and write (swrite) to files in hexadecimal.
# Compilation
To compile sfileop, just use cmake. To easily compile something with cmake, just run `mkdir build && cd build && cmake .. --build`. Currently there is no way to install sfileop other than to manually copy the binaries.

Alternatively, you could run cmake with the `-DFILE_IO=POSIX` (`cmake -DFILE_IO=POSIX ..`) to use POSIX file functions and not the file functions in `stdio.h`
