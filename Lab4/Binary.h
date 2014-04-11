/* Assignment4
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day
*/

#ifndef Lab4_Binary_h
#define Lab4_Binary_h

#include "Token.h"
#include "common.h"

using namespace std;


class Binary
{
	public:
  		Binary();
		~Binary();

 		void add(Token *token, int line);
		void destroy();
		void print();

	private:
  		void adder(Token *token, Token *Noder, int line);
  		void destroyer(Token *Noder);
  		void printer(Token *Noder);

		Token *root;
};

#endif
