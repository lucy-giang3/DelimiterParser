# DelimiterParser

## Overview 
DelimiterParser is a simple command-line utility that processes delimited data records (DSV format), tokenizes them into fields, and validates their structure. It ensures that each record contains the expected number of columns and prints them in a structured format.

## Dependencies
- Standard C libraries (stdio.h, stdlib.h, string.h, unistd.h, errno.h)
  
## Usage
[./DelimiterParser -c N < input_file] with N being the number of columns in the input data
