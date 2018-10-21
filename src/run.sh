#!/bin/bash

timeout() {

    time=$1

    command="/bin/sh -c \"$2\""

    echo $command

    expect -c "set echo \"-noecho\"; set timeout $time; spawn -noecho $command; expect timeout { exit 1 } eof { exit 0 }"    

    if [ $? = 1 ] ; then
        echo "Timeout after ${time} seconds"
    fi

}

test_cases_set="../benchmarks/test_cases"
program="./start"
cat $test_cases_set | while read one_test
do
    timeout 1800 "$program $one_test"
done

exit 0