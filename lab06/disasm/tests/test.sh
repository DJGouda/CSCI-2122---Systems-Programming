#!/bin/sh

echo ======================================================
echo ====================== TEST $1 ========================
echo ======================================================
if [ -f $1 ]; then 
  echo PASSED
else
  echo FAILED
  echo File $1 not found.
  exit 1
fi
