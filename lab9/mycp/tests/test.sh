#!/bin/sh

echo ======================================================
echo ====================== TEST $1 ========================
echo ======================================================
rm -f tests/test.$1.out
if [ -f tests/test.$1.old ]; then
  cp tests/test.$1.old tests/test.$1.out
fi

if timeout 10 ./$2/$3 tests/test.$1.src tests/test.$1.out; then 
  if diff tests/test.$1.src tests/test.$1.out; then
    echo PASSED
  else
    echo FAILED
    echo ======
    echo Files are not the same!
    exit 1
  fi
elif [ $? -eq 124 ]; then
  echo TIMEOUT
  exit 1
else 
  echo Abnormal program termination: the program crashed
  echo Exit code $?
  exit 1
fi
