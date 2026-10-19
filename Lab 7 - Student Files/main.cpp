/*******************************************************************************
** CPSC 120L:  Lab 7
*******************************************************************************/
///////////////////////// TO-DO (1) //////////////////////////////
  ///  Import required dependencies, such as the standard library, Lab7 Functions modules, and any other libraries used

/////////////////////// END-TO-DO (1) ////////////////////////////










// This program asks an operator for when (day, hour, minute) and where (street name) they'd like to park and then displays whether
// parking is allowed or disallowed for that combination of items.  The program returns the following exit statuses
//   o) 101 - indicates the day was not recognized
//   o) 102 - indicates the hour was not recognized or not within the 24 hour clock range
//   o) 103 - indicates the minute was not recognized or not within the 60 minutes per hour range
//   o)   1 - indicates there is no information about the street entered
//   o)   0 - the program completed successfully
//
// Programming note:  The content of what would normally be in function main(...) has been moved here strictly for unit testing
// purposes.
int main_helper()
{
  ///////////////////////// TO-DO (2) //////////////////////////////
    /// Prompt the operator for when and where they wish to park. Call your prompt function four times, once for each piece of
    /// information needed (street, day, hour, minute), and save the returned value in appropriately typed variables.  For
    /// example, streets and days should be stored in string variables, while hours and minutes should be stored in unsigned
    /// integer variables.
    /// Remember from Lab5, to prompt for a string:  variable = MyLibrary::prompt<string>("message")
    ///                     to prompt for a double:  variable = MyLibrary::prompt<double>("message")
    ///                     and so on ...
    ///
    ///
    ///
    ///
    /// Get the day...
    /// When prompting for the day, make sure the operator knows days of the week must start with a capital letter, be fully spelled
    /// out, and entered on its own line.  But advanced users familiar with your parking app know an undocumented shortcut that
    /// allows them to enter just a single letter in upper or lower case and you will convert that to a properly formed day for
    /// them.  After converting shortcuts to long names, validate the response before moving on to the next step. If the day is
    /// invalid, print an error message and exit the program with the exit status described above.  The error message shall look
    /// like this example:
    ///
    ///       It appears you entered the invalid day name "Today".
    ///       Days of the week must:
    ///          a) start with a capital letter,
    ///          b) be fully spelled out, and
    ///          c) be entered on its own line.
    ///       Please make corrections and try your query again.
    ///
    /// where Today is replaced by whatever the operator entered as their day name
    ///
    /// Hint:
    ///   o) Write an if-elseif chain that checks the operator's response for the shortcut and save the long version in your
    ///      variable.  Here are the shortcuts:
    ///           U|u -> Sunday
    ///           M|m -> Monday
    ///           T|t -> Tuesday
    ///           W|w -> Wednesday
    ///           R|r -> Thursday
    ///           F|f -> Friday
    ///           S|s -> Saturday
    ///   o) Call Lab7's function isValidDay(...) passing in the operator's potentially converted response to perform the validation
    ///   o) A compound Boolean expression with multiple operators may be needed
    ///   o) The :? format specifier can be used to put quotes around strings

  /////////////////////// END-TO-DO (2) ////////////////////////////





  ///////////////////////// TO-DO (3) //////////////////////////////
    /// Get the hour...
    /// When prompting for the hour, make sure the operator knows to specify the hour using a 24 hour clock from zero to 23.  For
    /// example she should enter a 7 to mean 7 AM and 19 (7 + 12) to mean 7 PM.  Validate the response before moving on to the next
    /// step. If the hour is invalid, print an error message and exit the program with the exit status described above. The error
    /// message shall look like this example:
    ///
    ///       It appears you entered the invalid hour "24".
    ///       Hours range from 0..23
    ///       Please make corrections and try your query again.
    ///
    /// where 24 is replaced by whatever the operator entered as their hour
    ///
    /// Hint:
    ///   o) Call Lab7's function isValidHour(...) passing in the operator's response to perform the validation
    ///   o) There is no format specifier to put quotes around integers, so you need to put the quotes around the hour yourself
    ///      using the escape sequence \".  For example, to put a quote in a string literal you would write
    ///          "invalid quantity \"36\" detected"
    ///   o) See https://en.cppreference.com/cpp/language/escape

  /////////////////////// END-TO-DO (3) ////////////////////////////





  ///////////////////////// TO-DO (4) //////////////////////////////
    /// Get the minute...
    /// When prompting for the minute, she should enter a number from zero through 59.  Validate the response before moving on to
    /// the next step. If the minute is invalid, print an error message and exit the program with the exit status described above.
    /// The error message shall look like this example:
    ///
    ///       It appears you entered the invalid minute "60".
    ///       Minutes range from 0..59
    ///       Please make corrections and try your query again.
    ///
    /// where 60 is replaced by whatever the operator entered as their minute
    ///
    /// Hint:
    ///   o) Call Lab7's function isValidMinute(...) passing in the operator's response to perform the validation
    ///   o) There is no format specifier to put quotes around integers, so you need to put the quotes around the hour yourself
    ///      using the escape sequence \".  For example, to put a quote in a string literal you would write
    ///          "invalid quantity \"36\" detected"
    ///   o) See https://en.cppreference.com/cpp/language/escape

  /////////////////////// END-TO-DO (4) ////////////////////////////





  ///////////////////////// TO-DO (5) //////////////////////////////
    /// Get the street and process the query...
    /// This one is a little different because we want to both validate the operator's street response and, for valid responses,
    /// process the query.
    ///
    /// Start by defining an empty string variable that will eventually hold the parking status (allowed or not allowed). Then,
    /// define another string variable for the street and initialize it to the value returned from your prompt function.  When
    /// prompting for the street, make sure the operator knows to enter the street name, which may have spaces, in all lower case
    /// and on its own line.
    ///
    ///
    /// Next, write an if-elseif-else chain that checks the operator's response against the known list of streets (Ash, Beech,
    /// Cedar, and Date). If the response matches the first known street, then for that street set the parking status variable to
    /// the value returned from the corresponding canParkOn* function (canParkOnAsh(...) if trying to park on Ash street,
    /// canParkOnBeech(...) if trying to park on Beech street, and so on).  If the response didn't match the first known street,
    /// check the second known street, and then the third, and so on.
    ///
    /// If no match is found after checking the operator's response against all the known street names, print an error message and
    /// exit the program with the exit status described above.  The error message shall look like this example:
    ///
    ///       There is no information about a street named "Elm".  Perhaps you want to try again?
    ///
    /// where Elm is replaced by whatever the operator entered as their street name
    ///
    /// Hint:
    ///   o) Structurally, your code might look something like
    ///         if street is equal to "avenue1"  then parking status is set to the returned value from canParkOnAvenue1( when )
    ///         otherwise, if street is equal to "avenue2"  then parking status is set to the returned value from canParkOnAvenue2( when )
    ///         otherwise, if street is equal to "avenue3"  then parking status is set to the returned value from canParkOnAvenue3( when )
    ///         otherwise, print an error message indicating no information is available
    ///   o) A compound Boolean expression with multiple operators may be needed
    ///   o) The :? format specifier can be used to put quotes around strings

  /////////////////////// END-TO-DO (5) ////////////////////////////





  ///////////////////////// TO-DO (6) //////////////////////////////
    /// And finally, print your findings.  The output message shall look like this example:
    ///
    ///    Parking on ash street is allowed on Monday at 7:00
    ///
    /// where ash     is replaced by the name of the street the operator specified;
    ///       allowed is replaced by the parking status variable as set by calling the corresponding canParkOn*(...) function;
    ///       Monday  is replaced by the day of the week the operator specified, with shortcuts expanded;
    ///       7       is replaced by the hour the operator specified; and
    ///       00      is replaced by the minute the operator specified formatted with exactly two digits
    ///
    /// Hint:  The format specifier :02 can be used to print an integer with two digits, even if the first digit is zero

  /////////////////////// END-TO-DO (6) ////////////////////////////

  return 0;
}










// Programming note:  While an object of type int is returned from function main(...), the Linux shell uses only the least
// significant byte causing the effective type returned to be an unsigned 8-bit integer. (i.e., unsigned char or std::uint8_t). If
// main(...) returned 256 for example, the shell sees this as if main(...) returned 0.  A returned value of -1 would be the same as
// returning 255.
// See https://www.man7.org/linux/man-pages/man3/exit.3@@man-pages.html and
//     https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Values-from-main.html
// By the way, this is different for Windows.  Windows uses the least significant eight bytes (a DWORD)
int main()
{
  return main_helper();
}















/***********************************************************************************************************************************
** Acknowledgements:  Special thanks goes to the Computer Science staff at CSUF, especially Michael Shafae, Keven Wortman, and all the
** other prior CPSC 120 instructors who this work is based on.
***********************************************************************************************************************************/

/***********************************************************************************************************************************
** (C) Copyright 2026 by Thomas Bettens. All Rights Reserved.
**
** DISCLAIMER: The participating authors at California State University's Computer Science Department have used their best efforts
** in preparing this code. These efforts include the development, research, and testing of the theories and programs to determine
** their effectiveness. The authors make no warranty of any kind, expressed or implied, with regard to these programs or to the
** documentation contained within. The authors shall not be liable in any event for incidental or consequential damages in
** connection with, or arising out of, the furnishing, performance, or use of these libraries and programs.  Distribution without
** written consent from the authors is prohibited.
***********************************************************************************************************************************/

/**************************************************
** Last modified:  18-JUL-2026
** Last Verified:  18-JUL-2026
** Verified with:  MS Visual Studio 2026 Version 18.7.2,  Compiler Version 19.51.36248 (/std:c++latest)
**                 GCC version 16.1.0 (-std=c++23 )
**                 Clang version 22.1.8 (-std=c++23 -stdlib=libc++)
***************************************************/
