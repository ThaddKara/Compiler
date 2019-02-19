#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <list>

namespace StateMechanism
{
enum TokenType
{
  Keyword,
  Identifier,
  Separator,
  Operator
};

enum States
{
  Process,
  FetchOperation,
  Stop
};

class NotImplementedException : public std::logic_error
{
public:
  virtual char const *what() const { return "Function not yet implemented."; }
} NotImplementedEx;

class StateMechanism
{
  StateMechanism::StateMechanism();
  StateMechanism::StateMechanism(Helper);
  States StateMechanism::StateIs(TokenType);
};

class Helper
{
public:
  Helper::Helper();
  Helper::Helper(std::string);
  bool Helper::IsKeyword(std::string);
  bool Helper::IsIdentifier(std::string);
  bool Helper::IsSeparator(std::string);
  bool Helper::IsSeparator(char);
  bool Helper::IsOperator(char);
  bool Helper::IsWhitespaceOrSeparatorOrOperator(char);
  std::string Helper::GetNext();
  std::list<std::string> Helper::GetNext(int);
  std::list<std::string> PreParse;
  std::string Token;
  std::map<TokenType, std::string> PostParse;
};

Helper::Helper()
{
  std::ifstream inputFile("Input.txt");
  if (inputFile.is_open)
  {
    std::string lineParse;
    int count = 0;
    while (std::getline(inputFile, lineParse))
    {
      PreParse.assign(count, lineParse);
      ++count;
    }
    inputFile.close;
  }
  else
  {
    throw NotImplementedEx;
  }
}

//
// Read from given file path or from default path and load into PreParse
//
Helper::Helper(std::string input)
{
  std::ifstream inputFile(input + ".txt");
  if (inputFile.is_open)
  {
    std::string lineParse;
    int count = 0;
    while (std::getline(inputFile, lineParse))
    {
      PreParse.assign(count, lineParse);
      ++count;
    }
    inputFile.close;
  }
  else
  {
    throw NotImplementedEx;
  }
}

bool Helper::IsKeyword(std::string input)
{
  if (input == "int" || input == "if" 
  || input == "else")
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Helper::IsIdentifier(std::string input)
{
}

bool Helper::IsSeparator(std::string input)
{
  if (input == "," || input == "(" 
  || input == ")" || input == ";" 
  || input == "{" || input == "}")
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Helper::IsSeparator(char input)
{
  if (input == ',' || input == '(' 
  || input == ')' || input == ';' 
  || input == '{' || input == '}')
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Helper::IsOperator(char input)
{
  if (input == '>' || input == '=')
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Helper::IsWhitespaceOrSeparatorOrOperator(char input)
{
  if (input == ' ' || IsSeparator(input)
  || IsOperator(input))
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Untested
//
// Return next string from PreParse list
//
std::string Helper::GetNext()
{
  std::string returnString = PreParse.front;
  PreParse.pop_front;
  return returnString;
}

// Untested
//
// Return list<string> with next multiple items in PreParse List
//
std::list<std::string> Helper::GetNext(int iterator)
{
  std::list<std::string> returnList;
  for (int i = 0; i < iterator; i++)
  {
    returnList.assign(PreParse.front);
    PreParse.pop_front;
  }
}

} // namespace Helper