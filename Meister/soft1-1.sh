#!/bin/bash

echo "数を入力"
read n 

echo "数を入力"
read m

if [ $n -gt $m ]; then
	ra=$m
	m=$n
	while [[ $ra -gt 0 ]]
	do
		n=$m
		m=$ra
		ra=`expr $n % $m `
	done

	echo "2数の最大公約数は$m"
else
	ra=$n
	n=$m
	while [[ $ra -gt 0 ]]
	do
		m=$n
		n=$ra
		ra=`expr $m % $n`
	done

	echo "2数の最大公約数は$n"
fi

exit 0
