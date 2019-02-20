/***
   prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

void getTwoLinesFromFile(std::string file, BigUnsigned &d, BigUnsigned &n)
{
   std::ifstream a_b(file);
   if (a_b.good())
   {
      std::string D;
      std::string N;
      std::getline(a_b, D);

      std::getline(a_b, N);
      d = stringToBigUnsigned(D);
      n = stringToBigUnsigned(N);
   }
}

void print(std::string title, BigUnsigned data)
{
   std::cout << title << ": " << data << std::endl
             << std::endl;
}

int main(int argc, char *argv[])
{
   //Second part of your project starts here
   if (argc != 3 || (argv[1][0] != 's' && argv[1][0] != 'v'))
      std::cout << "wrong format! should be \"a.exe s filename\"";
   else
   {
      std::string filename = argv[2];

      //read the file
      std::streampos begin, end;
      std::ifstream myfile(filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg(0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end - begin;
      //std::cout << "size of the file: " << size << " bytes.\n"; //size of the file

      myfile.seekg(0, std::ios::beg);
      char *memblock = new char[size];
      myfile.read(memblock, size); //read file; it's saved in the char array memblock
      myfile.close();

      // std::string copyOFfile = filename + ".Copy";
      // std::ofstream myfile2(copyOFfile.c_str(), std::ios::binary);
      // myfile2.write(memblock, size); //write to a file
      // myfile2.close();

      std::cout << "memblock: " << memblock << std::endl;
      std::string memblock_sha = sha256(memblock);
      std::cout << "memblock_sha: " << memblock_sha << std::endl;

      BigUnsigned mesAsUnsigned = BigUnsigned(BigUnsignedInABase(memblock_sha, 16));
      print("mesAsUnsigned", mesAsUnsigned);

      if (argv[1][0] == 's')
      {

         BigUnsigned d;
         BigUnsigned n;
         getTwoLinesFromFile("d_n.txt", d, n);

         BigUnsigned sig = modexp(mesAsUnsigned, d, n);
         print("sig", sig);

         std::ofstream sigOFfile(filename + ".signature");
         sigOFfile << bigUnsignedToString(sig) << std::endl;
         sigOFfile.close();
      }
      else
      {
         BigUnsigned e;
         BigUnsigned n;
         getTwoLinesFromFile("e_n.txt", e, n);
         BigUnsigned sig;

         std::ifstream sigFile(filename + ".signature");
         if (sigFile.good())
         {
            std::string sigStr;
            std::getline(sigFile, sigStr);
            sig = stringToBigUnsigned(sigStr);
         }

         print("sig", sig);

         BigUnsigned res = modexp(sig, e, n);

         print("res", res);

         std::cout << "Finally: " << (res == mesAsUnsigned) << std::endl;
      }
      delete[] memblock;
   }
   return 0;
}