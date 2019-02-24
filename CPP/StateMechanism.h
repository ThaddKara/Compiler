#ifndef STATEMECHANISM_H
#define STATEMECHANISM_H


#include <iostream>
#include <list>

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
};
class Helper
{
private:
	std::list<char> PreParse;
	std::list<std::pair<TokenType, std::string>> PostParse;

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
};

class StateMechanism
{
private:
	States CurrentState;
	TokenType CurrentToken;

public:
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
};
#endif // !STATEMECHANISM END