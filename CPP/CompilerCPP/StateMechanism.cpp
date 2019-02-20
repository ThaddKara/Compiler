#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <list>
#include <regex>

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

class Helper
{
  public:
	Helper();
	Helper(std::string);
	bool IsKeyword(std::string);
	bool IsIdentifier(std::string);
	bool IsSeparator(std::string);
	bool IsSeparator(char);
	bool IsOperator(char);
	bool IsNumber(std::string);
	bool IsComment(char);
	bool IsWhitespaceOrSeparatorOrOperator(char);
	char GetNext();
	void PushPreParse(char);
	char PopPreParse();
	bool IsPreParseEmpty();
	std::list<std::string> GetNext(int);
	std::string Token;

  private:
	std::list<char> PreParse;
	std::map<TokenType, std::string> PostParse;
};

Helper::Helper()
{
	std::ifstream inputFile;
	inputFile.open("Input.txt", std::ios::in);
	if (inputFile.is_open)
	{
		char charParse;
		while (inputFile.get(charParse))
		{
			PreParse.push_front(charParse);
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
// fills chars into PreParse
//
Helper::Helper(std::string input)
{
	std::ifstream inputFile;
	inputFile.open(input + ".txt", std::ios::in);
	if (inputFile.is_open)
	{
		char charParse;
		while (inputFile.get(charParse))
		{
			PreParse.push_front(charParse);
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

bool Helper::IsSeparator(char input)
{
	if (input == ',' || input == '(' || input == ')' || input == ';' || input == '{' || input == '}')
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

// Untested
// Also checks for floats
bool Helper::IsNumber(std::string input)
{
	std::regex regint("[0-9]+:[0-9]+");
	std::regex regfloat("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
	if (std::regex_match(input, regint) || std::regex_match(input, regfloat))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Helper::IsComment(char input)
{
	if (input == '!')
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
	if (input == ' ' || IsSeparator(input) || IsOperator(input))
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
char Helper::GetNext()
{
	char returnChar = PreParse.front;
	PreParse.pop_front;
	return returnChar;
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

void Helper::PushPreParse(char input)
{
	PreParse.push_front(input);
}

char Helper::PopPreParse()
{
	char returnChar = PreParse.front;
	PreParse.pop_front;
	return returnChar;
}

bool Helper::IsPreParseEmpty()
{
	if (PreParse.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

class StateMechanism
{
	StateMechanism();
	StateMechanism(std::string);
	void StateIs(Helper);
	void StateIsKeyword(std::string);
	void StateIsIdentifier(std::string);
	void StateIsSeparator(char);
	void StateIsOperator(char);
	void StateIsNumber(std::string);
	void StateIsComment(char);
	void StateIsWhiteSpace();
	States CurrentState;
};

// Pre-Initial State
StateMechanism::StateMechanism()
{
	Helper helper;
	StateIs(helper);
}

// Pre-Initial State
StateMechanism::StateMechanism(std::string fileName)
{
	Helper helper(fileName);
	StateIs(helper);
}

// Initial State
void StateMechanism::StateIs(Helper helper)
{
	while (!helper.IsPreParseEmpty())
	{
		char charBuilder;
		std::string strBuilder;
		while (!helper.IsWhitespaceOrSeparatorOrOperator(charBuilder = helper.PopPreParse()))
		{
			strBuilder += charBuilder;
		}

		// Test strBuilder
		if (!strBuilder.empty() && helper.IsKeyword(strBuilder))
		{
			StateIsKeyword(strBuilder);
		}
		else if (!strBuilder.empty() && helper.IsNumber(strBuilder))
		{
			StateIsNumber(strBuilder);
		}
		else if (!strBuilder.empty())
		{
			StateIsIdentifier(strBuilder);
		}

		// Test charBuilder
		if (helper.IsSeparator(charBuilder))
		{
			StateIsSeparator(charBuilder);
		}
		else if (helper.IsOperator(charBuilder))
		{
			StateIsOperator(charBuilder);
		}
		else if (helper.IsComment(charBuilder))
		{
			StateIsComment(charBuilder);
		}
		else
		{
			StateIsWhiteSpace();
		}
	}
}

void StateMechanism::StateIsKeyword(std::string input)
{
	throw NotImplementedEx;
}

void StateMechanism::StateIsIdentifier(std::string input)
{
	throw NotImplementedEx;
}

void StateMechanism::StateIsSeparator(char input)
{
	throw NotImplementedEx;
}

void StateMechanism::StateIsOperator(char input)
{
	throw NotImplementedEx;
}

void StateMechanism::StateIsNumber(std::string input)
{
	throw NotImplementedEx;
}

void StateMechanism::StateIsComment(char input)
{
	throw NotImplementedEx;
}

void StateMechanism::StateIsWhiteSpace()
{
	throw NotImplementedEx;
}
} // namespace StateMechanism