#!/bin/awk
BEGIN {
	max = 0
	tmp = 0
	linie = 1
	linie_max = 1
{
{
	if($0 == $linie) {
		tmp ++
	}
	else {
		if(tmp > max) {
		      max = tmp
	      	      linie_max = linie
		}	      

