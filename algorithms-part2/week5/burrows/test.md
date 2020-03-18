See the Assessment Guide for information on how to interpret this report.

ASSESSMENT SUMMARY

Compilation:  PASSED
API:          PASSED

Spotbugs:     FAILED (2 warnings)
PMD:          FAILED (2 warnings)
Checkstyle:   FAILED (0 errors, 3 warnings)

Correctness:  53/68 tests passed
Memory:       10/10 tests passed
Timing:       158/159 tests passed

Aggregate score: 86.64%
[Compilation: 5%, API: 5%, Spotbugs: 0%, PMD: 0%, Checkstyle: 0%, Correctness: 60%, Memory: 10%, Timing: 20%]

ASSESSMENT DETAILS

The following files were submitted:
----------------------------------
1.7K Mar 17 06:36 BurrowsWheeler.java
1.9K Mar 17 06:36 CircularSuffixArray.java
2.0K Mar 17 06:36 MoveToFront.java


********************************************************************************
*  COMPILING                                                                    
********************************************************************************


% javac11 CircularSuffixArray.java
*-----------------------------------------------------------

% javac11 BurrowsWheeler.java
*-----------------------------------------------------------

% javac11 MoveToFront.java
*-----------------------------------------------------------


================================================================


Checking the APIs of your programs.
*-----------------------------------------------------------
CircularSuffixArray:

BurrowsWheeler:

MoveToFront:

================================================================


********************************************************************************
*  CHECKING STYLE AND COMMON BUG PATTERNS                                       
********************************************************************************


% spotbugs *.class
*-----------------------------------------------------------
M D DLS_DEAD_LOCAL_STORE DLS: Assigns a value to the local variable 'row' but that value is never used.  At BurrowsWheeler.java:[line 32]
H D DLS_DEAD_LOCAL_STORE DLS: Assigns a value to the local variable 'next' but that value is never used.  At BurrowsWheeler.java:[line 34]
Warnings generated: 2


================================================================


% pmd .
*-----------------------------------------------------------
BurrowsWheeler.java:32: Avoid unused local variables, such as 'row'. [UnusedLocalVariable]
CircularSuffixArray.java:64: The method body is empty. If this is your intent, document it with a comment. [UncommentedEmptyMethodBody]
PMD ends with 2 warnings.


================================================================


% checkstyle *.java
*-----------------------------------------------------------

% custom checkstyle checks for CircularSuffixArray.java
*-----------------------------------------------------------

% custom checkstyle checks for BurrowsWheeler.java
*-----------------------------------------------------------
[WARN] BurrowsWheeler.java:15:9: You should not need to use the 'StringBuilder' data type in this program. [Design]
[WARN] BurrowsWheeler.java:15:28: You should not need to create objects of type 'java.lang.StringBuilder' in this program. [Design]
Checkstyle ends with 0 errors and 2 warnings.

% custom checkstyle checks for MoveToFront.java
*-----------------------------------------------------------
[WARN] MoveToFront.java:7:1: The constant '256' appears more than once. Define a constant variable (such as 'EXTENDED_ASCII') to hold the constant '256'. [NumericLiteralCount]
Checkstyle ends with 0 errors and 1 warning.


================================================================


********************************************************************************
*  TESTING CORRECTNESS
********************************************************************************

Testing correctness of CircularSuffixArray
*-----------------------------------------------------------
Running 15 total tests.

Test 1: check index() and length() with random binary strings
  * length = 10
  * length = 100
  * length = 1000
==> passed

Test 2: check index() and length() with random uppercase strings
  * length = 10
  * length = 100
  * length = 1000
==> passed

Test 3: check index() and length() with random ASCII strings
  * length = 10
  * length = 100
  * length = 1000
==> passed

Test 4: check index() and length() with random extended ASCII strings
  * length = 10
  * length = 100
  * length = 1000
==> passed

Test 5: check index() and length() with strings from text files
  * cadabra.txt
  * amendments.txt
  * moby1.txt
  * dickens1000.txt
==> passed

Test 6: check index() and length() with strings from binary files
  * us.gif
  * CS_bricks.jpg
  * rand1K.bin
==> passed

Test 7: check index() and length() with random strings of length 0, 1, and 2
  * length = 0
  * length = 1
  * length = 2
==> passed

Test 8: check that index() throws an exception when argument is out of bounds
  * string of length 10
  * string of length 100
  * string of length 2
  * string of length 1
  * string of length 0
==> passed

Test 9: check that constructor throws an exception when argument is null
==> passed

Test 10: check that two CircularSuffixArray objects can be created at the same time
  * cadabra.txt and amendments.txt
  * amendments.txt and cadabra.txt
  * dickens1000.txt and cadabra.txt
==> passed

Test 11: check that CircularSuffixArray is immutable
  * string = "QOQTMQAUVOGYMBZKAXSPYWBBKWAHVF"
  * string = "AAABABAAABBBBABAAAABABBAABBBAA"
  * string = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
  * string = hex representation: c6 4f 05 39 5f 4f 78 2e b2 4c c8 4e f4 fe 7d 
==> passed

Test 12: check index() and length() with corner-case strings
  * a.txt
  * nomatch.txt
  * zebra.txt
  * alphanum.txt
==> passed

Test 13: check index() and length() with strings that are nontrivial circular
         that are nontrivial circular suffixes of themselves
  * stars.txt
  * couscous.txt
==> passed

Test 14: check index() and length() with unary strings
  * length 10 string over unary alphabet
  * length 100 string over unary alphabet
  * length 1000 string over unary alphabet
==> passed

Test 15: check index() and length() with random strings
         that are nontrivial circular suffixes of themselves
  * length 2 string over binary alphabet, repeated 2 times
  * length 2 string over binary alphabet, repeated 10 times
  * length 5 string over binary alphabet, repeated 2 times
  * length 5 string over binary alphabet, repeated 3 times
  * length 5 string over binary alphabet, repeated 5 times
  * length 7 string over uppercase alphabet, repeated 2 times
  * length 7 string over uppercase alphabet, repeated 3 times
  * length 7 string over uppercase alphabet, repeated 5 times
==> passed

Total: 15/15 tests passed!


================================================================
Testing correctness of MoveToFront
*-----------------------------------------------------------
Running 25 total tests.

Test 1a: check main() on text files
  * java MoveToFront - < abra.txt
  * java MoveToFront - < zebra.txt
  * java MoveToFront - < amendments.txt
  * java MoveToFront - < aesop.txt
==> passed

Test 1b: check main() on text files
  * java MoveToFront + < abra.txt.mtf
  * java MoveToFront + < zebra.txt.mtf
  * java MoveToFront + < amendments.txt.mtf
  * java MoveToFront + < aesop.txt.mtf
==> passed

Test 2a: check parsing of argument "-" in main() on text files
  * java MoveToFront - < abra.txt
  * java MoveToFront - < zebra.txt
  * java MoveToFront - < amendments.txt
  * java MoveToFront - < aesop.txt
==> passed

Test 2b: check parsing of argument "+" in main() on text files
  * java MoveToFront + < abra.txt.mtf
  * java MoveToFront + < zebra.txt.mtf
  * java MoveToFront + < amendments.txt.mtf
  * java MoveToFront + < aesop.txt.mtf
==> passed

Test 3a: check that main() is consistent with encode() on text files
  * abra.txt
  * zebra.txt
  * amendments.txt
  * aesop.txt
==> passed

Test 3b: check that main() is consistent with decode() on text files
  * abra.txt.mtf
  * zebra.txt.mtf
  * amendments.txt.mtf
  * aesop.txt.mtf
==> passed

Test 4a: check encode() on text files
  * abra.txt
  * zebra.txt
  * amendments.txt
  * aesop.txt
  * stars.txt
  * alphanum.txt
  * a.txt
==> passed

Test 4b: check encode() on binary files
  * us.gif
  * CS_bricks.jpg
  * rand10K.bin
==> passed

Test 4c: check encode() on random inputs
  * 10 random characters from { A } alphabet
  * 10 random characters from { A, B } alphabet
  * 10 random characters from { A, T, C, G } alphabet
  * 10 random characters from uppercase letter alphabet
  * 1000 random characters from { A } alphabet
  * 1000 random characters from { A, B } alphabet
  * 1000 random characters from { A, T, C, G } alphabet
  * 1000 random characters from uppercase letter alphabet
==> passed

Test 4d: check encode() on more random inputs
  * 1000 random characters from ASCII alphabet 
  * 1000 random characters from extended ASCII alphabet
  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
==> passed

Test 5a: check decode() on move-to-front-encoded text files
  * abra.txt.mtf
  * zebra.txt.mtf
  * amendments.txt.mtf
  * aesop.txt.mtf
  * stars.txt.mtf
  * alphanum.txt.mtf
  * a.txt.mtf
==> passed

Test 5b: check decode() on move-to-front encoded binary files
  * us.gif.mtf
  * CS_bricks.jpg.mtf
  * rand10K.bin.mtf
==> passed

Test 5c: check decode() on random inputs
  * 10 random characters from { A } alphabet
  * 10 random characters from { A, B } alphabet
  * 10 random characters from { A, T, C, G } alphabet
  * 10 random characters from uppercase letter alphabet
  * 1000 random characters from { A } alphabet
  * 1000 random characters from { A, B } alphabet
  * 1000 random characters from { A, T, C, G } alphabet
  * 1000 random characters from uppercase letter alphabet
==> passed

Test 5d: check decode() on more random inputs
  * 1000 random characters from ASCII alphabet 
  * 1000 random characters from extended ASCII alphabet
  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
==> passed

Test 5e: check decode() on random inputs
         that were encoded with move-to-front
  * 10 random characters from { A } alphabet
  * 10 random characters from { A, B } alphabet
  * 10 random characters from { A, T, C, G } alphabet
  * 10 random characters from uppercase letter alphabet
  * 1000 random characters from { A } alphabet
  * 1000 random characters from { A, B } alphabet
  * 1000 random characters from { A, T, C, G } alphabet
  * 1000 random characters from uppercase letter alphabet
==> passed

Test 5f: check decode() on more random inputs
         that were encoded with move-to-front
  * 1000 random characters from ASCII alphabet 
  * 1000 random characters from extended ASCII alphabet
  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
==> passed

Test 6a: check whether decode(encode()) = original on text files
  * abra.txt
  * zebra.txt
  * amendments.txt
  * aesop.txt
  * stars.txt
  * alphanum.txt
  * a.txt
==> passed

Test 6b: check whether decode(encode()) = original on binary files
  * us.gif
  * CS_bricks.jpg
  * rand10K.bin
==> passed

Test 6c: check that decode(encode()) = original on random inputs
  * 10 random characters from { A } alphabet
  * 10 random characters from { A, B } alphabet
  * 10 random characters from { A, T, C, G } alphabet
  * 10 random characters from uppercase letter alphabet
  * 100 random characters from { A } alphabet
  * 1000 random characters from { A, B } alphabet
  * 1000 random characters from { A, T, C, G } alphabet
  * 1000 random characters from uppercase letter alphabet
==> passed

Test 6d: check that decode(encode()) = original on random inputs
  * 1000 random characters from ASCII alphabet 
  * 1000 random characters from extended ASCII alphabet
  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
==> passed

Test 7a: check that encode() calls either close() or flush()
  * amendments.txt
  * aesop.txt
==> passed

Test 7b: check that decode() calls either close() or flush()
  * amendments.txt.mtf
  * aesop.txt.mtf
==> passed

Test 8a: check encode() on large files
  * rand100K.bin
  * world192.txt
==> passed

Test 8b: check decode() on large files
  * rand100K.bin.mtf
  * world192.txt.mtf
==> passed

Test 8c: check whether decode(encode()) = original on large files
  * rand100K.bin
  * world192.txt
==> passed


Total: 25/25 tests passed!


================================================================
********************************************************************************
*  TESTING CORRECTNESS (substituting reference CircularSuffixArray)
********************************************************************************

Testing correctness of BurrowsWheeler
*-----------------------------------------------------------
Running 28 total tests.

Test 1a: check main() on text files
  * java BurrowsWheeler - < abra.txt
  * java BurrowsWheeler - < zebra.txt
  * java BurrowsWheeler - < cadabra.txt
  * java BurrowsWheeler - < amendments.txt
==> passed

Test 1b: check main() on text files
  * java BurrowsWheeler + < abra.txt.bwt
    - student   length = 0
    - reference length = 12
    - student:   
    - reference: 41 42 52 41 43 41 44 41 42 52 41 21 

  * java BurrowsWheeler + < zebra.txt.bwt
    - student   length = 0
    - reference length = 5
    - student:   
    - reference: 7a 65 62 72 61 

  * java BurrowsWheeler + < cadabra.txt.bwt
    - student   length = 0
    - reference length = 12
    - student:   
    - reference: 43 41 44 41 42 52 41 21 41 42 52 41 

  * java BurrowsWheeler + < amendments.txt.bwt
    - student   length = 0
    - reference length = 18369
    - student:   
    - reference: 41 72 74 69 63 6c 65 20 49 .. 65 72 76 65 6e 65 64 2e 0a 

==> FAILED

Test 2a: check parsing of argument "-" in main() on text files
  * java BurrowsWheeler - < abra.txt
  * java BurrowsWheeler - < zebra.txt
  * java BurrowsWheeler - < cadabra.txt
  * java BurrowsWheeler - < amendments.txt
==> passed

Test 2b: check parsing of argument "+" in main() on text files
  * java BurrowsWheeler + < abra.txt.bwt
  * java BurrowsWheeler + < zebra.txt.bwt
  * java BurrowsWheeler + < cadabra.txt.bwt
  * java BurrowsWheeler + < amendments.txt.bwt
==> passed

Test 3a: check that main() is consistent with transform() on text files
  * abra.txt
  * zebra.txt
  * cadabra.txt
  * amendments.txt
==> passed

Test 3b: check that main() is consistent with inverseTransform() on text files
  * abra.txt.bwt
  * zebra.txt.bwt
  * cadabra.txt.bwt
  * amendments.txt.bwt
==> passed

Test 4a: check transform() on text files
  * abra.txt
  * zebra.txt
  * cadabra.txt
  * amendments.txt
==> passed

Test 4b: check transform() on corner-case text files
  * alphanum.txt
  * a.txt
==> passed

Test 4c: check transform() on binary files
  * us.gif
  * CS_bricks.jpg
  * rand10K.bin
==> passed

Test 4d: check transform() on random inputs
  * 10 random characters from binary alphabet
  * 10 random characters from DNA alphabet
  * 10 random characters from uppercase alphabet
  * 1000 random characters from binary alphabet
  * 1000 random characters from DNA alphabet
  * 1000 random characters from uppercase alphabet
==> passed

Test 4e: check transform() on more random inputs
  * 1000 random characters from ASCII alphabet 
  * 1000 random characters from extended ASCII alphabet
  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
==> passed

Test 4f: check tranform() on random inputs that are circular
         shifts of themselves
  * 5 random strings from unary alphabet
  * 5 random strings from binary alphabet
  * 5 random strings from DNA alphabet
  * 5 random strings from uppercase alphabet
==> passed

Test 5a: check inverseTransform() on text files
  * abra.txt.bwt
    - student   length = 0
    - reference length = 12
    - student:   
    - reference: 41 42 52 41 43 41 44 41 42 52 41 21 

  * zebra.txt.bwt
    - student   length = 0
    - reference length = 5
    - student:   
    - reference: 7a 65 62 72 61 

  * cadabra.txt.bwt
    - student   length = 0
    - reference length = 12
    - student:   
    - reference: 43 41 44 41 42 52 41 21 41 42 52 41 

  * amendments.txt.bwt
    - student   length = 0
    - reference length = 18369
    - student:   
    - reference: 41 72 74 69 63 6c 65 20 49 .. 65 72 76 65 6e 65 64 2e 0a 

==> FAILED

Test 5b: check inverseTransform() on corner-case text files
  * alphanum.txt.bwt
    - student   length = 0
    - reference length = 36
    - student:   
    - reference: 61 62 63 64 65 66 67 68 69 .. 31 32 33 34 35 36 37 38 39 

  * a.txt.bwt
    - student   length = 0
    - reference length = 1
    - student:   
    - reference: 61 

  * stars.txt.bwt
    - student   length = 0
    - reference length = 13
    - student:   
    - reference: 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 

  * couscous.txt.bwt
    - student   length = 0
    - reference length = 8
    - student:   
    - reference: 63 6f 75 73 63 6f 75 73 

==> FAILED

Test 5c: check inverseTransform() on binary files
  * us.gif.bwt
    - student   length = 0
    - reference length = 12400
    - student:   
    - reference: 47 49 46 38 39 61 8e 01 01 .. 7f 03 1e 38 cc 41 00 00 3b 

  * CS_bricks.jpg.bwt
    - student   length = 0
    - reference length = 24567
    - student:   
    - reference: ff d8 ff e1 00 16 45 78 69 .. 46 8d 01 a3 46 8d 07 ff d9 

  * rand10K.bin.bwt
    - student   length = 0
    - reference length = 10000
    - student:   
    - reference: 1a de 9d f2 73 73 0c 05 e1 .. 46 04 ae 11 4f d4 bc 2d b4 

==> FAILED

Test 5d: check inverseTransform() of transform() on random inputs
  * 10 random characters from unary alphabet
    - student   length = 0
    - reference length = 10
    - student:   
    - reference: 41 41 41 41 41 41 41 41 41 41 

    - failed on trial 1 of 2
    - input = 'AAAAAAAAAA'

  * 10 random characters from binary alphabet
    - student   length = 0
    - reference length = 10
    - student:   
    - reference: 42 42 41 42 42 42 42 41 42 42 

    - failed on trial 1 of 100
    - input = 'BBABBBBABB'

  * 10 random characters from DNA alphabet
    - student   length = 0
    - reference length = 10
    - student:   
    - reference: 47 43 43 54 54 41 41 43 47 43 

    - failed on trial 1 of 100
    - input = 'GCCTTAACGC'

  * 10 random characters from uppercase alphabet
    - student   length = 0
    - reference length = 10
    - student:   
    - reference: 49 57 4c 56 51 41 46 48 4d 5a 

    - failed on trial 1 of 100
    - input = 'IWLVQAFHMZ'

  * 100 random characters from unary alphabet
    - student   length = 0
    - reference length = 100
    - student:   
    - reference: 41 41 41 41 41 41 41 41 41 .. 41 41 41 41 41 41 41 41 41 

    - failed on trial 1 of 2

  * 1000 random characters from binary alphabet
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 41 41 41 42 42 41 42 41 41 .. 41 41 41 41 41 41 41 42 42 

    - failed on trial 1 of 100

  * 1000 random characters from DNA alphabet
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 54 41 47 41 47 47 43 43 54 .. 43 54 43 41 41 43 43 43 54 

    - failed on trial 1 of 100

  * 1000 random characters from uppercase alphabet
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 5a 4b 4e 55 51 4b 44 4a 47 .. 4e 4f 51 4c 50 56 58 49 4b 

    - failed on trial 1 of 100

==> FAILED

Test 5e: check inverseTransform() of transform() on more random inputs
  * 1000 random characters from ASCII alphabet 
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 0e 61 1b 49 24 6a 28 28 7d .. 38 60 33 15 36 29 5e 7a 3b 

    - failed on trial 1 of 100

  * 1000 random characters from extended ASCII alphabet
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: a2 cd d2 df ec 2f 99 9a 26 .. 19 a4 98 43 7f 23 9d c9 82 

    - failed on trial 1 of 100

  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 82 d7 9c 24 ca e7 f2 b9 6f .. e2 75 51 96 53 a5 e5 1c 1e 

    - failed on trial 1 of 100

  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 4f 3f 0f c4 28 6d d6 82 51 .. 70 b0 a7 6c 9b 93 03 cc fa 

    - failed on trial 1 of 100

==> FAILED

Test 6a: check that inverseTransform(transform()) = original on text files
  * abra.txt
    - student   length = 0
    - reference length = 12
    - student:   
    - reference: 41 42 52 41 43 41 44 41 42 52 41 21 

  * zebra.txt
    - student   length = 0
    - reference length = 5
    - student:   
    - reference: 7a 65 62 72 61 

  * cadabra.txt
    - student   length = 0
    - reference length = 12
    - student:   
    - reference: 43 41 44 41 42 52 41 21 41 42 52 41 

  * amendments.txt
    - student   length = 0
    - reference length = 18369
    - student:   
    - reference: 41 72 74 69 63 6c 65 20 49 .. 65 72 76 65 6e 65 64 2e 0a 

==> FAILED

Test 6b: check that inverseTransform(transform()) = original on corner-case text files
  * alphanum.txt
    - student   length = 0
    - reference length = 36
    - student:   
    - reference: 61 62 63 64 65 66 67 68 69 .. 31 32 33 34 35 36 37 38 39 

  * a.txt
    - student   length = 0
    - reference length = 1
    - student:   
    - reference: 61 

  * stars.txt
    - student   length = 0
    - reference length = 13
    - student:   
    - reference: 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 2a 

  * couscous.txt
    - student   length = 0
    - reference length = 8
    - student:   
    - reference: 63 6f 75 73 63 6f 75 73 

==> FAILED

Test 6c: check that inverseTransform(transform()) = original on binary files
  * us.gif
    - student   length = 0
    - reference length = 12400
    - student:   
    - reference: 47 49 46 38 39 61 8e 01 01 .. 7f 03 1e 38 cc 41 00 00 3b 

  * CS_bricks.jpg
    - student   length = 0
    - reference length = 24567
    - student:   
    - reference: ff d8 ff e1 00 16 45 78 69 .. 46 8d 01 a3 46 8d 07 ff d9 

  * rand10K.bin
    - student   length = 0
    - reference length = 10000
    - student:   
    - reference: 1a de 9d f2 73 73 0c 05 e1 .. 46 04 ae 11 4f d4 bc 2d b4 

==> FAILED

Test 6d: check that inverseTransform(tranform()) = original on random inputs
  * 10 random characters from binary alphabet
    - student   length = 0
    - reference length = 10
    - student:   
    - reference: 42 42 41 42 42 41 42 42 41 42 

    - failed on trial 1 of 100
    - input = 'BBABBABBAB'

  * 10 random characters from DNA alphabet
    - student   length = 0
    - reference length = 10
    - student:   
    - reference: 54 41 41 54 41 41 43 54 41 54 

    - failed on trial 1 of 100
    - input = 'TAATAACTAT'

  * 10 random characters from uppercase alphabet
    - student   length = 0
    - reference length = 10
    - student:   
    - reference: 54 41 4d 56 4a 4b 49 57 4d 56 

    - failed on trial 1 of 100
    - input = 'TAMVJKIWMV'

  * 1000 random characters from binary alphabet
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 42 41 41 41 42 42 42 42 41 .. 41 41 41 42 42 42 42 42 41 

    - failed on trial 1 of 100

  * 1000 random characters from DNA alphabet
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 41 47 47 41 47 43 41 47 47 .. 43 41 41 41 41 41 41 43 54 

    - failed on trial 1 of 100

  * 1000 random characters from uppercase alphabet
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 51 43 5a 48 43 57 56 44 47 .. 4a 44 42 58 44 57 42 45 41 

    - failed on trial 1 of 100

==> FAILED

Test 6e: check that inverseTransform(tranform()) = original on random inputs
  * 1000 random characters from ASCII alphabet 
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 71 77 4f 1e 13 68 78 22 11 .. 15 45 57 41 23 18 2c 30 56 

    - failed on trial 1 of 100

  * 1000 random characters from extended ASCII alphabet
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: fa 49 c7 e5 29 c0 ff 55 57 .. 71 bc 11 19 74 43 bb 90 4d 

    - failed on trial 1 of 100

  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 73 b2 06 d1 fa 47 79 82 b3 .. 84 18 e3 a9 06 17 ac a2 c7 

    - failed on trial 1 of 100

  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
    - student   length = 0
    - reference length = 1000
    - student:   
    - reference: 50 71 52 17 b9 6a 2d db 31 .. fb 4b 05 5a 82 c5 bf ca 8b 

    - failed on trial 1 of 100

==> FAILED

Test 6f: check that inverseTransform(tranform()) = original
         on random inputs that are circular shifts of themselves
  * random strings from unary alphabet
    - student   length = 0
    - reference length = 25
    - student:   
    - reference: 41 41 41 41 41 41 41 41 41 .. 41 41 41 41 41 41 41 41 41 

    - failed on trial 1 of 2
    - input = 'AAAAAAAAAAAAAAAAAAAAAAAAA'

  * random strings from binary alphabet
    - student   length = 0
    - reference length = 15
    - student:   
    - reference: 42 42 42 41 42 42 42 42 41 42 42 42 42 41 42 

    - failed on trial 1 of 100
    - input = 'BBBABBBBABBBBAB'

  * random strings from DNA alphabet
    - student   length = 0
    - reference length = 20
    - student:   
    - reference: 43 43 41 47 54 43 43 41 47 54 43 43 41 47 54 43 43 41 47 54 

    - failed on trial 1 of 100
    - input = 'CCAGTCCAGTCCAGTCCAGT'

  * random strings from uppercase alphabet
    - student   length = 0
    - reference length = 20
    - student:   
    - reference: 55 4c 41 51 47 55 4c 41 51 47 55 4c 41 51 47 55 4c 41 51 47 

    - failed on trial 1 of 100
    - input = 'ULAQGULAQGULAQGULAQG'

==> FAILED

Test 7a: check that transform() calls either close() or flush()
  * amendments.txt
  * aesop.txt
==> passed

Test 7b: check that inverseTransform() calls either close() or flush()
  * amendments.txt.bwt
    - student   length = 0
    - reference length = 18369
    - student:   
    - reference: 41 72 74 69 63 6c 65 20 49 .. 65 72 76 65 6e 65 64 2e 0a 

  * aesop.txt.bwt
    - student   length = 0
    - reference length = 191943
    - student:   
    - reference: 41 65 73 6f 70 27 73 20 46 .. 72 20 73 75 6e 73 3f 22 0a 

==> FAILED

Test 8a: check transform() on large files
  * rand100K.bin
  * world192.txt
==> passed

Test 8b: check inverseTransform() on large files
  * rand100K.bin.bwt
    - student   length = 0
    - reference length = 100000
    - student:   
    - reference: 73 fe be 6c 9d a3 82 eb 5e .. f5 60 4f 60 99 82 d5 72 38 

  * world192.txt.bwt
    - student   length = 0
    - reference length = 2473400
    - student:   
    - reference: 2a 2a 2a 2a 54 68 65 20 50 .. 72 6c 61 6e 64 0d 0a 0d 0a 

==> FAILED

Test 8c: check that inverseTransform(transform()) = original on large files
  * rand100K.bin
    - student   length = 0
    - reference length = 100000
    - student:   
    - reference: 73 fe be 6c 9d a3 82 eb 5e .. f5 60 4f 60 99 82 d5 72 38 

  * world192.txt
    - student   length = 0
    - reference length = 2473400
    - student:   
    - reference: 2a 2a 2a 2a 54 68 65 20 50 .. 72 6c 61 6e 64 0d 0a 0d 0a 

==> FAILED


Total: 13/28 tests passed!


================================================================
********************************************************************************
*  MEMORY
********************************************************************************

Analyzing memory of CircularSuffixArray
*-----------------------------------------------------------
Running 10 total tests.

Memory usage of a CircularSuffixArray for a random string of length n.
Maximum allowed memory is 64n + 128.

                 n        bytes
-------------------------------
=> passed       16          192
=> passed       32          272
=> passed       64          432
=> passed      128          752
=> passed      256         1392
=> passed      512         2672
=> passed     1024         5232
=> passed     2048        10352
=> passed     4096        20592
=> passed     8192        41072
==> 10/10 tests passed

Total: 10/10 tests passed!

Estimated student memory (bytes) = 5.00 n + 112.00   (R^2 = 1.000)

================================================================



********************************************************************************
*  TIMING
********************************************************************************

Timing CircularSuffixArray
*-----------------------------------------------------------
Running 26 total tests.

Tests  1-13: time to create a circular suffix array for the first
             n character of dickens.txt and call index(i) for each i

            [ max allowed time = 10 seconds and <= 12x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00      10.11
=> passed     2000       0.00       0.00       1.16
=> passed     4000       0.00       0.00       1.73
=> passed     8000       0.00       0.00       1.95
=> passed    16000       0.01       0.00       2.89
=> passed    32000       0.01       0.00       2.00
=> passed    64000       0.01       0.01       2.41
=> passed   128000       0.03       0.01       2.88
=> passed   256000       0.06       0.02       3.09
=> passed   512000       0.13       0.04       2.85
=> passed  1024000       0.27       0.10       2.79
=> passed  2048000       0.57       0.21       2.72
=> passed  4096000       1.24       0.46       2.68

Estimated running time (using last 6 measurements)
    = 9.32e-08 * n^1.08  (R^2 = 1.00)


Tests 14-26: time to create circular suffix array for n random ASCII characters
            and call index(i) for each i

            [ max allowed time = 10 seconds and <= 20x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       4.06
=> passed     2000       0.00       0.00       2.58
=> passed     4000       0.00       0.00       2.45
=> passed     8000       0.00       0.00       3.61
=> passed    16000       0.00       0.00       4.92
=> passed    32000       0.01       0.00       6.19
=> passed    64000       0.01       0.00       5.81
=> passed   128000       0.03       0.00       6.23
=> passed   256000       0.05       0.01       4.40
=> passed   512000       0.12       0.03       4.37
=> passed  1024000       0.25       0.04       5.58
=> passed  2048000       0.54       0.09       6.26
=> passed  4096000       1.22       0.17       7.28

Estimated running time (using last 6 measurements)
    = 5.60e-08 * n^1.11  (R^2 = 1.00)


Total: 26/26 tests passed!


================================================================



********************************************************************************
*  TIMING
********************************************************************************

Timing MoveToFront
*-----------------------------------------------------------
Running 38 total tests.

Test 1: count calls to methods in BinaryStdOut from encode()
  * abra.txt
  * amendments.txt
==> passed

Test 2: count calls to methods in BinaryStdOut from decode()
  * abra.txt.mtf
  * amendments.txt.mtf
==> passed

Tests  3-12: Timing encode() with first n character of dickens.txt
             [ max allowed time = 2 seconds and <= 4x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       2.21
=> passed     2000       0.01       0.00       3.17
=> passed     4000       0.01       0.00       2.96
=> passed     8000       0.02       0.01       2.79
=> passed    16000       0.03       0.01       2.67
=> passed    32000       0.06       0.02       2.57
=> passed    64000       0.12       0.05       2.45
=> passed   128000       0.22       0.09       2.38
=> passed   256000       0.43       0.18       2.31

Estimated running time (using last 6 measurements)
     = 4.18e-06 * n^0.92  (R^2 = 1.00)


Tests  13-20: Timing encode() with first n character of abab.txt
             [ max allowed time = 2 seconds and <= 4x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       1.83
=> passed     2000       0.00       0.00       1.83
=> passed     4000       0.00       0.00       1.83
=> passed     8000       0.01       0.01       1.80
=> passed    16000       0.02       0.01       1.82
=> passed    32000       0.04       0.02       1.83
=> passed    64000       0.08       0.04       1.80
=> passed   128000       0.15       0.09       1.80
=> passed   256000       0.31       0.17       1.80

Estimated running time (using last 6 measurements)
     = 1.24e-06 * n^1.00  (R^2 = 1.00)


Tests 21-29: Timing decode() with first n character of dickens.txt
             [ max allowed time = 2 seconds and <= 4x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       1.90
=> passed     2000       0.00       0.00       1.91
=> passed     4000       0.01       0.00       1.94
=> passed     8000       0.01       0.01       1.96
=> passed    16000       0.02       0.01       1.98
=> passed    32000       0.05       0.02       2.11
=> passed    64000       0.09       0.04       2.01
=> passed   128000       0.18       0.09       1.98
=> passed   256000       0.36       0.18       2.02

Estimated running time (using last 6 measurements)
     = 1.53e-06 * n^0.99  (R^2 = 1.00)


Tests 30-38: Timing decode() with first n character of abab.txt
             [ max allowed time = 2 seconds and <= 4x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       2.04
=> passed     2000       0.00       0.00       2.06
=> passed     4000       0.01       0.00       2.07
=> passed     8000       0.01       0.01       2.07
=> passed    16000       0.02       0.01       2.07
=> passed    32000       0.04       0.02       2.07
=> passed    64000       0.09       0.04       2.07
=> passed   128000       0.18       0.09       2.07
=> passed   256000       0.35       0.17       2.07

Estimated running time (using last 6 measurements)
     = 1.40e-06 * n^1.00  (R^2 = 1.00)


Total: 38/38 tests passed!


================================================================



********************************************************************************
*  TIMING (substituting reference CircularSuffixArray)
********************************************************************************

Timing BurrowsWheeler
*-----------------------------------------------------------
Running 95 total tests.

Test 1: count calls to methods in CircularSuffixArray from transform()
  * abra.txt
  * amendments.txt
==> passed

Test 2: count calls to methods in CircularSuffixArray from inverseTransform()
  * abra.txt.bwt
  * amendments.txt.bwt
==> passed

Test 3: count calls to methods in BinaryStdOut from transform()
  * abra.txt
  * amendments.txt
==> passed

Test 4: count calls to methods in BinaryStdOut from inverseTransform()
  * abra.txt.bwt
    - inverseTransform() calls to write() = 0
    - minimum number of calls = 12
    - maximum number of calls = 12

  * amendments.txt.bwt
    - inverseTransform() calls to write() = 0
    - minimum number of calls = 18369
    - maximum number of calls = 18369

==> FAILED

Tests  5-17: timing transform() with first n character of dickens.txt
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       0.23
=> passed     2000       0.00       0.00       0.92
=> passed     4000       0.00       0.00       1.14
=> passed     8000       0.00       0.00       1.36
=> passed    16000       0.00       0.00       1.14
=> passed    32000       0.01       0.01       0.79
=> passed    64000       0.01       0.01       1.08
=> passed   128000       0.01       0.01       1.04
=> passed   256000       0.03       0.03       1.10
=> passed   512000       0.06       0.05       1.13
=> passed  1024000       0.13       0.12       1.10
=> passed  2048000       0.28       0.26       1.08
=> passed  4096000       0.64       0.57       1.12

Estimated running time as a function of n (using last 6 measurements)
    = 3.02e-08 * n^1.11  (R^2 = 1.00)


Tests 18-30: timing transform() with first n character of random.bin
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       1.06
=> passed     2000       0.00       0.00       1.12
=> passed     4000       0.00       0.00       1.09
=> passed     8000       0.00       0.00       1.09
=> passed    16000       0.00       0.00       1.08
=> passed    32000       0.00       0.00       1.20
=> passed    64000       0.01       0.01       1.12
=> passed   128000       0.02       0.01       1.10
=> passed   256000       0.03       0.03       1.13
=> passed   512000       0.07       0.06       1.11
=> passed  1024000       0.14       0.13       1.09
=> passed  2048000       0.32       0.30       1.09
=> passed  4096000       0.69       0.63       1.09

Estimated running time as a function of n (using last 6 measurements)
    = 3.47e-08 * n^1.10  (R^2 = 1.00)


Tests 31-43: timing transform() with first n character of abab.txt
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       0.92
=> passed     2000       0.00       0.00       1.05
=> passed     4000       0.00       0.00       1.06
=> passed     8000       0.00       0.00       1.05
=> passed    16000       0.00       0.00       1.08
=> passed    32000       0.00       0.00       2.74
=> passed    64000       0.00       0.00       1.20
=> passed   128000       0.00       0.00       1.27
=> passed   256000       0.01       0.01       1.29
=> passed   512000       0.01       0.01       1.27
=> passed  1024000       0.03       0.02       1.26
=> passed  2048000       0.05       0.05       1.14
=> passed  4096000       0.10       0.09       1.12

Estimated running time as a function of n (using last 6 measurements)
    = 3.01e-08 * n^0.99  (R^2 = 1.00)


Tests 44-56: timing inverseTransform() with first n character of dickens.txt
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       0.07
=> passed     2000       0.00       0.00       0.07
=> passed     4000       0.00       0.00       0.06
=> passed     8000       0.00       0.00       0.06
=> passed    16000       0.00       0.00       0.06
=> passed    32000       0.00       0.00       0.15
=> passed    64000       0.00       0.00       0.17
=> passed   128000       0.00       0.00       0.23
=> passed   256000       0.00       0.01       0.34
=> passed   512000       0.00       0.01       0.28
=> passed  1024000       0.01       0.03       0.26
=> passed  2048000       0.02       0.08       0.22
=> passed  4096000       0.04       0.24       0.18

Estimated running time as a function of n (using last 6 measurements)
    = 4.07e-09 * n^1.06  (R^2 = 1.00)


Tests 57-69: timing inverseTransform() with first n character of random.bin
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1024       0.00       0.00       0.29
=> passed     2048       0.00       0.00       0.47
=> passed     4096       0.00       0.00       0.44
=> passed     8192       0.00       0.00       0.45
=> passed    16384       0.00       0.00       0.45
=> passed    32768       0.00       0.00       0.45
=> passed    65536       0.00       0.00       0.45
=> passed   131072       0.00       0.00       0.45
=> passed   262144       0.00       0.01       0.35
=> passed   524288       0.00       0.02       0.26
=> passed  1048576       0.01       0.04       0.24
=> passed  2097152       0.02       0.08       0.22
=> passed  4194304       0.05       0.29       0.15

Estimated running time as a function of n (using last 6 measurements)
    = 4.21e-09 * n^1.05  (R^2 = 1.00)


Tests 70-82: timing inverseTransform() with first n character of abab.txt
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       0.45
=> passed     2000       0.00       0.00       0.47
=> passed     4000       0.00       0.00       0.45
=> passed     8000       0.00       0.00       0.41
=> passed    16000       0.00       0.00       0.51
=> passed    32000       0.00       0.00       0.44
=> passed    64000       0.00       0.00       0.43
=> passed   128000       0.00       0.00       0.44
=> passed   256000       0.00       0.00       0.45
=> passed   512000       0.00       0.01       0.45
=> passed  1024000       0.01       0.02       0.45
=> passed  2048000       0.02       0.04       0.45
=> passed  4096000       0.03       0.07       0.45

Estimated running time as a function of n (using last 6 measurements)
    = 8.56e-09 * n^1.00  (R^2 = 1.00)


Tests 83-95: timing inverseTransform() with first n character of cyclic.bin
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1024       0.00       0.00       0.47
=> passed     2048       0.00       0.00       0.46
=> passed     4096       0.00       0.00       0.45
=> passed     8192       0.00       0.00       0.45
=> passed    16384       0.00       0.00       0.45
=> passed    32768       0.00       0.00       0.44
=> passed    65536       0.00       0.00       0.44
=> passed   131072       0.00       0.00       0.44
=> passed   262144       0.00       0.01       0.28
=> passed   524288       0.00       0.02       0.22
=> passed  1048576       0.01       0.04       0.22
=> passed  2097152       0.02       0.08       0.23
=> passed  4194304       0.04       0.17       0.21

Estimated running time as a function of n (using last 6 measurements)
    = 8.01e-09 * n^1.00  (R^2 = 1.00)


Total: 94/95 tests passed!


================================================================