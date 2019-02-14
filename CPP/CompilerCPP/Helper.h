#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <list>

namespace Helper
{
enum class TokenType
{
  Keyword,
  Identifier,
  Separator,
  Operator
};

class NotImplementedException : public std::logic_error
{
public:
  virtual char const *what() const { return "Function not yet implemented."; }
} NotImplementedEx;

class Helper
{
public:
  Helper::Helper();
  Helper::Helper(std::string);
  bool Helper::IsKeyword(std::string);
  bool Helper::IsIdentifier(std::string);
  bool Helper::IsSeparator(std::string);
  bool Helper::IsOperator(std::string);

private:
  std::list<std::string> PreParse;
  std::string Token;
  std::map<TokenType, std::string> PostParse;
};

Helper::Helper()
{
}

//
// Read from given file path or from default path and load into PreParse
//
Helper::Helper(std::string input)
{
  std::ifstream inputFile(input + "txt");
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
  if (input == "int" || input == "if" || input == "else")
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
  if (input == "," || input == "(" || input == ")" || input == ";" || input == "{" || input == "}")
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Helper::IsOperator(std::string input)
{
  if (input == ">" || input == "=")
  {
    return true;
  }
  else
  {
    return false;
  }
}

} // namespace Helper