/***********************************************************************************************************************************
**  Module Regression.Lab7Tests
**
***********************************************************************************************************************************/
module;
  #include "extern_declarations.hpp"


export module Regression.Lab7Tests;
import std;

import Lab7.Functions;

import Regression.CheckResults;
import Utilities.UsurpIO;


export namespace Regression
{
  class Lab7Tests
  {
    public:
      Lab7Tests();

    private:
      std::vector<std::string> validDays{ "Sunday",
                                          "Monday",
                                          "Tuesday",
                                          "Wednesday",
                                          "Thursday",
                                          "Friday",
                                          "Saturday" };

      std::vector<std::string> validShortcuts{ "U", "u",
                                               "M", "m",
                                               "T", "t",
                                               "W", "w",
                                               "R", "r",
                                               "F", "f",
                                               "S", "s" };

      std::vector<std::string> validStreets{"ash",
                                            "beech",
                                            "cedar",
                                            "date" };



      void isValidDay_tests    ();
      void isValidHour_tests   ();
      void isValidMinute_tests ();
      void canParkOnAsh_tests  ();
      void canParkOnBeech_tests();
      void canParkOnCedar_tests();
      void canParkOnDate_tests ();
      void main_helper_tests   ();



      static std::string toUpper( std::string str )
      {
        static std::locale locale;
        for( auto & c : str ) c = std::toupper( c, locale );
        return str;
      }

      static std::string toLower( std::string str )
      {
        static std::locale locale;
        for( auto & c : str ) c = std::tolower( c, locale );
        return str;
      }

      template<class... Vecs>
      std::vector<std::string> concat( std::vector<std::string> v1, const Vecs &... vs )
        requires(( std::same_as<Vecs, std::vector<std::string>> && ... ))
      {
        ( v1.append_range( vs ), ... );
        return v1;        // returns the grown vector
      }

      // Tre if lower <= x < upper)
      bool static isBetween( unsigned x, unsigned lower, unsigned upper )
      { return  lower <= x  &&  x < upper; }

      Regression::CheckResults affirm;
  };
}















/***********************************************************************************************************************************
**  Module Regression.Lab7Tests Implementation
**  Private implementation: Not exported and not reachable
**
***********************************************************************************************************************************/
// module : private;    GCC doesn't yet (as of version 16.1.0) support private fragments.
//                      The workaround is to just don't create a private fragment
//                      The better approach is to create a separate module implementation unit (.cpp) file, but I didn't want the overhead
// Note:  For GCC all the stuff below is reachable and not encapsulated as a :private fragment
// module : private;




namespace Regression
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Namespace scoped object gets constructed BEFORE main(...) begins to execute.  It's this construction process that launches all
  // the regress tests.
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  static Lab7Tests run_Lab7_tests;







  void Lab7Tests::isValidDay_tests()
  {
    Utilities::ProvideStdInput _{ "No input data expected\n" };
    std::string                stdOutput;

    for( const auto & validDay : validDays )
    {
      bool result = ( Utilities::CaptureStdOutput{ stdOutput },    Lab7::isValidDay( validDay ) );

      affirm.is_true( std::format( "{:>11?} is a valid day name", validDay ), result );
      if( stdOutput.size() > 0 ) affirm.is_equal( "Function isValidDay(...) - nothing written to standard output or standard error", "", stdOutput );
    }

    for( const auto & invalidDay : concat( validStreets, validDays, validShortcuts ) )
    {
      auto lowerInvalidDay = toLower( invalidDay );
      bool result          = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::isValidDay( lowerInvalidDay ) );

      affirm.is_true( std::format( "{:>11?} is an invalid day name", lowerInvalidDay ), !result );
      if( stdOutput.size() > 0 ) affirm.is_equal( "Function isValidDay(...) - nothing written to standard output or standard error", "", stdOutput );

      auto upperInvalidDay = toUpper( invalidDay );
      result               = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::isValidDay( upperInvalidDay ) );

      affirm.is_true( std::format( "{:>11?} is an invalid day name", upperInvalidDay ), !result );
      if( stdOutput.size() > 0 ) affirm.is_equal( "Function isValidDay(...) - nothing written to standard output or standard error", "", stdOutput );
    }
  }







  void Lab7Tests::isValidHour_tests()
  {
    Utilities::ProvideStdInput _{ "No input data expected\n" };
    std::string                stdOutput;

    for( int hr : { 0, 1, 22, 23 } )
    {
      bool result = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::isValidHour( hr ) );

      affirm.is_true( std::format( "{} is a valid hour", hr ), result );
      if( stdOutput.size() > 0 ) affirm.is_equal( "Function isValidHour(...) - nothing written to standard output or standard error", "", stdOutput );
    }

    for( int hr : { -2, -1, 24, 25 } )
    {
      bool result = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::isValidHour( hr ) );

      affirm.is_true( std::format( "{} is an invalid hour", hr ), !result );
      if( stdOutput.size() > 0 ) affirm.is_equal( "Function isValidHour(...) - nothing written to standard output or standard error", "", stdOutput );
    }
  }







  void Lab7Tests::isValidMinute_tests()
  {
    Utilities::ProvideStdInput _{ "No input data expected\n" };
    std::string                stdOutput;

    for( int minute : { 0, 1, 58, 59 } )
    {
      bool result = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::isValidMinute( minute ) );

      affirm.is_true( std::format( "{} is a valid minute", minute ), result );
      if( stdOutput.size() > 0 ) affirm.is_equal( "Function isValidMinute(...) - nothing written to standard output or standard error", "", stdOutput );
    }

    for( int minute : { -2, -1, 60, 61 } )
    {
      bool result = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::isValidMinute( minute ) );

      affirm.is_true( std::format( "{} is an invalid minute", minute ), !result );
      if( stdOutput.size() > 0 ) affirm.is_equal( "Function isValidMinute(...) - nothing written to standard output or standard error", "", stdOutput );
    }
  }







  void Lab7Tests::canParkOnAsh_tests()
  {
    Utilities::ProvideStdInput _{ "No input data expected\n" };
    std::string                stdOutput;

    std::string result = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::canParkOnAsh( validDays[0], 0 ) );
    if( stdOutput.size() > 0 ) affirm.is_equal( "Function canParkOnAsh(...) - nothing written to standard output or standard error", "", stdOutput );

    bool allPassed = true;
    for( const auto & day : validDays )  for( unsigned hr = 0; hr < 24; ++hr )
    {
      std::string actual   = Lab7::canParkOnAsh( day, hr );
      std::string expected = ( day == "Wednesday"  &&  isBetween( hr, 10, 12 ) ) ? "not allowed" : "allowed";

      // Let's throttle the number of shown tests, there are just too many to show them all
      if( expected != actual )
      {
        affirm.is_equal( std::format( "Parking on Ash {} during hour {}", day, hr ), expected, actual );
        allPassed = false;
      }
    }

    affirm.is_true( "Parking on Ash street", allPassed );
  }







  void Lab7Tests::canParkOnBeech_tests()
  {
    Utilities::ProvideStdInput _{ "No input data expected\n" };
    std::string                stdOutput;

    std::string result = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::canParkOnBeech( validDays[0], 0 ) );
    if( stdOutput.size() > 0 ) affirm.is_equal( "Function canParkOnBeech(...) - nothing written to standard output or standard error", "", stdOutput );

    bool allPassed = true;
    for( const auto & day : validDays )  for( unsigned hr = 0; hr < 24; ++hr )
    {
      std::string actual   = Lab7::canParkOnBeech( day, hr );
      std::string expected = ( day == "Friday"  &&  isBetween( hr, 8, 12 ) ) ? "not allowed" : "allowed";

      // Let's throttle the number of shown tests, there are just too many to show them all
      if( expected != actual )
      {
        affirm.is_equal( std::format( "Parking on Beech {} during hour {}", day, hr ), expected, actual );
        allPassed = false;
      }
    }

    affirm.is_true( "Parking on Beech street", allPassed );
  }







  void Lab7Tests::canParkOnCedar_tests()
  {
    Utilities::ProvideStdInput _{ "No input data expected\n" };
    std::string                stdOutput;

    std::string result = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::canParkOnCedar( validDays[0], 0 ) );
    if( stdOutput.size() > 0 ) affirm.is_equal( "Function canParkOnCedar(...) - nothing written to standard output or standard error", "", stdOutput );

    bool allPassed = true;
    for( const auto & day : validDays )  for( unsigned hr = 0; hr < 24; ++hr )
    {
      std::string actual   = Lab7::canParkOnCedar( day, hr );
      std::string expected = ( isBetween( hr, 0, 7 )  ||  isBetween( hr, 19, 24 )  ||  ( day == "Tuesday" && isBetween( hr, 8, 10 ) ) )
                             ? "not allowed"
                             : "allowed";

      // Let's throttle the number of shown tests, there are just too many to show them all
      if( expected != actual )
      {
        affirm.is_equal( std::format( "Parking on Cedar {} during hour {}", day, hr ), expected, actual );
        allPassed = false;
      }
    }

    affirm.is_true( "Parking on Cedar street", allPassed );
  }







  void Lab7Tests::canParkOnDate_tests()
  {
    Utilities::ProvideStdInput _{ "No input data expected\n" };
    std::string                stdOutput;

    std::string result = ( Utilities::CaptureStdOutput{ stdOutput }, Lab7::canParkOnDate( validDays[0], 0, 0 ) );
    if( stdOutput.size() > 0 ) affirm.is_equal( "Function canParkOnDate(...) - nothing written to standard output or standard error", "", stdOutput );

    bool allPassed = true;
    for( const auto & day : validDays )  for( unsigned hr = 0; hr < 24; ++hr )  for( unsigned min = 0; min < 60; ++min)
    {
      std::string actual   = Lab7::canParkOnDate( day, hr, min );
      std::string expected = ( !isBetween( hr*100+min, 6'30, 16'00 )  ||  day == "Saturday"  ||  day == "Sunday" )
                             ? "allowed"
                             : "not allowed";

      // Let's throttle the number of shown tests, there are just too many to show them all
      if( expected != actual )
      {
        affirm.is_equal( std::format( "Parking on Date {} during hour {} during minute {}", day, hr, min ), expected, actual );
        allPassed = false;
      }
    }

    affirm.is_true( "Parking on Date street", allPassed );
  }







  void Lab7Tests::main_helper_tests()
  {
    auto        const regex_syntax_options = std::regex::ECMAScript | std::regex::icase /*| std::regex::multiline*/;
    std::smatch       m;
    std::string       stdOutput;
    std::string const preamble = R"(^[\S\s]*?\b)";



    // Process an invalid day
    //
    const std::string day_error_message_pattern{ R"(It\s+appears\s+you\s+entered\s+(?:the|an)\s+invalid\s+day\s+name\s+"day of the week"\s*\.\s*\n\s*)"
                                                 R"(Days\s+of\s+the\s+week\s+must\s*:\s*\n\s*)"
                                                 R"(a\s*\)\s+start\s+with\s+a\s+capital\s+letter\s*,\s*\n\s*)"
                                                 R"(b\s*\)\s+be\s+fully\s+spelled\s+out\s*,\s+and\s*\n\s*)"
                                                 R"(c\s*\)\s+be\s+entered\s+on\s+its\s+own\s+line\s*\.\s*\n\s*)"
                                                 R"(Please\s+make\s+corrections\s+and\s+try\s+your\s+query\s+again\s*\.\s*\n)" };

    int exit_status = ( Utilities::ProvideStdInput{ "day of the week\n" },        // statement scoped objects used for temporary redirection
                        Utilities::CaptureStdOutput{ stdOutput },
                        main_helper() );


    affirm.is_equal( "Invalid day correctly detected and exited with appropriate exit status", 101, exit_status );

    std::regex_search( stdOutput, m, std::regex( preamble + "(" + day_error_message_pattern + ")", regex_syntax_options ) );

    if( m.size() > 1  &&  m[1].matched )   affirm.is_equal( "Correct error message emitted for an invalid day", m[1].str(), m[1].str() );
    else                                   affirm.is_equal( "Correct error message emitted for an invalid day", day_error_message_pattern, stdOutput );




    std::println( affirm.testResults );




    // Process valid days and invalid hour
    //
    const std::string hour_error_message_pattern{ R"(It\s+appears\s+you\s+entered\s+(?:the|an)\s+invalid\s+hour\s+"25"\s*\.\s*\n\s*)"
                                                  R"(Hours\s+range\s+from\s+0\s*\.\.\s*23\s*\n\s*)"
                                                  R"(Please\s+make\s+corrections\s+and\s+try\s+your\s+query\s+again\s*\.\s*\n)" };


    unsigned display_test_results = 0b11;
    for( const auto & day : concat( validDays, validShortcuts ) )         // The important thing here are the shortcuts - they've not been tested elsewhere
    {
      exit_status = ( Utilities::ProvideStdInput{ day + "\n 25\n" },        // statement scoped objects used for temporary redirection
                      Utilities::CaptureStdOutput{ stdOutput },
                      main_helper() );

      if( exit_status == 102 )                                            // Always display failures, but display passed tests just once
      {
        if( ( display_test_results & 0b10 ) != 0 )
        {
          affirm.is_equal( "Invalid hour correctly detected and exited with appropriate exit status", 102, exit_status );
          display_test_results &= ~0b10;
        }
      }
      else affirm.is_equal( std::format( "Invalid hour correctly detected and exited with appropriate exit status: {:?}, 25", day), 102, exit_status );



      std::regex_search( stdOutput, m, std::regex( "(?!" + preamble + day_error_message_pattern + ")" +
                                                   preamble + "(" + hour_error_message_pattern  + ")",
                                                   regex_syntax_options ) );

      if( m.size() > 1 && m[1].matched )                                  // Always display failures, but display passed tests just once
      {
        if( ( display_test_results & 0b01 ) != 0 )
        {
          affirm.is_equal( "Correct error message emitted for an invalid hour", m[1].str(), m[1].str() );
          display_test_results &= ~0b01;
        }
      }
      else affirm.is_equal( "Correct error message emitted for an invalid hour", hour_error_message_pattern, stdOutput );
    }




    std::println( affirm.testResults );




    // Process valid days, hours, and invalid minute
    //
    const std::string minute_error_message_pattern{ R"(It\s+appears\s+you\s+entered\s+(?:the|an)\s+invalid\s+minute\s+"60"\s*\.\s*\n\s*)"
                                                    R"(Minutes\s+range\s+from\s+0\s*\.\.\s*59\s*\n\s*)"
                                                    R"(Please\s+make\s+corrections\s+and\s+try\s+your\s+query\s+again\s*\.\s*\n)" };


    exit_status = ( Utilities::ProvideStdInput{ "R\n 17\n 60\n" },            // statement scoped objects used for temporary redirection
                    Utilities::CaptureStdOutput{ stdOutput },
                    main_helper() );

    affirm.is_equal( "Invalid minute correctly detected and exited with appropriate exit status", 103, exit_status );

    std::regex_search( stdOutput, m, std::regex( "(?!" + preamble + day_error_message_pattern  + ")" +
                                                 "(?!" + preamble + hour_error_message_pattern + ")" +
                                                 preamble + "(" + minute_error_message_pattern + ")",
                                                 regex_syntax_options ) );

    if( m.size() > 1 && m[1].matched )   affirm.is_equal( "Correct error message emitted for an invalid minute", m[1].str(), m[1].str() );
    else                                 affirm.is_equal( "Correct error message emitted for an invalid minute", minute_error_message_pattern, stdOutput );




    std::println( affirm.testResults );




    // Process valid days, hours, minutes, and invalid street
    //
    const std::string street_error_message_pattern{ R"(There\s+is\s+no\s+information\s+about\s+a\s+street\s+named\s+"Nutwood Ave"\s*\.\s+)"
                                                    R"(Perhaps\s+you\s+want\s+to\s+try\s+again\s*\?\s*\n)" };


    exit_status = ( Utilities::ProvideStdInput{ "R\n 17\n 15\nNutwood Ave\n" },            // statement scoped objects used for temporary redirection
                    Utilities::CaptureStdOutput{ stdOutput },
                    main_helper() );

    affirm.is_equal( "Invalid street correctly detected and exited with appropriate exit status", 1, exit_status );

    std::regex_search( stdOutput, m, std::regex( "(?!" + preamble + day_error_message_pattern    + ")"  +
                                                 "(?!" + preamble + hour_error_message_pattern   + ")"  +
                                                 "(?!" + preamble + minute_error_message_pattern + ")"  +
                                                 preamble + "(" + street_error_message_pattern   + ")",
                                                 regex_syntax_options ) );

    if( m.size() > 1 && m[1].matched )   affirm.is_equal( "Correct error message emitted for an invalid street name", m[1].str(), m[1].str() );
    else                                 affirm.is_equal( "Correct error message emitted for an invalid street name", street_error_message_pattern, stdOutput );




    std::println( affirm.testResults );




    // Process valid days, hours, minutes, and street
    //
    exit_status = ( Utilities::ProvideStdInput{ "R\n 17\n 30\ndate\n" },        // statement scoped objects used for temporary redirection
                    Utilities::CaptureStdOutput{ stdOutput },
                    main_helper() );

    affirm.is_equal( "Successful program termination correctly detected and exited with appropriate exit status when input is valid", 0, exit_status );
  }







  Lab7Tests::Lab7Tests()
  {
    // affirm.policy = Regression::CheckResults::ReportingPolicy::ALL;
    // affirm.name_width = 40;
    constexpr auto TEST_NAME = "Lab 7 Regression Test";
    try
    {
      std::println( std::clog, "{}", TEST_NAME );

      std::println( std::clog, "{}:  Is Valid Day", TEST_NAME );
      isValidDay_tests();

      std::println( std::clog, "\n\n{}:  Is Valid Hour", TEST_NAME );
      isValidHour_tests();

      std::println( std::clog, "\n\n{}:  Is Valid Minute", TEST_NAME );
      isValidMinute_tests();

      std::println( std::clog, "\n\n{}:  Can Park On Ash Street", TEST_NAME );
      canParkOnAsh_tests();

      std::println( std::clog, "\n\n{}:  Can Park On Beech Street", TEST_NAME );
      canParkOnBeech_tests();

      std::println( std::clog, "\n\n{}:  Can Park On Cedar Street", TEST_NAME );
      canParkOnCedar_tests();

      std::println( std::clog, "\n\n{}:  Can Park On Date Street", TEST_NAME );
      canParkOnDate_tests();

      std::println( std::clog, "\n\n{}:  Program Orchestration (main and helpers)", TEST_NAME );
      main_helper_tests();

      std::println( std::clog, "\n\n{} {}\n", TEST_NAME, affirm );
    }


    catch( const std::exception & ex )
    {
      std::println( std::clog, "FAILURE:  Regression test for {:?} failed with an unhandled exception.\n\n\n"
                             "{}",
                             TEST_NAME,  ex.what() );
      std::clog.flush();
    }
  }
} // namespace Regression















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
