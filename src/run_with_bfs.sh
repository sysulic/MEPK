#!/bin/bash

timeout() {

    time=$1

    command="/bin/sh -c \"$2\""

    echo $command

    expect -c "set timeout $time; spawn -noecho $command; expect timeout { exit 1 } eof { exit 0 }"    

    if [ $? = 1 ] ; then
        echo "Timeout after ${time} seconds"
    fi

}

test_cases_set="../benchmarks/test_cases"
program="./start"
cat $test_cases_set | while read one_test
do
	[ -z "$one_test" ] && continue
	echo "========================================================================================"
    timeout 100 "$program $one_test 2"
done

exit 0