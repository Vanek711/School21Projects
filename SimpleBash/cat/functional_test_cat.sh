#!/bin/bash

SUCCESS=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"VAR test_case_cat.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_1.txt
    cat $t > test_2.txt
    DIFF_RES="$(diff -s test_1.txt test_2.txt)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_1.txt and test_2.txt are identical" ]
    then
      (( SUCCESS++ ))
        echo -e "\033[1;92m$SUCCESS\033[0m/$COUNTER \033[1;92msuccess\033[0m ./s21_cat $t"
    fi
    rm test_1.txt test_2.txt
}

# 1 параметр
for var1 in b e n s t v E T
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 параметра
for var1 in b e n s t v E T
do
    for var2 in b e n s t v E T
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

# 3 параметра
for var1 in b e n s t v E T
do
    for var2 in b e n s t v E T
    do
        for var3 in b e n s t v E T
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

# 4 параметра
for var1 in b e n s t v E T
do
    for var2 in b e n s t v E T
    do
        for var3 in b e n s t v E T
        do
            for var4 in b e n s t v E T
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

echo -e "\033[31mFAIL: $FAIL\033[0m"
echo -e "\033[32mSUCCESS: $SUCCESS\033[0m"
