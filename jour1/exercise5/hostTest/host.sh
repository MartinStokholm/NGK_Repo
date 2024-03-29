#!/bin/bash
function code {
    echo "$@"
    echo '```'  
    $@
    echo '```'
}
echo "## Running host test on "$1""  > "$2"
echo '### No flags' >> "$2"
echo No flags test. 
code host "$1" >> "$2"
echo '### -a flag' >> "$2"
echo -a flag test
code host -a "$1" >> "$2"
echo '### -4 flags' >> "$2"
echo -4 flag test
code host -4 "$1" >> "$2"
echo '### -6 flags' >> "$2"
echo -6 flag test
code host -6 "$1" >> "$2"
echo '### -d flags' >> "$2"
echo -d flag test
code host -d "$1" >> "$2"
