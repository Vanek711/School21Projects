#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""


RED='\033[0;91m'
GREEN='\033[1;92m'
CLEAR='\033[0m'
WHITE='\033[1;97m'


declare -a tests=(
"VAR s test_grep.txt"
"VAR for s21_grep.c"
"VAR -e int s21_grep.c"
"VAR -e while print s21_grep.c -f test_f_grep.txt"
"VAR -e while -e void s21_grep.c -f test_f_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo -e "$SUCCESS/$COUNTER ${GREEN}success${CLEAR} grep ${WHITE}$t${CLEAR}"
    else 
      (( FAIL++ ))
      echo -e "$FAIL $COUNTER ${RED}fail${CLEAR} grep ${WHITE}$t${CLEAR}"
    fi
    rm test_s21_grep.log test_grep.log
}


for var1 in i c l n h s v
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

for var1 in i c l n h s 
do
    for var2 in i c l n h s 
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

for var1 in i c l n h s 
do
    for var2 in i c l n h s 
    do
        for var3 in i c l n h s 
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

echo -e "\033[31mFAIL: $FAIL\033[0m"
echo -e "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
