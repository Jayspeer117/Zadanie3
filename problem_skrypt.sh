#!/bin/bash

a=(1 1 0 7 0 23)
b=(1 1 0 7 4 23)
c=(1 1 0 1 0 0)
d=(1 1 -1 -1 3 0)
e=(1 0 0 0 1 0)
f=(1 1 0 1 1 0)

result=(1 0 1 0 1 1)

for ind in $(seq 0 5); do
	out=$(./problem ${a[$ind]} ${b[$ind]} ${c[$ind]} ${d[$ind]} ${e[$ind]} ${f[$ind]})
	
	if [ "$out" != "${result[$ind]}" ] ; then
		echo "in" ${a[$ind]} ${b[$ind]} ${c[$ind]} ${d[$ind]} ${e[$ind]} ${f[$ind]} 
		echo "real out" $out
		echo "expected out" ${result[$ind]}
	fi
done
