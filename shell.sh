Factorial Using Recursion:-
#!/bin/bash

# Factorial using Recursion
factorial() {
  if [ $1 -le 1 ]; then
    echo 1
  else
    prev=$(factorial $(( $1 - 1 )))
    echo $(( $1 * prev ))
  fi
}

echo "Factorial of 5: $(factorial 5)"

Palindrome Check for a String:-

#!/bin/bash

# Palindrome Check for a String
is_palindrome() {
  input=$1
  reversed=$(echo $input | rev)
  if [ "$input" == "$reversed" ]; then
    echo "$input is a palindrome"
  else
    echo "$input is not a palindrome"
  fi
}

is_palindrome "racecar"
is_palindrome "hello"

Bubble Sort:-
#!/bin/bash

# Bubble Sort
bubble_sort() {
  arr=("$@")
  n=${#arr[@]}
  
  for (( i=0; i<$n; i++ ))
  do
    for (( j=0; j<$n-i-1; j++ ))
    do
      if [ ${arr[$j]} -gt ${arr[$((j+1))]} ]; then
        temp=${arr[$j]}
        arr[$j]=${arr[$((j+1))]}
        arr[$((j+1))]=$temp
      fi
    done
  done

  echo "Sorted Array: ${arr[@]}"
}

bubble_sort 5 2 9 1 5 6


Count Occurrences of Substring
#!/bin/bash

# Count Occurrences of Substring
count_occurrences() {
  string=$1
  substring=$2
  count=$(grep -o "$substring" <<< "$string" | wc -l)
  echo "The substring '$substring' occurs $count times"
}

count_occurrences "hello world, hello again" "hello"


Sum of Digits:-
#!/bin/bash

# Sum of Digits
sum_digits() {
  number=$1
  sum=0
  while [ $number -gt 0 ]; do
    digit=$(( number % 10 ))
    sum=$(( sum + digit ))
    number=$(( number / 10 ))
  done
  echo "Sum of digits: $sum"
}

sum_digits 12345


Reverse Digits:-
#!/bin/bash

# Reverse Digits
reverse_digits() {
  number=$1
  reverse=0
  while [ $number -gt 0 ]; do
    digit=$(( number % 10 ))
    reverse=$(( reverse * 10 + digit ))
    number=$(( number / 10 ))
  done
  echo "Reversed number: $reverse"
}

reverse_digits 12345


Armstrong Number Check:-
#!/bin/bash

# Armstrong Number Check
is_armstrong() {
  number=$1
  sum=0
  temp=$number
  length=${#number}
  
  while [ $temp -gt 0 ]; do
    digit=$(( temp % 10 ))
    sum=$(( sum + digit ** length ))
    temp=$(( temp / 10 ))
  done
  
  if [ $sum -eq $number ]; then
    echo "$number is an Armstrong number"
  else
    echo "$number is not an Armstrong number"
  fi
}

is_armstrong 153
is_armstrong 123