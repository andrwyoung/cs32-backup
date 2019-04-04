#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

std::string spacegone(std::string space)
//gets rid of white space
{
	std::string temp = "";
	int length = space.length();
	for(int i = 0; i < length; i++)
	{
		if(space[i] != ' ')
		{
			temp += space[i];
		}
	}

	return temp;
}

bool postfixed(std::string infix, std::string& postfix) 
//converts infix into postfix, and returns if process was succesfful
//this function doesn't check if operator to operand ratio is good
{
	std::stack<std::string> hold; //helps hold values

	std::string infixed = spacegone(infix);

	std::string temp = ""; //holds the postfix string that will be copied later if it's valid
	int length = infixed.length();//length of infixed string

	//makes sure operand to operator ratio is good
	//catches many errors
	int operators = 1;
	int operands = 0;

	if(infixed[0] == '|' || infixed[0] == '&' || infixed[length - 1] == '!' || 
		infixed[length - 1] == '|' || infixed[length - 1] == '&' || infixed[length - 1] == '(') 
	{
		//checks if operands are in ends
		return false;
	}

	for(int i = 0; i < length; i++) //go through each character
	{
		switch(infixed[i])
		{	
			case ' ':
				continue;
			case 'T':
			case 'F':
				temp += infixed.substr(i, 1);

				while(!hold.empty() && hold.top() == "!")
				//! must act on operand immedietly
				{
					temp += "!";
					hold.pop();
				}
				operands++;
				break;
			case '(':
				if(infixed[i + 1] == '&' || infixed[i + 1] == '|' || 
						infixed[i + 1] == ')')
				//very first if statement makes sure we don't walk off string
				//( must be followed up with operand, another ( or !
				{
					return false;
				}
				hold.push(infixed.substr(i, 1));
				break;
			case '!':
				hold.push(infixed.substr(i, 1));
				break;
			case ')':
				if(hold.empty()) 
				//checks for no open parenthesis so while loop is safe
				{
					return false;
				}

				while(hold.top() != "(")
				{	
					temp += hold.top();
					hold.pop();

					if(hold.empty()) 
					//checks if no open parenthesis
					{
						return false;
					}
				}
				hold.pop(); //pop '('
				while(!hold.empty() && hold.top() == "!")
				//pop all those !
				{
					temp += hold.top();
					hold.pop(); 
				}
				break;
			case '|':
			case '&':
				if(infixed[i + 1] == ')' || infixed[i - 1] == '(')
				//very first if statement makes sure we don't walk off string
				//makes sure | and & are not on ends of parenthesis
				{
					return false;
				}



				if(!hold.empty() && hold.top() == "!")
				//can't have ! followed by operator 
				{
					return false; 
				}

				while(!hold.empty() && hold.top() != "(" && infixed.substr(i, 1) >= hold.top())
				{
					temp += hold.top();
					hold.pop();
				}
				hold.push(infixed.substr(i, 1));
				operators++;
				break;
			//case ' ':
			//	break;
			default: //other characters not allowed
				return false;

		}
	}

	while(!hold.empty())
	{
		std::string top = hold.top();

		if(top == "(")
		//checks for loose (
		{
			return false;
		}

		temp += top;
		hold.pop();
	}

	if(operators != operands)
	{
		return false;
	}

	postfix = temp;
	return true;
}

bool postdo(std::string postfix, bool& result)
//evaluates the postfix, and returns if process was successful
//relies on postfixed to catch most errors
{
	std::stack<bool> hold; //helps hold T and Fs
	int length = postfix.length();//length of infixed string

	for(int i = 0; i < length; i++) //go through each character
	{
		if(postfix[i] == 'T')
		{
			hold.push(true);
		}
		else if(postfix[i] == 'F')
		{
			hold.push(false);
		}	
		else 
		{
			bool one;
			bool two;

			switch(postfix[i])
			{
				case '!':
					one = hold.top();
					hold.pop();
					hold.push(!one);
					break;
				case '&':
					two = hold.top();
					hold.pop();
					one = hold.top();
					hold.pop();
					hold.push(one && two);
					break;
				case '|':
					two = hold.top();
					hold.pop();
					one = hold.top();
					hold.pop();
					hold.push(one || two);
					break;
				default:
					return false;
			}
		}
	}

	result = hold.top();
	return true;
}

// int evaluate(std::string infix, std::string& postfix, bool& result)
// {
// 	std::string tempPostfix = "";
// 	if(postfixed(infix, postfix))
// 	{
// 		bool tempResult;
// 		if(postdo(postfix, result))
// 		{
// 			return 0;
// 		}
// 		else
// 		{
// 			return 1;
// 		}
// 	}
// 	else
// 	{
// 		return 1;
// 	}

// }

// int main()
// {
// 	std::string a = "";
//     std::string pf;
//     bool answer;
//     assert(evaluate(" T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
//     assert(evaluate("T|", pf, answer) == 1);
//     assert(evaluate("F  F", pf, answer) == 1);
//     assert(evaluate("TF", pf, answer) == 1);
//     assert(evaluate("()", pf, answer) == 1);
//     assert(evaluate("   T(F |T)", pf, answer) == 1);
//     assert(evaluate("T(&T)", pf, answer) == 1);
//     assert(evaluate("( T &(  F|F) ", pf, answer) == 1);
//     assert(evaluate("",  pf, answer) == 1);
//     assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&|"  &&  !answer);
//     assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
//     assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T" &&  answer);

//     assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0 &&  pf == "TFTT&|F|!&FT&F&!!!|" &&  answer);
//     assert(evaluate("((T|!T)&(F&F))|((!T&F)&T)", pf, answer) == 0  &&  pf == "TT!|FF&&T!F&T&|"  &&  !answer);

//     assert(evaluate("T(&T)", a, answer) == 1);
// 	assert(evaluate("T(F|)", a, answer) == 1);
// 	assert(evaluate("T)", a, answer) == 1);
// 	assert(evaluate("a", a, answer) == 1);
// 	assert(evaluate("!", a, answer) == 1);
// 	assert(evaluate("T | F !", a, answer) == 1);
// 	assert(evaluate("TF&", a, answer) == 1);
// 	assert(evaluate("(!|F)()", a, answer) == 1);
// 	assert(evaluate("(F!|)", a, answer) == 1);
// 	assert(evaluate("()", a, answer) == 1);
// 	assert(evaluate("T()", a, answer) == 1);
// 	assert(evaluate("TT&()", a, answer) == 1);
// 	assert(evaluate("TFFTF", a, answer) == 1);

// 	assert(evaluate("T", a, answer) == 0 && answer);
// 	assert(evaluate("((T))", a, answer) == 0 && answer);
// 	assert(evaluate("F  |  !F & (T&F) ", a, answer) == 0 && !answer);
// 	assert(evaluate("(T&(F|F))", a, answer) == 0 && !answer);
// 	assert(evaluate("(F|(F))", a, answer) == 0 && !answer);
// 	assert(evaluate("(!F)", a, answer) == 0 && answer);
// 	assert(evaluate("(T)&F", a, answer) == 0 && !answer);
// 	assert(evaluate("!!!!T", a, answer) == 0 && answer);

// 	assert(evaluate("!!!!  T!  !!!!T", a, answer) == 1);
// 	assert(evaluate("!! !!T|!! !!!T", a, answer) == 0);// && a == "T!!!!T!!!!!|" && answer);
// 	assert(evaluate("!!!!T", a, answer) == 0 && a == "T!!!!" && answer);
// 	assert(evaluate("T !!!!", a, answer) == 1);
// 	assert(evaluate("T!!!!!!", a, answer) == 1);
// 	assert(evaluate("F  |  !F & (T&F) ", a, answer) == 0 && a == "FF!TF&&|" && !answer);
// 	assert(evaluate("T|  F", a, answer) == 0 && a == "TF|"  &&  answer);
// 	assert(evaluate(" F  ", a, answer) == 0 && a == "F" && !answer);
// 	assert(evaluate("((T))", a, answer) == 0 && a == "T"  &&  answer);
// 	assert(evaluate("      F    ", a, answer) == 0 && a == "F");
// 	assert(evaluate("  ( (T))", a, answer) == 0 && a == "T");
// 	assert(evaluate(" ", a, answer) == 1);
// 	assert(evaluate("T|F|T", a, answer) == 0 && a == "TF|T|" && answer);
// 	assert(evaluate("T|(F|T)", a, answer) == 0 && a == "TFT||" && answer);
// 	assert(evaluate("(   )" , a, answer) == 1);
// 	assert(evaluate("TT", a, answer) == 1);
// 	assert(evaluate("F      F", a, answer) == 1);
// 	assert(evaluate("T(F|T)", a, answer) == 1);
// 	assert(evaluate("T| F", a, answer) == 0 && a == "TF|");
// 	assert(evaluate("T| |F", a, answer) == 1);
// 	assert(evaluate("T&|F", a, answer) == 1);
// 	assert(evaluate("T| ", a, answer) == 1);
// 	assert(evaluate("T|T|", a, answer) == 1);
// 	assert(evaluate("T|TTT", a, answer) == 1);
// 	assert(evaluate("T|( T&F|T)", a, answer) == 0);
// 	assert(evaluate("T!T", a, answer) == 1);
// 	assert(evaluate("T|!T", a, answer) == 0);
// 	assert(evaluate("!(T|F)", a, answer) == 0);
// 	assert(evaluate("!T|!F)", a, answer) == 1);
// 	assert(evaluate("(!T|!F)", a, answer) == 0);
// 	assert(evaluate("(!T|!F", a, answer) == 1);
// 	assert(evaluate("(!T|!F))", a, answer) == 1);
// 	assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F) ", a, answer) == 0 && a == "TFTT&|F|!&FT&F&!!!|" && answer) ;
// 	assert(evaluate(" T|F&F ", a, answer) == 0);
// 	assert(evaluate("  !F|T ", a, answer) == 0);
// 	assert(evaluate("!(F|T) ", a, answer) == 0);
// 	assert(evaluate("T & !F ", a, answer) == 0);
// 	assert(evaluate("T&(F) ", a, answer) == 0 && a == "TF&" && !answer);
// 	assert(evaluate("((T|!T)&(F&F))|((!T&F)&T)", a, answer) == 0 && a == "TT!|FF&&T!F&T&|" && !answer);



// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("  )", postfix, result)==1);//no unclose parens
// 		assert(evaluate(")(", postfix, result) == 1);//NONE OF THIS EITHER
// 		assert(evaluate("asd", postfix, result) == 1);//no wierd values
// 		assert(evaluate("!()", postfix, result) == 1);
// 		assert(evaluate("(&T|F)", postfix, result) == 1);
// 		assert(evaluate("!FT", postfix, result) == 1);
// 		assert(evaluate("T|T &!F!T!F", postfix, result) == 1);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("T|F", postfix, result) == 0 && result == true);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("T&F", postfix, result) == 0 && result == false);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("T&&T", postfix, result) == 1);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("!F", postfix, result) == 0 && result == true);
// 	}
// 	{
// 		bool result;
// 		string postfix; 
// 		assert(evaluate("T& ( F)", postfix, result) == 0 && result == false);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("T & !F", postfix, result) == 0 && result == true);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("!(T|F)", postfix, result) == 0 && result == false);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("! F |  T", postfix, result) == 0 &&  result == true);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate(" ( T  & ) F  ", postfix, result) == 1);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("(T &F    )F ", postfix, result) == 1);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate(" (T& F|) F ", postfix, result) == 1);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate(" T |F &F", postfix, result) == 0 && result == true);
// 	}
// 	{
// 		bool result;
// 		string postfix; 
// 		assert(evaluate(" T&! ( F|T&T| F)|!!!(F  &T&F)", postfix, result) == 0 && result == true);
// 	}
// 	{
// 		bool result;
// 		string postfix;
// 		assert(evaluate("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!T", postfix, result) == 0);//this is absurd but... has to work
// 	}
// 	std::cout << "All Tests Succeeded!" << std::endl;

//  	assert(evaluate("TT&(   )", a, answer) == 1);

// 	return 0;
	  
// }