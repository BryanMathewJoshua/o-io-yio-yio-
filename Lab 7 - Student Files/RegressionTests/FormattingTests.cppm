/***********************************************************************************************************************************
**  Source Code Formatting Tests
**
***********************************************************************************************************************************/
export module Regression.SourceCodeFormattingTests;
import std;
import Regression.CheckResults;
import Utilities.CommandRunner;

export namespace Regression
{
  class SourceCodeFormattingTests
  {
    public:
      SourceCodeFormattingTests();

    private:
      void formatting();

      Regression::CheckResults affirm;
  };
}















/***********************************************************************************************************************************
**  Module Regression.SourceCodeFormattingTests Implementation
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
  static SourceCodeFormattingTests run_source_code_formatting_tests;







  void SourceCodeFormattingTests::formatting()
  {
    using shell = Utilities::CommandRunner;
    namespace fs = std::filesystem;



    // If running in the context of the autograder, let's build the list of files to check.  Otherwise, let the list of files to
    // check default to the script
    auto is_cplusplusFile = []( const fs::path & file )
    {
      const std::array extensions = { ".hpp", ".hxx", ".h", ".inc", ".cpp", ".cxx", ".cc", ".cppm", ".ixx" };
      const auto       extension  = file.extension();

      return std::ranges::any_of( extensions, [&]( const auto & ext ) { return ext == extension; } );
    };



    auto get_file_list = [&]() -> std::vector<std::string>
    {
      // Search path to list of files to check ...
      const std::array search_paths = { "/autograder/source/AssignmentUnique",                        // Gradescope's autograder
                                        "../source/AssignmentUnique" };                               // autograder's test harness
      const std::array locations    = { "Baseline", "Expected", ".Expected" };

      fs::path basedir = ".";                                                                         // use the current directory unless you find something better
      for( const fs::path path : search_paths )  for( const fs::path loc : locations )  if( fs::exists( path / loc ) )
      {
        basedir = path;
        goto BREAK;   // want to break out of both the inner and outer loops, but the break statement only breaks out of the inner most loop
      } BREAK:


      std::vector<std::string> args;
      for( auto && location : locations )  if( fs::exists( basedir / location ) )
      {
        for( auto && entry : fs::recursive_directory_iterator( basedir / location ) )
        {
          if( !entry.is_directory() && is_cplusplusFile( entry ) )   
          {
            // Skip files in the Baseline location if there are no student modifiable sections 
            static const std::string beginToDoPattern{ R"(^\s*\/{5,}\s*TO-DO\s*\([0-9]+\)\s*\/{5,}\s*$)" };
            const auto [out, err, exit_code] = shell( "grep", std::vector<std::string>{ "-qE", beginToDoPattern, entry.path().string() } ).run();
            
            if( std::strcmp(location, "Baseline") == 0  &&  exit_code == 1) continue;  // grep returns a 1 if no lines were selected

            args.emplace_back( entry.path().lexically_relative( basedir / location ) );
          }
        }
      }

//    std::ranges::sort( args );
      std::ranges::sort( args, []( std::string_view lhs, std::string_view rhs )                       // case insensitive sort (was it worth it?)
                                 {
                                   static std::locale locale{"en_US.UTF-8"};
                                   auto lower = [&](char chr) { return std::tolower( chr, locale ); };
                                   return std::ranges::lexicographical_compare( lhs | std::views::transform( lower ),
                                                                                rhs | std::views::transform( lower ) );
                                 } );

      return args;
    };


    const std::string command = "RegressionTests/check_formatting.sh";
    const auto        args    = get_file_list();

    const auto [out, err, exit_code] = shell( command, args ).run();


    if( exit_code != 0 )  throw std::runtime_error( std::format( "*** Check Formatting command failed with exit status:  {}\n"
                                                                 "    command:    {:?}\n"
                                                                 "    arguments: {:n:?}\n"
                                                                 "    Subprocess exited with status {} and returned:\n"
                                                                 "-----------------\n"
                                                                 "{}{}"
                                                                 "-----------------\n",
                                                                 exit_code, command, args, exit_code, out, err ) );
    std::string file_name;
    std::string hunk_marker;
    std::string original_code;
    std::string corrected_code;

    std::istringstream out_stream{ out };
    for( std::string line; std::getline( out_stream, line ); )
    {
      original_code .clear();
      corrected_code.clear();

      if( line.starts_with( "******* Checking formatting for \"" ) && line.ends_with( "\" *******" ) )
      {
        auto first = line.find ( '"' );
        auto last  = line.rfind( '"' );
        file_name  = line.substr( first + 1, last - first - 1 );
      }
      else if( line.starts_with( "@@ " )  &&  line.ends_with( " @@" ) )
      {
        hunk_marker = line;
        //                                 0         1    2 3           4    5 6
        static const std::regex pattern{ R"(\s*@@\s+-(\d+)(,(\d+))?\s+\+(\d+)(,(\d+))?\s+@@)" };

        std::smatch match;
        if( std::regex_match( line, match, pattern ) )
        {
          // Make sure to query the match before changing "line"
          auto orig_start = ( match[1].matched ? std::stoi( match[1].str() ) : 1 );
          auto orig_count = ( match[3].matched ? std::stoi( match[3].str() ) : 1 );
          auto corr_start = ( match[4].matched ? std::stoi( match[4].str() ) : 1 );
          auto corr_count = ( match[6].matched ? std::stoi( match[6].str() ) : 1 );

          for( auto i = 0; i < orig_count; ++i )
          {
            std::getline( out_stream, line );
            original_code += std::format( "{:3}:{}\n", orig_start++, line.substr( 1 ) );
          }

          for( auto i = 0; i < corr_count; ++i )
          {
            std::getline( out_stream, line );
            corrected_code += std::format( "{:3}:{}\n", corr_start++, line.substr( 1 ) );
          }
        }

        affirm.is_equal( std::format( "{:?}:  {}", file_name, hunk_marker ), '\n' + corrected_code, '\n' + original_code );
      }
    }
  }







  SourceCodeFormattingTests::SourceCodeFormattingTests()
  {
    // affirm.policy = Regression::CheckResults::ReportingPolicy::ALL;
    // affirm.name_width = 40;
    constexpr auto TEST_NAME = "Source Code Formatting Regression Test";
    try
    {
      std::println( std::clog, "{}", TEST_NAME );

      std::println( std::clog, "{}:  Formatting", TEST_NAME );
      formatting();

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
