/***
   prepared for CS435 Project 1 part 1
   Ryan Pascal
   2932732
**/

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

bool isRelativelyPrime(BigUnsigned x, BigUnsigned y);
BigUnsigned getRandomNumber(BigUnsigned k);
bool fermatTest(BigUnsigned N);
BigUnsigned getLargeRandomPrime();
BigUnsigned getE(BigUnsigned phi);

int main()
{
   srand(time(NULL));

   /* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
   try
   {
      BigUnsigned p = getLargeRandomPrime();
      BigUnsigned q = getLargeRandomPrime();

      BigUnsigned n = p * q;

      BigUnsigned phi = (p - 1) * (q - 1);

      BigUnsigned e = getE(phi);

      BigUnsigned d = modinv(e, phi);

      // Adding p and q to file
      std::ofstream p_q("p_q.txt");
      p_q << p << std::endl;
      p_q << q << std::endl;
      p_q.close();

      // Adding e and n to file
      std::ofstream e_n("e_n.txt");
      e_n << e << std::endl;
      e_n << n << std::endl;
      e_n.close();

      // Adding d and n to file
      std::ofstream d_n("d_n.txt");
      d_n << d << std::endl;
      d_n << n << std::endl;
      d_n.close();
   }
   catch (char const *err)
   {
      std::cout << "The library threw an exception:\n"
                << err << std::endl;
   }

   return 0;
}

bool isRelativelyPrime(BigUnsigned x, BigUnsigned y)
{
   return gcd(x, y) == 1;
}

BigUnsigned getRandomNumber(BigUnsigned k)
{
   BigUnsigned x = BigUnsigned(1);
   for (int i = 0; k >= i; i++)
   {
      x = x * 10 + rand();
   }
   return x;
}

bool fermatTest(BigUnsigned N)
{
   BigUnsigned a1(1);
   BigUnsigned a2(2);
   return (modexp(a1, N - 1, N) == 1) && (modexp(a2, N - 1, N) == 1);
}

BigUnsigned getLargeRandomPrime()
{
   BigUnsigned x = getRandomNumber(155);
   while (!fermatTest(x))
   {
      x = getRandomNumber(155);
   }
   if (x % 2 == 0)
   {
      x++;
   }
   return x;
}

BigUnsigned getE(BigUnsigned phi)
{

   BigUnsigned e = getRandomNumber(25);
   while (!isRelativelyPrime(e, phi))
   {
      e = getRandomNumber(25);
   }
   if (e % 2 == 0)
   {
      e++;
   }
   return e;
}