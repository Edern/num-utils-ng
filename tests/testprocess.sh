#!/bin/bash

#This script should gather all the tests for the function process.

ERROR_NB=0
LAST_ERROR=0

../src/process /+1/ ../tests/test3 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "1" ] 
then
  echo -e "The detection of type error does not work properly"
  ERROR_NB=1
fi

../src/process -blabla ../tests/test3 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "2" ] 
then
  echo -e "The detection of option failure does not work properly"
  ERROR_NB=2
fi

../src/process 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "3" ] 
then
  echo -e "The detection of missing expression does not work properly"
  ERROR_NB=3
fi

../src/process rge ../tests/test3 2>/dev/null
LAST_ERROR=$?
if [ "$LAST_ERROR" -ne "4" ] 
then
  echo -e "The detection of wrong expressions does not work properly"
  ERROR_NB=4
fi

if [ "$ERROR_NB" -eq "0" ] 
then
  echo -e "All tests on process went well"
fi

exit $ERROR_NB
