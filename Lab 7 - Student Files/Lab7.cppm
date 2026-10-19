export module Lab7.Functions;
import std;

using std::string;










export namespace Lab7
{
  /*********************************************************************************************************************************
  **  Module Lab7.Functions Interface
  **
  **  Function Declarations
  *********************************************************************************************************************************/
  // Returns true if day is a day of the week as enumerated below
  bool isValidDay( const string & day ) noexcept;





  // returns true if hour is less than HOURS_PER_DAY
  bool isValidHour( unsigned int hour ) noexcept;





  // returns true if minute is less than MINUTES_PER_HOUR
  bool isValidMinute( unsigned int hour ) noexcept;





  // Returns PARKING_ALLOWED as enumerated below if parking is allowed on Ash Street at the given time, and PARKING_NOT_ALLOWED
  // otherwise.
  //
  // The sign on Ash street reads:
  //   NO PARKING 10AM TO 12PM WEDNESDAY STREET SWEEPING
  //
  // day is the name of a day of the week as enumerated below.
  //
  // hour is the number 0 up to but not including HOURS_PER_DAY, using 24-hour notation (military time), so 7 means 7 AM and
  // 19 means 7 PM.
  //
  // Constraint:  Assumes parameters day and hour are valid
  string canParkOnAsh( const string & day, unsigned int hour );





  // Returns PARKING_ALLOWED as enumerated below if parking is allowed on Beech Street at the given time, and PARKING_NOT_ALLOWED
  // otherwise.
  //
  // The sign on Beech street reads:
  //   Street Cleaning Every Friday of EACH MONTH, 8 am - 12 noon
  //
  // day is the name of a day of the week as enumerated below.
  //
  // hour is the number 0 up to but not including HOURS_PER_DAY, using 24-hour notation (military time), so 7 means 7 AM and
  // 19 means 7 PM.
  //
  // Constraint:  Assumes parameters day and hour are valid
  string canParkOnBeech( const string & day, unsigned int hour );





  // Returns PARKING_ALLOWED as enumerated below if parking is allowed on Cedar Street at the given time, and PARKING_NOT_ALLOWED
  // otherwise.
  //
  // The signs on Cedar street read:
  //   NO PARKING NIGHTTIME 7PM - 7AM EVERYDAY
  //   NO PARKING 8 AM to 10 AM TUESDAY STREET SWEEPING
  //
  // day is the name of a day of the week as enumerated below.
  //
  // hour is the number 0 up to but not including HOURS_PER_DAY, using 24-hour notation (military time), so 7 means 7 AM and
  // 19 means 7 PM.
  //
  // Constraint:  Assumes parameters day and hour are valid
  string canParkOnCedar( const string & day, unsigned int hour );





  // Returns PARKING_ALLOWED as enumerated below if parking is allowed on Date Street at the given time, and PARKING_NOT_ALLOWED
  // otherwise.
  //
  // The signs on Date street read:
  //   NO PARKING 6:30 AM TO 4 PM EXCEPT SATURDAY & SUNDAY
  //
  // day is the name of a day of the week as enumerated below.
  //
  // hour is the hour number 0 up to but not including HOURS_PER_DAY, using 24-hour notation (military time), so 7 means 7 AM
  // and 19 means 7 PM.
  //
  // minute must be the minute number, 0 up to but not including MINUTES_PER_HOUR, so at 3:25 PM, minute would be 25.
  //
  // Constraint:  Assumes parameters day, hour, and minute are valid
  string canParkOnDate( const string & day, unsigned int hour, unsigned int minute );
}  // namespace Lab7

























/***********************************************************************************************************************************
**  Module Lab7.Functions Implementation
**
**  Function Definitions
**  Private implementation: Not exported and not reachable
***********************************************************************************************************************************/
// GCC doesn't yet (as of version 16.1.0) support private fragments.  (Clang and MS VC++ already do.)  The workaround (and perhaps
// preferred method) is to move this content to a separate implementation source file (.cpp).  However, I wanted to demonstrate the
// use of a single module interface file that still separates the extremely important concept of separating interface from
// implementation.  There are pros and cons to both approaches.
//
// module : private;     // GCC lists this fixed in 16.2, but that is after our Fall '26 cutoff.  So, for now we'll keep it commented out

namespace   // Private definitions
{
  /*********************************************************************************************************************************
  **  Enumerated Constant and Threshold Definitions
  **
  **  Note:  We'll look at other ways to define enumerated constants in upcoming labs
  *********************************************************************************************************************************/
  const string PARKING_ALLOWED    { "allowed"     };
  const string PARKING_NOT_ALLOWED{ "not allowed" };

  const string SUN{ "Sunday"    };
  const string MON{ "Monday"    };
  const string TUE{ "Tuesday"   };
  const string WED{ "Wednesday" };
  const string THR{ "Thursday"  };
  const string FRI{ "Friday"    };
  const string SAT{ "Saturday"  };

  const unsigned int HOURS_PER_DAY   { 24 };
  const unsigned int MINUTES_PER_HOUR{ 60 };
}   // namespace Private definitions










namespace Lab7
{
  // Implement function isValidDay(...).
  bool isValidDay( const string & day ) noexcept
  {
    ///////////////////////// TO-DO (1) //////////////////////////////
      /// Hint:
      ///   o) a compound Boolean expression with multiple operators may be needed
      ///   o) As in the prior lab, avoid using an if statement.  Recall:
      ///      In this case, avoid using an if statement.  That is, avoid the obvious:
      ///
      ///        if( something == "dog"  ||  some_other_thing == "cat" ) return true;
      ///        else                                                    return false;
      ///
      ///
      ///      instead, just return the Boolean answer, like this:
      ///
      ///        return something == "dog"  ||  some_other_thing == "cat";
      ///

    /////////////////////// END-TO-DO (1) ////////////////////////////
  }





  // Define and implement function isValidHour(...)
  ///////////////////////// TO-DO (2) //////////////////////////////
    /// Hint:
    ///   o) Copy function isValidHour(...)'s declaration from above and paste it here.  Then remove the semicolon and open a set of
    ///      curly braces.
    ///   o) Return true if parameter hour is less than hours per day from above, false otherwise.
    ///   o) Use function isValidDay(...) as an example

  /////////////////////// END-TO-DO (2) ////////////////////////////





  // Define and implement function isValidMinute(...)
  ///////////////////////// TO-DO (3) //////////////////////////////
    /// Hint:
    ///   o) Copy function isValidMinute(...)'s declaration from above and paste it here.  Then remove the semicolon and open a set of
    ///      curly braces.
    ///   o) Return true if parameter minute is less than minutes per hours from above, false otherwise.
    ///   o) Use function isValidDay(...) as an example

  /////////////////////// END-TO-DO (3) ////////////////////////////





  // Implement function canParkOnAsh(...)
  string canParkOnAsh( const string & day, unsigned int hour )
  {
    ///////////////////////// TO-DO (4) //////////////////////////////
      /// Write code to decide if parking is allowed or not and return the answer.
      /// See declaration above for parking restriction rules.  For example:
      ///       if it is Wednesday between 8'Oclock AM and 1'Oclock PM, then  parking is not allowed
      ///    or
      ///       if it is Wednesday or Friday before Noon, then parking is allowed
      /// Hints:
      ///   o) A compound Boolean expression with multiple operators may be needed
      ///   o) Be sure to return one of the parking allowed or not allowed enumerated constant strings from above
      ///   o) Assume day and hour have already been validated

    /////////////////////// END-TO-DO (4) ////////////////////////////
  }





  // Define and implement function canParkOnBeech(...)
  ///////////////////////// TO-DO (5) //////////////////////////////
    /// Hint:  Copy function canParkOnBeech(...)'s declaration from above and paste it here.  Then remove the semicolon and open a
    ///        set of curly braces.
      /// Write code to decide if parking is allowed or not and return the answer.
      /// See declaration above for parking restriction rules.  For example:
      ///       if it is Wednesday between 8'Oclock AM and 1'Oclock PM, then  parking is not allowed
      ///    or
      ///       if it is Wednesday or Friday before Noon, then parking is allowed
      /// Hints:
      ///   o) A compound Boolean expression with multiple operators may be needed
      ///   o) Be sure to return one of the parking allowed or not allowed enumerated constant strings from above
      ///   o) Assume day and hour have already been validated
      ///   o) Use function canParkOnAsh(...) as an example

  /////////////////////// END-TO-DO (5) ////////////////////////////





  // Define and implement function canParkOnCedar(...)
  ///////////////////////// TO-DO (6) //////////////////////////////
    /// Hint:  Copy function canParkOnCedar(...)'s declaration from above and paste it here.  Then remove the semicolon and open a
    ///        set of curly braces.
      /// Write code to decide if parking is allowed or not and return the answer.
      /// See declaration above for parking restriction rules.  For example:
      ///       if it is Wednesday between 8'Oclock AM and 1'Oclock PM, then  parking is not allowed
      ///    or
      ///       if it is Wednesday or Friday before Noon, then parking is allowed
      /// Hints:
      ///   o) A compound Boolean expression with multiple operators may be needed
      ///   o) Be sure to return one of the parking allowed or not allowed enumerated constant strings from above
      ///   o) Assume day and hour have already been validated
      ///   o) Use function canParkOnAsh(...) as an example

  /////////////////////// END-TO-DO (6) ////////////////////////////





  // Define and implement function canParkOnDate(...)
  ///////////////////////// TO-DO (7) //////////////////////////////
    /// Hint:  Copy function canParkOnDate(...)'s declaration from above and paste it here.  Then remove the semicolon and open a
    ///        set of curly braces.
      /// Write code to decide if parking is allowed or not and return the answer.
      /// See declaration above for parking restriction rules.  For example:
      ///       if it is Wednesday between 8'Oclock AM and 1'Oclock PM, then  parking is not allowed
      ///    or
      ///       if it is Wednesday or Friday before Noon, then parking is allowed
      /// Hints:
      ///   o) A compound Boolean expression with multiple operators may be needed
      ///   o) Be sure to return one of the parking allowed or not allowed enumerated constant strings from above
      ///   o) Assume day, hour, and minute have already been validated
      ///   o) Multiply (assuming 0..23) hours by 100 and then add minutes to get military clock time (e.g., 13:30 hours for 1:30 PM)
      ///   o) Use function canParkOnAsh(...) as an example

  /////////////////////// END-TO-DO (7) ////////////////////////////
}  // namespace Lab7
