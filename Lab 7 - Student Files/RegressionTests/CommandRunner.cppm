/***********************************************************************************************************************************
** Run a shell command and capture the standard output and error streams as well as the command's exit status
**
** Usage example:
** int main()
** {
**   auto [out, err, exit_code] = Utilities::CommandRunner( "/usr/bin/ls", { "-A", "-l" } ).run();  // with command arguments
**    or
**   auto [out, err, exit_code] = Utilities::CommandRunner( "/usr/bin/ls" ).run();                  // without command arguments
**
**   std::print( std::cout, "STDOUT:\n{}\n\n"
**                          "STDERR:\n{}\n\n"
**                          "Exit code: {}\n",
**               out, err, exit_code );
** }
***********************************************************************************************************************************/


module;
  #include <sys/wait.h>        // pip_t, waitpid()
  #include <unistd.h>          // pipe(), close(), dup2(), STDOUT_FILENO, STDERR  _FILENO


export module Utilities.CommandRunner;
import std;


export namespace Utilities
{
  struct CommandResult
  {
      std::string _stdout_str;
      std::string _stderr_str;
      int         _exit_code{ 0 };
  };


  class CommandRunner
  {
    public:
      CommandRunner()                                        = delete;
      CommandRunner( CommandRunner const & )                 = delete;
      CommandRunner( CommandRunner && ) noexcept             = delete;
      CommandRunner & operator=( CommandRunner const & )     = delete;
      CommandRunner & operator=( CommandRunner && ) noexcept = delete;

      CommandRunner( std::string program, std::vector<std::string> args = {} );
      ~CommandRunner() noexcept;

      CommandResult run();

    private:
      // Instance attributes
      std::string              _program;
      std::vector<std::string> _args;
      std::array<int, 2>       _stdout_pipe{};
      std::array<int, 2>       _stderr_pipe{};

      // Private helper functions
      [[noreturn]] void child_exec();
      CommandResult     parent_collect( pid_t pid );
  };
}        // namespace Utilities












/***********************************************************************************************************************************
**  Module Utilities.CommandRunner Private Implementation
**
**  Design Decision:  I seriously considered moving this module's implementation into its own unit (CommandRunner.cpp file) instead
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
  CommandRunner::CommandRunner( std::string program, std::vector<std::string> args )
  : _program( std::move( program ) ), _args( std::move( args ) )
  {
    // RAII:  Create POSIX pipes to receive stdout and stderr
    if( pipe( _stdout_pipe.data() ) == -1 ) throw std::runtime_error( "pipe(stdout) failed" );

    if( pipe( _stderr_pipe.data() ) == -1 )
    {
      close( _stdout_pipe[0] );
      close( _stdout_pipe[1] );
      throw std::runtime_error( "pipe(stderr) failed" );
    }
  }




  CommandRunner::~CommandRunner() noexcept
  {
    // RAII:  Close the POSIX pipes to receive stdout and stderr
    for( auto fd : { _stdout_pipe[0], _stdout_pipe[1], _stderr_pipe[0], _stderr_pipe[1] } )
    {
      if( fd >= 0 ) close( fd );
    }
  }



  CommandResult CommandRunner::run()
  {
    pid_t pid = fork();
    if( pid < 0 ) throw std::runtime_error( "fork failed" );

    if( pid == 0 ) child_exec();        // never returns

    return parent_collect( pid );
  }




  void CommandRunner::child_exec()
  {
    // Close read ends of the pipes
    close( _stdout_pipe[0] );
    close( _stderr_pipe[0] );

    // Redirect stdout and stderr
    dup2( _stdout_pipe[1], STDOUT_FILENO );
    dup2( _stderr_pipe[1], STDERR_FILENO );

    // Close write ends after dup
    close( _stdout_pipe[1] );
    close( _stderr_pipe[1] );

    // Build argv array
    std::vector<char *> argv;
    argv.reserve( _args.size() + 2 );        // one for the program name and one for the null string at the end

    argv.push_back( const_cast<char *>( _program.c_str() ) );
    for( auto & arg : _args )  argv.push_back( const_cast<char *>( arg.c_str() ) );

    argv.push_back( nullptr );

    execvp( _program.c_str(), argv.data() );

    _exit( 127 );                            // exec failed
  }






  CommandResult CommandRunner::parent_collect( pid_t pid )
  {
    // Close write ends of the pipes
    close( _stdout_pipe[1] );
    close( _stderr_pipe[1] );

    std::string            out;
    std::string            err;
    std::array<char, 4096> buffer;

    ssize_t n = 0;
    // Read stdout and then stderr while there is something more to read
    while( ( n = read( _stdout_pipe[0], buffer.data(), buffer.size() ) ) > 0 )  out.append( buffer.data(), n );
    while( ( n = read( _stderr_pipe[0], buffer.data(), buffer.size() ) ) > 0 )  err.append( buffer.data(), n );

    // Close read ends
    close( _stdout_pipe[0] );
    close( _stderr_pipe[0] );

    // Wait for child
    int status = 0;
    waitpid( pid, &status, 0 );

    int exit_code = WIFEXITED( status ) ? WEXITSTATUS( status ) : -1;

    return { ._stdout_str = out, ._stderr_str = err, ._exit_code = exit_code };
  }
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
