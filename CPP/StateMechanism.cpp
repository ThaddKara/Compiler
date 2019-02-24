#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <list>
#include <regex>
#include <algorithm>
#include <iterator>
#include "StateMechanism.h"

/*namespace DFSM
/*{
	enum class TokenType
	{
		Initial,
		Keyword,
		Identifier,
		Separator,
		Operator,
		Number,
		WhiteSpace,
		Comment,
		Unknown
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
		StateIsComment,
		StateIsUnknown
	};*/

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
		{TokenType::Comment, States::StateIsComment},
		{TokenType::Unknown, States::StateIsUnknown} };

	/*class NotImplementedException : public std::logic_error
	{
	public:
		virtual char const *what() const { return "Function not yet implemented."; }
	} NotImplementedEx;*/

	/*class Helper
	{
	public:
		Helper();
		Helper(std::string);
		bool IsKeyword(std::string);
		//bool IsIdentifier(std::string);
		bool IsSeparator(std::string);
		bool IsSeparator(char);
		bool IsOperator(char);
		bool IsNumber(std::string);
		bool IsComment(char);
		bool IsWhitespaceOrSeparatorOrOperator(char);
		bool IsWhiteSpace(char);
		char GetNext();
		void PushPreParse(char);
		char PopPreParse();
		bool IsPreParseEmpty();
		std::pair<TokenType, std::string> PopPostParse();
		void PushPostParse(TokenType, std::string);
		//std::list<std::string> GetNext(int);
		void WritetoFile(std::string, TokenType);
		void WriteToFile(char, TokenType);
		std::string TokenReturn(TokenType);

	private:
		std::list<char> PreParse;
		std::list<std::pair<TokenType, std::string>> PostParse;
	};*/

	Helper::Helper()
	{
		std::ifstream inputFile;
		inputFile.open("Input.txt", std::ios::in);
		if (inputFile.is_open())
		{
			char charParse;
			while (inputFile.get(charParse))
			{
				std::cout << charParse << std::endl;
				PreParse.push_front(charParse);
			}
			inputFile.close();
		}
		else
		{
			std::cout << "fail" << std::endl;
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
				std::cout << charParse << std::endl;
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
		if (IsWhiteSpace(input) || IsSeparator(input) || IsOperator(input))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Helper::IsWhiteSpace(char input)
	{
		if (input == ' ')
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
			returnList.assign(PreParse.begin(), PreParse.end()); // JK: not 100% sure if this is how you wanted to use assign with PreParse
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

	void Helper::WritetoFile(std::string tokenVal, TokenType tokenType)
	{
		std::ofstream writter;
		writter.open("Output.txt", std::ios::app);
		writter << tokenVal << "-----" << TokenReturn(tokenType) << std::endl;
		writter.close();
	}

	void Helper::WriteToFile(char tokenVal, TokenType tokenType)
	{
		std::ofstream writter;
		writter.open("Output.txt", std::ios::app);
		writter << tokenVal << "-----" << TokenReturn(tokenType) << std::endl;
		writter.close();
	}

	std::string Helper::TokenReturn(TokenType tokenType)
	{
		if (tokenType == TokenType::Keyword) { return "Keyword"; }
		else if (tokenType == TokenType::Number) { return "Number"; }
		else if (tokenType == TokenType::Identifier) { return "Identifier"; }
		else if (tokenType == TokenType::Separator) { return "Separator"; }
		else if (tokenType == TokenType::Operator) { return "Operator"; }
		else if (tokenType == TokenType::Comment) { return "Comment"; }
		else if (tokenType == TokenType::WhiteSpace) { return "WhiteSpace"; }
		else { return "Unknown"; }
	}

	/*class StateMechanism
	{
		StateMechanism();
		StateMechanism(std::string);
		void StateTransition(Helper, TokenType, States, std::string, char);
		void StateIs(Helper);
		void StateIsKeyword(Helper, TokenType, std::string);
		void StateIsIdentifier(Helper, TokenType, std::string);
		void StateIsSeparator(Helper, TokenType, char);
		void StateIsOperator(Helper, TokenType, char);
		void StateIsNumber(Helper, TokenType, std::string);
		void StateIsComment(Helper, TokenType, char);
		void StateIsWhiteSpace(Helper, TokenType, char);
		void StateIsUnknown(Helper, TokenType, char);
		void End();
		std::string GetCurrentState();
		//std::string GetCurrentToken();

	private:
		States CurrentState;
		TokenType CurrentToken;
	};*/

	// Pre-Initial State
	StateMechanism::StateMechanism()
	{
		std::cout << "fail" << std::endl;
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
	void StateMechanism::StateTransition(Helper helper, TokenType tokenType, States states, std::string strBuilder, char charBuilder)
	{
		States toState;
		for (std::list<std::pair<TokenType, States>>::iterator it = Transitions.begin(); it != Transitions.end(); ++it)
		{
			if ( it->first == tokenType )
			{
				toState = it->second;
				break;
			}
		}

		if (toState == States::StateIsKeyword) { StateIsKeyword(helper, tokenType, strBuilder); }
		else if (toState == States::StateIsNumber) { StateIsNumber(helper, tokenType, strBuilder); }
		else if (toState == States::StateIsIdentifier) { StateIsIdentifier(helper, tokenType, strBuilder); }
		else if (toState == States::StateIsSeperator) { StateIsSeparator(helper, tokenType, charBuilder); }
		else if (toState == States::StateIsOperator) { StateIsOperator(helper, tokenType, charBuilder); }
		else if (toState == States::StateIsComment) { StateIsComment(helper, tokenType, charBuilder); }
		else if (toState == States::StateIsWhiteSpace) { StateIsWhiteSpace(helper, tokenType, charBuilder); }
		else if (toState == States::StateIsUnknown) { StateIsUnknown(helper, tokenType, charBuilder); }
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
				CurrentToken = TokenType::Identifier;
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
			else if (helper.IsWhiteSpace(charBuilder))
			{
				CurrentToken = TokenType::WhiteSpace;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}
			else
			{
				CurrentToken = TokenType::Unknown;
				StateTransition(helper, CurrentToken, CurrentState, strBuilder, charBuilder);
			}
		}

		End();
	}

	void StateMechanism::StateIsKeyword(Helper helper, TokenType tokenType, std::string input)
	{
		CurrentState = States::StateIsKeyword;
		helper.WritetoFile(input, tokenType);
		StateIs(helper);
	}

	void StateMechanism::StateIsIdentifier(Helper helper, TokenType tokenType, std::string input)
	{
		CurrentState = States::StateIsIdentifier;
		helper.WritetoFile(input, tokenType);
		StateIs(helper);
	}

	void StateMechanism::StateIsNumber(Helper helper, TokenType tokenType, std::string input)
	{
		CurrentState = States::StateIsNumber;
		helper.WritetoFile(input, tokenType);
		StateIs(helper);
	}

	void StateMechanism::StateIsSeparator(Helper helper, TokenType tokenType, char input)
	{
		CurrentState = States::StateIsSeperator;
		helper.WriteToFile(input, tokenType);
		StateIs(helper);
	}

	void StateMechanism::StateIsOperator(Helper helper, TokenType tokenType, char input)
	{
		CurrentState = States::StateIsOperator;
		helper.WriteToFile(input, tokenType);
		StateIs(helper);
	}

	void StateMechanism::StateIsComment(Helper helper, TokenType tokenType, char input)
	{
		CurrentState = States::StateIsComment;
		helper.WriteToFile(input, tokenType);
		StateIs(helper);
	}

	void StateMechanism::StateIsWhiteSpace(Helper helper, TokenType tokenType, char input)
	{
		CurrentState = States::StateIsWhiteSpace;
		helper.WriteToFile(input, tokenType);
		StateIs(helper);
	}

	void StateMechanism::StateIsUnknown(Helper helper, TokenType tokenType, char input)
	{
		CurrentState = States::StateIsUnknown;
		helper.WriteToFile(input, tokenType);
		StateIs(helper);
	}

	void StateMechanism::End() {}

	std::string StateMechanism::GetCurrentState() {
		if (CurrentState == States::StateIs) { return "InitialState"; }
		else if (CurrentState == States::StateIsComment) { return "CommentState"; }
		else if (CurrentState == States::StateIsIdentifier) { return "IdentifierState"; }
		else if (CurrentState == States::StateIsKeyword) { return "KeywordState"; }
		else if (CurrentState == States::StateIsNumber) { return "NumberState"; }
		else if (CurrentState == States::StateIsOperator) { return "OperatorState"; }
		else if (CurrentState == States::StateIsSeperator) { return "SeparatorState"; }
		else if (CurrentState == States::StateIsWhiteSpace) { return "WhiteSpaceState"; }
		else { return "UnknownState"; }
	}
// namespace StateMechanism
