#pragma once

#include <string>
namespace Helper
{
class Helper
{
public:
  Helper::Helper();
  Helper::Helper(std::string);
  bool Helper::IsKeyword(std::string);
  bool Helper::IsIdentifier(std::string);
  bool Helper::IsSeparator(std::string);
  bool Helper::IsOperator(std::string);
};

Helper::Helper()
{
}

Helper::Helper(std::string input)
{
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
  if(input==">"||input=="=")
  {
    return true;
  }
  else
  {
    return false;
  }
  
}
} // namespace Helper