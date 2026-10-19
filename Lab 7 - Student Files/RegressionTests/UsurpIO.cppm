/***********************************************************************************************************************************
** RAII Classes that temporarily captures standard output as a string and provides standard input as a string
***********************************************************************************************************************************/
module;
#include <cstdio>   // FILE (macro)


export module Utilities.UsurpIO;
import std;


export namespace Utilities
{
  /*********************************************************************************************************************************
  ** A RAII Class that temporarily captures standard output and returns the contents as a string
  **
  ** Usage example:
  **   CaptureStdOutput cap;
  **   auto returned_value = your_function_under_test();
  **   std::string out = cap.all();
  **
  ** or
  **   std::string cout_text   = cap.get_cout();
  **   std::string stdout_text = cap.get_stdout();
  **   std::string cerr_text   = cap.get_cerr();
  **   std::string stderr_text = cap.get_stderr();
  **
  ** or
  **   std::string actual_output;
  **   auto        returned_value = ( CaptureStdOutput{ actual_output }, your_function_under_test() );  // statement scoped object used for temporary redirection
  *********************************************************************************************************************************/
  class CaptureStdOutput
  {
    public:
      CaptureStdOutput();
      explicit CaptureStdOutput( std::string & results );
     ~CaptureStdOutput() noexcept;

      CaptureStdOutput            ( CaptureStdOutput const  & )          = delete;
      CaptureStdOutput            ( CaptureStdOutput       && ) noexcept = delete;
      CaptureStdOutput & operator=( CaptureStdOutput const  & )          = delete;
      CaptureStdOutput & operator=( CaptureStdOutput       && ) noexcept = delete;


      std::string get_stdout() const;
      std::string get_cout  () const;
      std::string get_output() const { return get_stdout() + get_cout(); }

      std::string get_stderr() const;
      std::string get_cerr  () const;
      std::string get_clog  () const;
      std::string get_error () const { return get_stderr() + get_cerr() + get_clog(); }

      std::string get_all() const { return get_output() + get_error(); }


    private:
      // returned value
      std::string * _results = nullptr;

      // C++ stream buffers
      std::ostringstream _cout_ss;
      std::ostringstream _cerr_ss;
      std::ostringstream _clog_ss;
      std::streambuf *   _cout_old = nullptr;
      std::streambuf *   _cerr_old = nullptr;
      std::streambuf *   _clog_old = nullptr;

      // FILE* stdout capture
      FILE * _stdout_mem  = nullptr;
      FILE * _old_stdout  = nullptr;
      char * _stdout_buf  = nullptr;
      size_t _stdout_size = 0;

      // FILE* stderr capture
      FILE * _stderr_mem  = nullptr;
      FILE * _old_stderr  = nullptr;
      char * _stderr_buf  = nullptr;
      size_t _stderr_size = 0;
  };




  /*********************************************************************************************************************************
  ** A RAII Class that temporarily redirect standard input (for now just std::cin, not stdin)
  **
  ** Usage example:
  **   ProvideStdInput r("Alice 42");
  **   std::string name;
  **   int age;
  **   std::cin >> name >> age;
  **   ...
  **   std::println( "{} is {} years old", name, age);           // Alice is 42 years old.
  **
  **
  **   ProvideStdInput r("line1\nline 2\nline 3 and below");
  **   std::string s;
  **   while (std::getline(std::cin, s))  std::println("{:?}", s);  // "line1"
  **                                                                // "Line 2"
  **                                                                // "line 3 and below"
  **
  *********************************************************************************************************************************/
  class ProvideStdInput
  {
    public:
      explicit ProvideStdInput( std::string data )
      : _iss( std::move( data ) ), _old_buf( std::cin.rdbuf( _iss.rdbuf() ) )
      {}

      ProvideStdInput()                                       = delete;
      ProvideStdInput( ProvideStdInput const  & )             = delete;
      ProvideStdInput( ProvideStdInput       && )             = delete;
      ProvideStdInput & operator=( ProvideStdInput const  & ) = delete;
      ProvideStdInput & operator=( ProvideStdInput       && ) = delete;

      ~ProvideStdInput()
      { std::cin.rdbuf( _old_buf ); }

    private:
      std::istringstream _iss;            // reads from storage
      std::streambuf *   _old_buf;        // original cin buffer
  };
}        // export namespace Utilities












/***********************************************************************************************************************************
**  Module Utilities.CaptureStdOutput Private Implementation
**
**  Design Decision:  I seriously considered moving this module's implementation into its own unit (CaptureStdOutput.cpp file) instead
**                    of this private module fragment (module :private), but ultimately decided against it at this time.  I don't
**                    have a valid design or technical reason to buck "best practices". I just didn't want the overhead of two files.
**
**                    In either case, it is important to separate interface from implementation, which is why the lazy pattern of
**                    implementing functions "inline" as part of the class definition is consistently avoided.
***********************************************************************************************************************************/
// module :private;   // Not yet (version 16) supported in g++

// Not exported but reachable
/***********************************************************************************************************************************
************************************************************************************************************************************
** Separating Interface from Implementation is an extremely important concept I hope students will come to appreciate.
************************************************************************************************************************************
***********************************************************************************************************************************/
namespace Utilities
{
  CaptureStdOutput::CaptureStdOutput()
  {
    // --- Capture C++ streams ---
    // save the original associated buffer then redirect
    _cout_old = std::cout.rdbuf( _cout_ss.rdbuf() );
    _cerr_old = std::cerr.rdbuf( _cerr_ss.rdbuf() );
    _clog_old = std::clog.rdbuf( _clog_ss.rdbuf() );

    // --- Capture stdout (FILE*) ---
    _stdout_buf  = nullptr;
    _stdout_size = 0;
    _stdout_mem  = open_memstream( &_stdout_buf, &_stdout_size );
    if( _stdout_mem == nullptr )   throw std::runtime_error( "open_memstream(stdout) failed" );

    // save the original file descriptor then redirect to memory resident stream buffer
    _old_stdout = stdout;
    stdout     = _stdout_mem;

    // --- Capture stderr (FILE*) ---
    _stderr_buf  = nullptr;
    _stderr_size = 0;
    _stderr_mem  = open_memstream( &_stderr_buf, &_stderr_size );
    if( _stderr_mem == nullptr )   throw std::runtime_error( "open_memstream(stderr) failed" );

    // save the original file descriptor then redirect to memory resident stream buffer
    _old_stderr = stderr;
    stderr     = _stderr_mem;
  }




  CaptureStdOutput::CaptureStdOutput( std::string & results )
  : CaptureStdOutput()
  { _results = &results; }




  CaptureStdOutput::~CaptureStdOutput() noexcept
  {
    if( _results != nullptr ) *_results = get_all();

    // Restore FILE* streams
    fflush( _stdout_mem );
    fflush( _stderr_mem );

    stdout = _old_stdout;
    stderr = _old_stderr;

    fclose( _stdout_mem );
    fclose( _stderr_mem );

    // Restore C++ streams
    std::cout.rdbuf( _cout_old );
    std::cerr.rdbuf( _cerr_old );
    std::clog.rdbuf( _clog_old );
  }



  std::string CaptureStdOutput::get_stdout() const
  {
    fflush( _stdout_mem );
    return _stdout_buf != nullptr ? std::string( _stdout_buf, _stdout_size ) : "";
   }

  std::string CaptureStdOutput::get_stderr() const
  {
    fflush( _stderr_mem );
    return _stderr_buf != nullptr ? std::string( _stderr_buf, _stderr_size ) : "";
  }

  std::string CaptureStdOutput::get_cout() const
  { return _cout_ss.str(); }

  std::string CaptureStdOutput::get_cerr() const
  { return _cerr_ss.str(); }

  std::string CaptureStdOutput::get_clog() const
  { return _clog_ss.str(); }

}        // namespace Utilities















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
