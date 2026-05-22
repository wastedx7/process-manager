# Process Manager

<p align="center">
  <strong>A compact Linux process viewer built in C.</strong><br>
  Lists running processes from <code>/proc</code> in a clean table with PID, command name, CPU time, and resident memory.
</p>

## Overview

`process-manager` is a lightweight terminal utility that scans the Linux `/proc` filesystem, collects basic process metrics, and prints them in a formatted table.

It is intentionally small and dependency-free: the code uses only the C standard library plus POSIX directory and process interfaces.

## Features

- Enumerates numeric entries in `/proc` to discover running processes
- Reads per-process command names from `/proc/<pid>/stat`
- Reads CPU time fields:
  - `utime`
  - `stime`
- Reads resident memory usage from `/proc/<pid>/status` via `VmRSS`
- Prints a readable ASCII table directly to stdout
- Uses a small helper layer for string and character utilities

## Output

The program prints rows similar to this:

```text
+--------+----------------------+--------------+--------------+--------------+
| PID    | Name                 | utime        | stime        | VmRSS KB     |
+--------+----------------------+--------------+--------------+--------------+
| 1234   | bash                 | 42           | 8            | 3168         |
| 2281   | code                 | 512          | 97           | 184320       |
+--------+----------------------+--------------+--------------+--------------+
```

## Requirements

- Linux
- A `/proc` filesystem
- GCC or another C compiler
- GNU Make

## Build

From the project root:

```bash
make
```

This produces the executable named `main`.

To remove build artifacts:

```bash
make clean
```

## Run

After building:

```bash
./main
```

## Project Structure

- `src/main.c` - program entry point and table rendering
- `src/functions.c` - `/proc` parsing and process collection
- `src/helper.c` - helper functions used by the parser
- `src/main.h` - shared declarations and data structures
- `makefile` - build rules

## Implementation Notes

- The program iterates over `/proc`, filters numeric directory names, and treats them as process IDs.
- `read_processes_stats()` parses `/proc/<pid>/stat` to extract the process name, `utime`, and `stime`.
- `read_vmrss()` scans `/proc/<pid>/status` for `VmRSS`.
- `count_procs()` stores the collected results into a fixed-size array capped by `MAX_PROCS` in `src/main.h`.

## Limitations

- Linux only: the code depends on `/proc`, so it does not run natively on Windows or macOS.
- No sorting or filtering: processes are shown in the order they are discovered in `/proc`.
- No live refresh: this is a snapshot view, not an interactive monitor.
- CPU values are reported as raw jiffies, not normalized percentages.
- Memory is reported as resident set size in kilobytes.

## Extending The Tool

Some natural next improvements would be:

- Add sorting by PID, CPU time, or memory
- Convert jiffies into human-readable CPU usage percentages
- Add command-line filters by process name or PID
- Handle malformed `/proc` entries more defensively
- Support width-aware formatting for very long process names

## License

This project is distributed under the terms of the MIT License. See [LICENSE](LICENSE).
