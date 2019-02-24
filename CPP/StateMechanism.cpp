#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <list>
#include <regex>
#include <algorithm>
#include <iterator>

namespace StateMechanism
{
	enum class TokenType
	{
		Initial,
		Keyword,
		Identifier,
		Separator,
		Operator,
		Number,
		WhiteSpace,
		Comment
	};

	enum class States
	{
		StateIs,
		StateIsKeyword,
		StateIsIdentifier,
		StateIsSeperator,
		StateIsOperator,
		StateIsNumber,
		StateIsWhiteSpace,
		StateIsComment
	};

	// 2D object of state transitions from IsState (the initial state)
	//
	// implementation -> compare tokentype to Transitions list and switch based
	// on Transitions.first/Transitions.second
	std::list<std::pair<TokenType, States>> Transitions{
		{TokenType::Initial, States::StateIs},
		{TokenType::Keyword, States::StateIsKeyword},
		{TokenType::Identifier, States::StateIsIdentifier},
		{TokenType::Separator, States::StateIsSeperator},
		{TokenType::Operator, States::StateIsOperator},
		{TokenType::Number, States::StateIsNumber},
		{TokenType::WhiteSpace, States::StateIsWhiteSpace},
		{TokenType::Comment, States::StateIsComment} };

	/*class NotImplementedException : public std::logic_error
	{
	public:
		virtual char const *what() const { return "Function not yet implemented."; }
	} NotImplementedEx;*/

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
		std::pair<TokenType, std::string> PopPostParse();
		void PushPostParse(TokenType, std::string);
		std::list<std::string> GetNext(int);
		std::string Token;

	private:
		std::list<char> PreParse;
		std::list<std::pair<TokenType, std::string>> PostParse;
	};

	Helper::Helper()
	{
		std::ifstream inputFile;
		inputFile.open("Input.txt", std::ios::in);
		if (inputFile.is_open())
		{
			char charParse;
			while (inputFile.get(charParse))
			{
				PreParse.push_front(charParse);
			}
			inputFile.close();
		}
		else
		{
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
		if (inputFile.is_open())
		{
			char charParse;
			while (inputFile.get(charParse))
			{
				PreParse.push_front(charParse);
			}
			inputFile.close();
		}
		else
		{
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

	/*bool Helper::IsIdentifier(std::string input)
	{
	}*/

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
		char returnChar = PreParse.front();
		PreParse.pop_front();
		return returnChar;
	}

	// Untested
	//
	// Return list<string> with next multiple items in PreParse List
	//
	/*std::list<std::string> Helper::GetNext(int iterator)
	{
		std::list<std::string> returnList;
		for (int i = 0; i < iterator; i++)
		{
			returnList.assign(PreParse.front());
			PreParse.pop_front();
		}
	}*/

	void Helper::PushPreParse(char input)
	{
		PreParse.push_front(input);
	}

	char Helper::PopPreParse()
	{
		char returnChar = PreParse.front();
		PreParse.pop_front();
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

	std::pair<TokenType, std::string> Helper::PopPostParse()
	{
		//std::list<std::pair<TokenType, std::string>>::iterator it = PostParse.begin();
		std::pair<TokenType, std::string> pair = PostParse.front();
		PostParse.pop_front();
		return pair;
	}

	void Helper::PushPostParse(TokenType tokenType, std::string input)
	{
		std::pair<TokenType, std::string> pair;
		pair.first = tokenType;
		pair.second = input;
		PostParse.push_front(pair);
	}

	class StateMechanism
	{
		StateMechanism();
		StateMechanism(std::string);
		void StateTransition(Helper, TokenType, States, std::string, char);
		void StateIs(Helper);
		void StateIsKeyword(std::string);
		void StateIsIdentifier(std::string);
		void StateIsSeparator(char);
		void StateIsOperator(char);
		void StateIsNumber(std::string);
		void StateIsComment(char);
		void StateIsWhiteSpace();
		std::string GetCurrentState();
		std::string GetCurrentToken();

	private:
		States CurrentState;
		TokenType CurrentToken;
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

	// Iterate through Transitions to find next state
	// 0 = initial, 1 = Keyword, 2 = Identifier, 3 = Separator, 4 = Operator, 5 = Number, 6 = Comment
	void StateMechanism::StateTransition(Helper helper, TokenType tokenType, States states, std::string strBuilder, char charBuilder)
	{
		std::pair<TokenType, States> transition{ tokenType, states };
		std::list<std::pair<TokenType, States>>::iterator it = Transitions.begin();
	}

	// Initial State
	void StateMechanism::StateIs(Helper helper)
	{
		while (!helper.IsPreParseEmpty())
		{
			CurrentState = States::StateIs;
			char charBuilder;
			std::string strBuilder;
			while (!helper.IsWhitespaceOrSeparatorOrOperator(charBuilder = helper.PopPreParse()))
			{
				strBuilder += charBuilder;
			}

			// Test strBuilder
			if (!strBuilder.empty() && helper.IsKeyword(strBuilder))
			{
				CurrentToken = TokenType::Keyword;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}
			else if (!strBuilder.empty() && helper.IsNumber(strBuilder))
			{
				CurrentToken = TokenType::Number;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}
			else if (!strBuilder.empty())
			{
				CurrentToken = TokenType::Separator;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}

			// Test charBuilder
			if (helper.IsSeparator(charBuilder))
			{
				CurrentToken = TokenType::Separator;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}
			else if (helper.IsOperator(charBuilder))
			{
				CurrentToken = TokenType::Operator;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}
			else if (helper.IsComment(charBuilder))
			{
				CurrentToken = TokenType::Comment;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}
			else
			{
				CurrentToken = TokenType::WhiteSpace;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}
		}
	}

	void StateMechanism::StateIsKeyword(std::string input)
	{
		CurrentState = States::StateIsKeyword;
		//throw NotImplementedEx;
	}

	void StateMechanism::StateIsIdentifier(std::string input)
	{
		CurrentState = States::StateIsIdentifier;
		//throw NotImplementedEx;
	}

	void StateMechanism::StateIsSeparator(char input)
	{
		CurrentState = States::StateIsSeperator;
		//throw NotImplementedEx;
	}

	void StateMechanism::StateIsOperator(char input)
	{
		CurrentState = States::StateIsOperator;
		//throw NotImplementedEx;
	}

	void StateMechanism::StateIsNumber(std::string input)
	{
		CurrentState = States::StateIsNumber;
		//throw NotImplementedEx;
	}

	void StateMechanism::StateIsComment(char input)
	{
		CurrentState = States::StateIsComment;
		//throw NotImplementedEx;
	}

	void StateMechanism::StateIsWhiteSpace()
	{
		CurrentState = States::StateIsWhiteSpace;
		//throw NotImplementedEx;
	}

	std::string StateMechanism::GetCurrentState() {
		if (CurrentState == States::StateIs) { return "InitialState"; }
		else if (CurrentState == States::StateIsComment) { return "CommentState"; }
		else if (CurrentState == States::StateIsIdentifier) { return "IdentifierState"; }
		else if (CurrentState == States::StateIsKeyword) { return "KeywordState"; }
		else if (CurrentState == States::StateIsNumber) { return "NumberState"; }
		else if (CurrentState == States::StateIsOperator) { return "OperatorState"; }
		else if (CurrentState == States::StateIsSeperator) { return "SeparatorState"; }
		else if (CurrentState == States::StateIsWhiteSpace) { return "WhiteSpaceState"; }
	}
} // namespace StateMechanism