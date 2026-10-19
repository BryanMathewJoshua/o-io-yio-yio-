#!/usr/bin/env bash

# This script checks the formatting of C++ source files using clang-format.  Some file have explicit
# section students are to complete, while other files are created by the student in their entirety.
# For files with explicit fill-in-the-blank (TO-DO) sections, the script will only check the formatting
# of those sections.  For files without explicit sections, the script will check the formatting of the entire file.
#
# See Parameter Expansion section of Bash man page for "%%"'s' Remove matching suffix pattern
# behavior (https://linux.die.net/man/1/bash)
#  ${parameter,,}         ==> lower case
#  ${parameter^^}         ==> upper case
#  ${parameter%word}      ==> Remove shortest matching suffix pattern
#  ${parameter%%word}     ==> Remove longest  matching suffix pattern
#  ${parameter#word}      ==> Remove shortest matching prefix pattern
#  ${parameter##word}     ==> Remove longest  matching prefix pattern
versionID="26.07.25"
Self=$( realpath ${0} )
echo "${Self##*/} version ${versionID}"

# Would like a way to automate the contends of the files to check, but for now ...
# Specify path names relative to the current working directory, which is likely different then the location of this script
#
# See Positional Parameters section of Bash man page for "$@"
# behavior (https://linux.die.net/man/1/bash)
if (( $# > 0 )); then
  fileList=("$@")
else
  echo -e "Nothing to do.  Usage:\n  ${Self##*/} filename [filename ...]"
  exit 1
fi


start='^\s*\/{5,}\s*TO-DO\s*\([0-9]+\)\s*\/{5,}\s*$'             # regular expressions identifying the start and end
end='^\s*\/{5,}\s*END-TO-DO\s*\([0-9]+\)\s*\/{5,}\s*$'           # of a TO-DO section students are to complete


for file in "${fileList[@]}"; do
  if [[ -f "${file}" ]]; then
    echo -e "\n\n******* Checking formatting for \"${file}\" *******"

    if grep -qE "${start}" "${file}"; then
      echo -e "+++++++ Found TO-DO markers in \"${file}\". Checking formatting for the TO-DO sections only.\n"
      diff -U0  <(sed -n -E "/${start}/,/${end}/p" "${file}")   <(clang-format -style=file  "${file}" | sed -n -E "/${start}/,/${end}/p")
      status=$?
    else
      echo -e "+++++++ No TO-DO markers found in \"${file}\". Checking formatting for the entire file.\n"
      diff -U0  "${file}"  <(clang-format -style=file  "${file}")
      status=$?
    fi

    if [[ $status -eq 0 ]]; then
      echo -e "\n+++++++ Format check for \"${file}\" is complete - no changes needed.\n"
    else
      echo -e "+++++++ Format check for \"${file}\" is complete - changes needed.\n"
    fi
  else
    echo "File \"${file}\" does not exist. Skipping."
  fi
done

















####################################################################################################################################
## (C) Copyright 2026 by Thomas Bettens. All Rights Reserved.
##
## DISCLAIMER: The participating authors at California State University's Computer Science Department have used their best efforts
## in preparing this code. These efforts include the development, research, and testing of the theories and programs to determine
## their effectiveness. The authors make no warranty of any kind, expressed or implied, with regard to these programs or to the
## documentation contained within. The authors shall not be liable in any event for incidental or consequential damages in
## connection with, or arising out of, the furnishing, performance, or use of these libraries and programs.  Distribution without
## written consent from the authors is prohibited.
####################################################################################################################################

###################################################
## Last modified:  18-JUL-2026
## Last Verified:  18-JUL-2026
###################################################
