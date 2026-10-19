module;                                                                         // Global fragment (not part of the module)
  // Empty




/***********************************************************************************************************************************
**  Module Regression.CheckResults Interface
**
***********************************************************************************************************************************/
export module Regression.CheckResults;                                     // Primary Module Interface Definition
import std;


export namespace Regression
{
  struct CheckResults
  {
    enum class ReportingPolicy{ FAILED_ONLY, BRIEF, ALL };
    CheckResults( std::ostream & stream = std::clog ) : testResults( stream )
    { testResults << std::unitbuf; } // flush the buffer after each insertion - sometimes having that little bit extra info helps if the program crashes

                                     bool is_true                    ( const std::string & nameOfTest,                     bool      actual );
    template<typename T, typename U> bool is_equal                   ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_not_equal               ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_less_than               ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_less_than_or_equal_to   ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_greater_than            ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_greater_than_or_equal_to( const std::string & nameOfTest, const T & expected, const U & actual );

    template<typename T, typename U >
    constexpr bool equal( T const & lhs,  U const & rhs) noexcept
    {
      if constexpr( std::is_floating_point_v<std::common_type_t<T, U>> ) return std::abs( lhs - rhs ) < EPSILON;
      else                                                               return lhs == rhs;
    }

    unsigned        testCount   = 0;
    unsigned        testsPassed = 0;
    unsigned        name_width  = 55;
    double          EPSILON     = 1e-9;
    ReportingPolicy policy      = ReportingPolicy::BRIEF;
    std::ostream &  testResults;
  };  // export struct CheckResults

  std::ostream & operator<<( std::ostream & stream, const CheckResults & results );
}  // export namespace Regression















// Not exported but reachable

// Specialize the formatter to accept and process CSUF::CPSC131::Student typed objects
template<>
struct std::formatter<Regression::CheckResults> : std::formatter<std::string>
{
  // No special parsing options, for now.  So let's inherit and delegate to the formatter<string>::parse function Someday, we might
  // want to allow the client to specify, for example, '[' instead of '{', or the delimiter between fields.
  //
  // constexpr auto parse( auto & ctx )


  auto format( const Regression::CheckResults & results, auto & ctx ) const
  {
    const std::string str = std::format( "Summary: {} of {} ({:.5g}%) tests passed",
                                          results.testsPassed,
                                          results.testCount,
                                          (results.testCount != 0) ? (results.testsPassed * 100.0 / results.testCount) : 100.0 );
    return std::formatter<std::string>::format( str, ctx );


    // Alternately, if you don't want to process like a string using the string format descriptors, then
    //
    // return std::format_to( ctx.out(), "Summary: {} of {} ({:.5g}%) tests passed", results.testsPassed, results.testCount, results.testsPassed * 100.0 / results.testCount );
  }
};






namespace Regression
{
  /***********************************************************************************************************************************
  ** Definitions
  ***********************************************************************************************************************************/
  inline std::ostream & operator<<( std::ostream & stream, const CheckResults & results )
  {
    return stream << std::format( "{}", results );
  }









  inline bool CheckResults::is_true( const std::string & nameOfTest, bool actual )
  {
    return is_equal( nameOfTest, true, actual );
  }









  template<typename T, typename U>
  inline bool CheckResults::is_equal( const std::string & nameOfTest, const T & expected, const U & actual )
  {
    ++testCount;

    if( ! equal(expected, actual) )
    {
      std::print( testResults, " *[FAILED] {:{}}: the expected value is not equal to the actual value, but should be\n", nameOfTest, name_width );
      if constexpr( std::is_pointer<T>{} || std::is_pointer<U>{} )   std::print( testResults, "    EXP: {{{:014p}}}\n"
                                                                                              "    ACT: {{{:014p}}}\n",
                                                                                              static_cast<void*>(expected), static_cast<void*>(actual) );
      else                                                           std::print( testResults, "    EXP: {{{}}}\n"
                                                                                              "    ACT: {{{}}}\n",
                                                                                              expected, actual );
      return false;
    }

    ++testsPassed;

    if( policy >= ReportingPolicy::BRIEF )
    {
      std::print( testResults, "  [PASSED] {:{}}", nameOfTest, name_width );

      if( policy > ReportingPolicy::BRIEF )
      {
        if constexpr( std::is_pointer<T>{} || std::is_pointer<U>{} )  std::print( testResults, ": as expected, the expected and actual values are equal:  {{{:014p}}}", static_cast<void*>(actual) );
        else                                                          std::print( testResults, ": as expected, the expected and actual values are equal:  {{{}}}",                         actual  );
     }
      std::println( testResults );
    }

    return true;
  }









  template<typename T, typename U>
  inline bool CheckResults::is_not_equal( const std::string & nameOfTest, const T & expected, const U & actual )
  {
    ++testCount;

    if( equal(expected, actual) )
    {
      std::print( testResults, " *[FAILED] {:{}}: the expected value is equal to the actual value, but shouldn't be:  ", nameOfTest, name_width );
      if constexpr( std::is_pointer<T>{} || std::is_pointer<U>{} )   std::print( testResults, "{{{:014p}}}\n", static_cast<void*>(actual) );
      else                                                           std::print( testResults, "{{{}}}\n",                         actual  );

      return false;
    }

    ++testsPassed;

    if( policy >= ReportingPolicy::BRIEF )
    {
      std::print( testResults, "  [PASSED] {:{}}", nameOfTest, name_width );
      if( policy > ReportingPolicy::BRIEF )
      {
        std::print( testResults, ": as expected, the expected and actual values are not equal\n" );
        if constexpr( std::is_pointer<T>{} || std::is_pointer<U>{} )  std::print( testResults, "    EXP: {{{:014p}\n"
                                                                                               "    ACT: {{{:014p}}}",
                                                                                               static_cast<void*>(expected), static_cast<void*>(actual) );

        else                                                          std::print( testResults, "    EXP: {{{}\n"
                                                                                               "    ACT: {{{}}}",
                                                                                               expected, actual );
      }
      std::println( testResults );
    }

    return true;
  }









  template<typename T, typename U>
  inline bool CheckResults::is_less_than( const std::string & nameOfTest, const T & expected, const U & actual )
  {
    ++testCount;

    if( equal(expected, actual)  ||  !(expected < actual) )       // account for "close enough" floating point numbers before check for inequality
    {
      std::print( testResults, " *[FAILED] {:{}}: the expected value is not less than the actual value, but should be\n"
                                 "    EXP: {{{}}}\n"
                                 "    ACT: {{{}}}\n",
                                 nameOfTest, name_width,
                                 expected, actual );
      return false;
    }

    ++testsPassed;
    if( policy >= ReportingPolicy::BRIEF )
    {
      std::print( testResults, "  [PASSED] {:{}}", nameOfTest, name_width );
      if( policy > ReportingPolicy::BRIEF ) std::print( testResults, ": as expected, the expected value is less than the actual value\n"
                                                                     "    EXP: {{{}}}\n"
                                                                     "    ACT: {{{}}}",
                                                                     expected, actual );
      std::println( testResults );
    }

    return true;
  }









  template<typename T, typename U>
  inline bool CheckResults::is_greater_than( const std::string & nameOfTest, const T & expected, const U & actual )
  {
    ++testCount;

    if( equal(expected, actual)  ||  !(actual < expected) )       // account for "close enough" floating point numbers before check for inequality
    {
      std::print( testResults, " *[FAILED] {:{}}: the expected value is not greater than the actual value, but should be\n"
                               "   EXP: {{{}}}\n"
                               "   ACT: {{{}}}\n",
                               nameOfTest, name_width,
                               expected, actual );
      return false;
    }

    ++testsPassed;
    if( policy >= ReportingPolicy::BRIEF )
    {
      std::print( testResults, "  [PASSED] {:{}}", nameOfTest, name_width );
      if( policy > ReportingPolicy::BRIEF ) std::print( testResults, ": as expected, the expected value is greater than the actual value\n"
                                                                     "    EXP: {{{}}}\n"
                                                                     "    ACT: {{{}}}",
                                                                     expected, actual );
      std::println( testResults );
    }

    return true;
  }
}    // namespace Regression















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
