#!/bin/bash

gcc src/quees.c -lm -o /usr/local/bin/quees

cp -f quees.1.gz /usr/local/share/man/man1
mandb 

echo "quees installation is completed"
echo "run quees --help for usage information"
