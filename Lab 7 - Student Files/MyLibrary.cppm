export module MyLibrary.Prompt;
import std;


export namespace MyLibrary
{
  // Displays the promptMessage to standard output and returns the operator's response
  //    if we want an integer type response, we write:           MyLibrary::prompt<int>         ("Please enter ...");
  //    if we want a floating point type response, we write:     MyLibrary::prompt<double>      ("Please enter ...");
  //    and if we want a string type response, we write:         MyLibrary::prompt<std::string> ("Please enter ...");
  template <typename T>
  T prompt( std::string_view promptMessage );
}















/*************************************************************************************************************************
** Visible, but not exported
** Template definitions need to be visible at call point for implicit instantiation
**
*************************************************************************************************************************/
namespace MyLibrary
{
  // Function prompt takes a string and returns an object of the requested type T.
  // - The operator enters her response on the same line as the prompt message
  // - The prompt message is immediately followed by a colon and one space, for example if the promptMessage contains
  //        "Please enter data",
  // then the function displays
  //        "Please enter data: "
  template <typename T>
  T prompt( std::string_view promptMessage )
  {
    ///////////////////////// TO-DO (1) //////////////////////////////
      /// You did this function in Labs 3 and 4, almost.  Copy that and use it again here, but this time instead of reading and returning
      /// an int or double type, read and return a T type.  T is a type parameter passed here by caller.  For example, instead of
      ///    int userInput{0};
      /// you write
      ///    T userInput{};

    /////////////////////// END-TO-DO (1) ////////////////////////////
  }


  // Template Specialization for type std::string
  template <>
  std::string prompt<std::string>( std::string_view promptMessage )
  {
    ///////////////////////// TO-DO (2) //////////////////////////////
      /// You did this function in Lab 2.  Copy that and use it again here.
      /// If it looks like you always read an empty line, it's likely because there is still a newline character in the stream. This
      /// can happen when, for example, the last thing read was a number followed by a newline character (e.g., hitting the enter
      /// key).  The newline character is not consumed when reading numbers and remains in the stream. Then when you read a line of
      /// data with std::getline(...) you read everything up to the newline character - which would be nothing. Verify you use one
      /// of these two forms to extract data from standard input:
      ///    std::getline( std::cin >> std::ws, userInput );          // reads everything up to the newline character
      /// or
      ///    std::cin >> std::quoted( userInput );                    // reads everything inside double quotes, or just the next
      ///                                                             // whitespace delimited word if no quotes are found

    /////////////////////// END-TO-DO (2) ////////////////////////////
  }
}
