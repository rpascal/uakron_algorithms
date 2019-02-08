// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

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

BigUnsigned modExp(BigUnsigned x, BigUnsigned y, BigUnsigned m)
{
   if (y == 0)
   {
      return BigUnsigned(1);
   }
   else
   {
      BigUnsigned z = modExp(x, y / 2, m);
      if (y % 2 == 0)
      {
         return (z * z % m);
      }
      else
      {
         return (x * z * z % m);
      }
   }
}

bool fermatTest(BigUnsigned N)
{
   BigUnsigned a1(1);
   BigUnsigned a2(2);
   return (modExp(a1, N - 1, N) == 1) && (modExp(a2, N - 1, N) == 1);
}

BigUnsigned getLargeRandomPrime()
{
   BigUnsigned x = getRandomNumber(155);
   while (!fermatTest(x))
   {
      x = getRandomNumber(155);
   }
   return x;
}

BigUnsigned getE(BigUnsigned p, BigUnsigned q)
{
   BigUnsigned theta = (p - 1) * (q - 1);
   if (theta % 2 == 0)
   {
      theta++;
   }

   BigUnsigned e = getRandomNumber(20);
   while (!isRelativelyPrime(e, theta))
   {
      e = getRandomNumber(20);
   }
   return e;
}

int main()
{
   /* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
   try
   {

      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned p = getLargeRandomPrime();
      std::cout << p << std::endl;
      BigUnsigned q = getLargeRandomPrime();
      std::cout << q << std::endl;

      BigUnsigned e = getE(p, q);
      std::cout << e << std::endl;
   }
   catch (char const *err)
   {
      std::cout << "The library threw an exception:\n"
                << err << std::endl;
   }

   return 0;
}