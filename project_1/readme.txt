Ryan Pascal 2932732
Algorithms Project 1

Part 1
    The purpose of part 1 was to implement rsa as discussed within class.
    For the encription various numbers are generated to be used for keys. 
        p and q are generated using the function getLargeRandomPrime()
        n = p*q
        Once p and q are found phi is calculated by phi(n) = (p-1)(q-1)
        e is found by using the getE(BigUnsigned phi) function which will be realitivly prime to phi\
        d is the modular inverse of e
    Once all these numbers are found they are saved into files: p_q.txt, e_n.txt, and d_n.txt

    This part of the project only includes rsa435.cc file and can be run directly from that file.
        Running: ./rsa435
        
Part 2
    The purpose of part 2 is to sign and verify a file.
    sha256 is used to hash the input file and then that is converted to a number by BigInteger library.
    The files e_n.txt, and d_n.txt are needed within the same directory project is ran in.
    When signing d and n are used.
    When verifying e and n are used. 
    Once a file is signed it will be saved in the following format: <filename.extension>.signature
    When verifying the generated file will be used. This file will be compared against the original.
        If they do not match the original file has been modified.
        If they do match the original is authentic.

    This part of the project only includes messageDigest435.cpp and can be run directly from that file 
        To sign:   ./messageDigest435 s file.txt
        To verify: ./messageDigest435 v file.txt
