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
		bool IsWhitespaceOrSeparatorOrOperator(char);
		char GetNext();
		void PushPreParse(char);
		std::list<std::string> GetNext(int);
		std::string Token;
		std::map<TokenType, std::string> PostParse;
	private:
		std::list<char> PreParse;
	};

	Helper::Helper()
	{
		std::ifstream inputFile;
		inputFile.open("Input.txt", std::ios::in);
		if (inputFile.is_open)
		{
			char charParse;
			int count = 0;
			while (inputFile.get(charParse))
			{
				PreParse.assign(count, charParse);
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
	// fills chars into PreParse
	//
	Helper::Helper(std::string input)
	{
		std::ifstream inputFile;
		inputFile.open(input + ".txt", std::ios::in);
		if (inputFile.is_open)
		{
			char charParse;
			int count = 0;
			while (inputFile.get(charParse))
			{
				PreParse.assign(count, charParse);
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

	void Helper::PushPreParse(char input){
		PreParse.push_front(input);
	}

	class StateMechanism
	{
		StateMechanism();
		StateMechanism(Helper helper);
		States StateIs(TokenType);
		void StateIsKeyword();
		void StateIsIdentifier();
		void StateIsSeparator();
		void StateIsOperator();
		void StateIsNumber();
		void StateIsComments();
	};

	StateMechanism::StateMechanism()
	{
		throw NotImplementedEx;
	}

	// Initial State
	StateMechanism::StateMechanism(Helper helper)
	{
		std::string strBuilder;
		char charBuilder;
		while(!helper.IsWhitespaceOrSeparatorOrOperator((charBuilder=helper.GetNext())))
		{
			strBuilder+=charBuilder;
		} 
	}
} // namespace StateMechanism