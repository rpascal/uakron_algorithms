/***
   prepared for CS435 Project 1 part 2
   Ryan Pascal
   2932732
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

/*
   This function will read a file that has two lines
   First line will be put into a variable
   Second line b
*/
void getTwoLinesFromFile(std::string file, BigUnsigned &a, BigUnsigned &b)
{
   std::ifstream a_b(file);
   if (a_b.good())
   {
      std::string A;
      std::string B;
      std::getline(a_b, A);

      std::getline(a_b, B);
      a = stringToBigUnsigned(A);
      b = stringToBigUnsigned(B);
   }
}

BigUnsigned getMessageData(std::string filename)
{
   //read the file
   std::streampos begin,
       end;
   std::ifstream myfile(filename.c_str(), std::ios::binary);
   begin = myfile.tellg();
   myfile.seekg(0, std::ios::end);
   end = myfile.tellg();
   std::streampos size = end - begin;

   myfile.seekg(0, std::ios::beg);
   char *memblock = new char[size];
   myfile.read(memblock, size); //read file; it's saved in the char array memblock
   myfile.close();

   std::string memblock_sha = sha256(memblock);
   delete[] memblock;
   return BigUnsigned(BigUnsignedInABase(memblock_sha, 16));
}

int main(int argc, char *argv[])
{
   //Second part of your project starts here
   if (argc != 3 || (argv[1][0] != 's' && argv[1][0] != 'v'))
      std::cout << "wrong format! should be \"a.exe s filename\"";
   else
   {
      std::string filename = argv[2];
      std::string filenameSignature = filename + ".signature";

      BigUnsigned messageAsNumber = getMessageData(filename);

      if (argv[1][0] == 's')
      {
         BigUnsigned d;
         BigUnsigned n;
         getTwoLinesFromFile("d_n.txt", d, n);

         BigUnsigned sig = modexp(messageAsNumber, d, n);

         // Write to signature file
         std::ofstream sigOFfile(filenameSignature);
         sigOFfile << bigUnsignedToString(sig) << std::endl;
         sigOFfile.close();
      }
      else
      {
         BigUnsigned e;
         BigUnsigned n;
         getTwoLinesFromFile("e_n.txt", e, n);

         BigUnsigned sig;

         // Just to be safe it signed first
         try
         {
            std::ifstream sigFile(filenameSignature);
            if (sigFile.good())
            {
               std::string sigStr;
               std::getline(sigFile, sigStr);
               sig = stringToBigUnsigned(sigStr);
            }
         }
         catch (const std::exception &e)
         {
            std::cout << "Could not open signature file... Exitting...\n";
            return 0;
         }

         BigUnsigned encrypt = modexp(sig, e, n);

         if (encrypt == messageAsNumber)
         {
            std::cout << "Verification succeeded: " << filename << " authentic.\n";
         }
         else
         {
            std::cout << "Verification failed: " << filename << " modified.\n";
         }
      }
   }
   return 0;
}