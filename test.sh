#!/bin/sh

echo "1 2 3 .s" | ./4th | if egrep -q '^  <3> 1 2 3 ok$' ; then echo yes; else echo no; fi
echo "1 2 3 . " | ./4th | if egrep -q '^  3 ok' ; then echo yes; else echo no; fi
echo "2 2 + .s" | ./4th | if egrep -q '^  <1> 4 ok' ; then echo yes; else echo no; fi
echo "2 3 * .s" | ./4th | if egrep -q '^  <1> 6 ok' ; then echo yes; else echo no; fi
echo "2 3 5 swap 6 .s" | ./4th | if egrep -q '^  <4> 2 5 3 6 ok' ; then echo yes; else echo no; fi
echo "2 3 5 swap 6 dup .s" | ./4th | if egrep -q '^  <5> 2 5 3 6 6 ok' ; then echo yes; else echo no; fi
echo "2 3 5 swap 6 dup . . .s" | ./4th | if egrep -q '^  6 6 <3> 2 5 3 ok' ; then echo yes; else echo no; fi
echo "1 2 3 drop .s" | ./4th | if egrep -q '^  <2> 1 2 ok' ; then echo yes; else echo no; fi
#
echo ": x 1 if 3 then 5 3 + ; x .s" | ./4th  | if egrep -q '^  <2> 3 8 ok' ; then echo yes; else echo no; fi
echo ": x 1 if 5 3 * then 5 3 + ; x .s" | ./4th  | if egrep -q '^  <2> 15 8 ok' ; then echo yes; else echo no; fi
echo ": x 0 if 5 3 * then 5 3 + ; x .s" | ./4th  | if egrep -q '^  <1> 8 ok' ; then echo yes; else echo no; fi
echo ": x 0 if 5 3 * else 5 3 + then ; x .s" | ./4th  | if egrep -q '^  <1> 8 ok' ; then echo yes; else echo no; fi
echo ": x 1 if 5 3 * else 5 3 + then ; x .s" | ./4th  | if egrep -q '^  <1> 15 ok' ; then echo yes; else echo no; fi
echo ": x 0 0 if if 1 else 2 then else  if 3 else 4 then then ; x .s" | ./4th  | if egrep -q '^  <1> 4 ok' ; then echo yes; else echo no; fi
echo ": x 1 0 if if 1 else 2 then else  if 3 else 4 then then ; x .s" | ./4th  | if egrep -q '^  <1> 3 ok' ; then echo yes; else echo no; fi
echo ": x 0 1 if if 1 else 2 then else  if 3 else 4 then then ; x .s" | ./4th  | if egrep -q '^  <1> 2 ok' ; then echo yes; else echo no; fi
echo ": x 1 1 if if 1 else 2 then else  if 3 else 4 then then ; x .s" | ./4th  | if egrep -q '^  <1> 1 ok' ; then echo yes; else echo no; fi
#
echo "variable xyz 3 xyz ! 6 xyz dup @ rot + swap ! xyz @ .s" | ./4th -s | if egrep -q '^  <1> 9 ok' ; then echo yes; else echo no; fi
echo ": +! dup @ rot + swap ! ; variable xyz 3 xyz ! 6 xyz +! xyz @ .s" | ./4th -s | if egrep -q '^  <1> 9 ok' ; then echo yes; else echo no; fi

echo ": beginloop 5 begin 1 - dup 42 emit if 0 else 1 then until ; beginloop" |./4th | if egrep -q '^ \*\*\*\*\* ok' ; then echo yes; else echo no; fi

echo "2 7 9 3 quadratic .s" |./4th | if egrep -q '^  <1> 48 ok' ; then echo yes; else echo no; fi
