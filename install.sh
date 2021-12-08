#!/bin/bash

success=0

gcc src/quees.c -lm -o /usr/local/bin/quees && \
rm -rf /usr/local/share/man/man1/quees.1.gz && \
success=1

if [ ! -d /usr/local/share/man/man1 ]
    then
        mkdir /usr/local/share/man/man1
fi
cp quees.1.gz /usr/local/share/man/man1/quees.1.gz
if [ $success -eq 1 ]
    then
        echo "quees installation is completed"
        echo "run quees --help for usage information"
    else 
        echo "quees installation failed!"
fi
