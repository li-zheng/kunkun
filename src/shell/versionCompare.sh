#!/bin/sh
vercomp () {
    if [ "$1" = "$2" ]
    then
        return 0
    fi

    local first second
    first=`echo $1 | grep -o '^[0-9]*\.' | grep -o '[0-9]*'`
    second=`echo $2 | grep -o '^[0-9]*\.' | grep -o '[0-9]*'`    
    if [ -z "$first" ]
    then
      first=0
    fi
    if [ -z "$second" ]
    then
      second=0
    fi
    if [ $first -gt $second ] 
    then
      return 1
    fi
    if [ $first -lt $second ] 
    then
      return 2
    fi
    
    first=`echo $1 | grep -o '\.[0-9]*' | grep -o -m 1 '[0-9]*'`
    second=`echo $2 | grep -o '\.[0-9]*' | grep -o -m 1 '[0-9]*'`
    if [ -z "$first" ]
    then
      first=0
    fi
    if [ -z "$second" ]
    then
      second=0
    fi
    if [ $first -gt $second ] 
    then
      return 1
    fi
    if [ $first -lt $second ] 
    then
      return 2
    fi
    
    first=`echo $1 | grep -o '\.[0-9]*\.[0-9]*$' | grep -o '\.[0-9]*$' | grep -o '[0-9]*'`
    second=`echo $2 | grep -o '\.[0-9]*\.[0-9]*$' | grep -o '\.[0-9]*$' | grep -o '[0-9]*'`
    if [ -z "$first" ]
    then
      first=0
    fi
    if [ -z "$second" ]
    then
      second=0
    fi

    if [ $first -gt $second ] 
    then
      return 1
    fi
    if [ $first -lt $second ] 
    then
      return 2
    fi
    
    return 0
}

testvercomp () {
    vercomp $1 $2
    case $? in
        0) op='=';;
        1) op='>';;
        2) op='<';;
    esac
    if [ $op != $3 ]
    then
        echo "FAIL: Expected '$3', Actual '$op', Arg1 '$1', Arg2 '$2'"
    else
        echo "Pass: '$1 $op $2'"
    fi
}

# Run tests
# argument table format:
# testarg1   testarg2     expected_relationship
echo "The following tests should pass"
while read -r test
do
    testvercomp $test
done << EOF
1.0.0            1.0.0            =
2.1.0          2.2.0          <
3.0.5     3.0.4      >
4.08.1         4.08.2      <
3.2.1  3.2.0          >
3.2.0          3.2.1      <
1.2.1          2.1.0          <
2.1.0          1.2.0          >
5.6.7        5.6.7        =
1.1.1        1.01.1       =
1.13.1       1.3.1    >
1.0     1.0.0        =
1.3.2   1.3     >
1.14    1.3.0   >
1.5.3   1.4     >
EOF

echo "The following test should fail (test the tester)"
testvercomp 1 1 '>'
