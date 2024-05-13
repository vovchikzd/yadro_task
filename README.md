## Build
``` shell
cmake -S . -B .build && cmake --build .build
```

## Usage
``` shell
ext-sort INPUT FILE [OPTION ARGUMENT(S)]

Tape file (input file) must has numbers with padding up to 11 characters plus
space/tab/newline separator, otherwise all operations (write/read/rewind/shift)
to this tape are ambiguous
All invalib options will be ignored (as well as all unrecognized arguments)
First argument being a file is considered as input file

Options:
     -h, --help    print this help message (in case this option will be pass
                   with any others options it will be ignored)
     
     -o,           specify name of outputs file (default is name of input file
                   with .res format)
     
     -c,           specify config file, all settings are written in in the
                   order 'write read rewind shift' and must be space/tab/newline
                   separated. All delays in seconds. Optionally as fifth setting
                   can be specifed max availabe RAM in bytes
     
     -m,           specify max available RAM for sort in bytes
     
     -M,           specify max abailable RAM for sort in megabytes

Default value for any setting is zero.
To skip any setting in config file, its value must be zero.
If max RAM not specified (or specified as zero) I assume that there isn't
restriction in RAM usage.
In case max RAM usage is specified both through config file and argument,
the value from file is used
All numbers are expected to be integer non-negative values, otherwise will be
used default (zero) value
```

