## Project status

This project is unfinished. I'm currently working on other projects, so it's on hold.

As it stands, it contains the basic features, themselves limited to the minimum of what they should provide.

## Future plans

At some point, I'd like to:

- add features;
- go deeper on the existing ones;
- change the output format so the command integrates cleanly into scripts;
- add my own touch, so the utility has a reason to be used over another;
- explore what is rarely or poorly done in existing utilities, and provide a solution.

## Feature status

## Feature status

| Command | Description | Status |
|---|---|---|
| `ispng <file>` | Checks the 8-byte PNG signature | Done |
| `list <file>` | Lists every chunk: offset, type, size, critical/ancillary class | minimum |
| `cat <file>` | Prints the raw file as different format | minimum |
| `integrity <file>` | Check PNG integrity | minimum |
| `info <file>` | Decodes the IHDR: dimensions, bit depth, colour type, compression, filter and interlace methods, in plain text | minimum |
| `delmd <src> <dest>` | Writes a copy containing only the critical chunks, and reports the number of bytes removed | minimum |
| Text metadata injection | Inserting a `tEXt` chunk | Not implemented |

New Features incoming...
