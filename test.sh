#!/bin/sh

./measure ./test2 | awk '
/seconds.*Mbytes/ {
  print;
  if ($1 <= 1) print "speed requirement: PASSED";
  else print "speed requirement: FAILED";
  if ($3 <= 10) print "memory requirement: PASSED";
  else print "memory requirement: FAILED";
}

{
  print;
}
'
