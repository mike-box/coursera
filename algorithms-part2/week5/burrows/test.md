See the Assessment Guide for information on how to interpret this report.

ASSESSMENT SUMMARY

Compilation:  PASSED
API:          PASSED

Spotbugs:     PASSED
PMD:          PASSED
Checkstyle:   PASSED

Correctness:  68/68 tests passed
Memory:       10/10 tests passed
Timing:       159/159 tests passed

Aggregate score: 100.00%
[Compilation: 5%, API: 5%, Spotbugs: 0%, PMD: 0%, Checkstyle: 0%, Correctness: 60%, Memory: 10%, Timing: 20%]

ASSESSMENT DETAILS

The following files were submitted:
----------------------------------
2.3K Mar 18 15:39 BurrowsWheeler.java
1.8K Mar 18 15:39 CircularSuffixArray.java
2.1K Mar 18 15:39 MoveToFront.java


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


================================================================


% pmd .
*-----------------------------------------------------------


================================================================


% checkstyle *.java
*-----------------------------------------------------------

% custom checkstyle checks for CircularSuffixArray.java
*-----------------------------------------------------------

% custom checkstyle checks for BurrowsWheeler.java
*-----------------------------------------------------------

% custom checkstyle checks for MoveToFront.java
*-----------------------------------------------------------


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
  * string = "EKUXMIVVKVBHILFCSHHKFGQLXWAYHC"
  * string = "BBAABABAABAAAABBABABABBBABBABB"
  * string = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
  * string = hex representation: 7a d7 26 44 6b aa b9 f0 1b 91 c4 ae bb 2b 41 
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
  * java BurrowsWheeler + < zebra.txt.bwt
  * java BurrowsWheeler + < cadabra.txt.bwt
  * java BurrowsWheeler + < amendments.txt.bwt
==> passed

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
  * zebra.txt.bwt
  * cadabra.txt.bwt
  * amendments.txt.bwt
==> passed

Test 5b: check inverseTransform() on corner-case text files
  * alphanum.txt.bwt
  * a.txt.bwt
  * stars.txt.bwt
  * couscous.txt.bwt
==> passed

Test 5c: check inverseTransform() on binary files
  * us.gif.bwt
  * CS_bricks.jpg.bwt
  * rand10K.bin.bwt
==> passed

Test 5d: check inverseTransform() of transform() on random inputs
  * 10 random characters from unary alphabet
  * 10 random characters from binary alphabet
  * 10 random characters from DNA alphabet
  * 10 random characters from uppercase alphabet
  * 100 random characters from unary alphabet
  * 1000 random characters from binary alphabet
  * 1000 random characters from DNA alphabet
  * 1000 random characters from uppercase alphabet
==> passed

Test 5e: check inverseTransform() of transform() on more random inputs
  * 1000 random characters from ASCII alphabet 
  * 1000 random characters from extended ASCII alphabet
  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
==> passed

Test 6a: check that inverseTransform(transform()) = original on text files
  * abra.txt
  * zebra.txt
  * cadabra.txt
  * amendments.txt
==> passed

Test 6b: check that inverseTransform(transform()) = original on corner-case text files
  * alphanum.txt
  * a.txt
  * stars.txt
  * couscous.txt
==> passed

Test 6c: check that inverseTransform(transform()) = original on binary files
  * us.gif
  * CS_bricks.jpg
  * rand10K.bin
==> passed

Test 6d: check that inverseTransform(tranform()) = original on random inputs
  * 10 random characters from binary alphabet
  * 10 random characters from DNA alphabet
  * 10 random characters from uppercase alphabet
  * 1000 random characters from binary alphabet
  * 1000 random characters from DNA alphabet
  * 1000 random characters from uppercase alphabet
==> passed

Test 6e: check that inverseTransform(tranform()) = original on random inputs
  * 1000 random characters from ASCII alphabet 
  * 1000 random characters from extended ASCII alphabet
  * 1000 random characters from extended ASCII alphabet (excluding 0x00)
  * 1000 random characters from extended ASCII alphabet (excluding 0xFF)
==> passed

Test 6f: check that inverseTransform(tranform()) = original
         on random inputs that are circular shifts of themselves
  * random strings from unary alphabet
  * random strings from binary alphabet
  * random strings from DNA alphabet
  * random strings from uppercase alphabet
==> passed

Test 7a: check that transform() calls either close() or flush()
  * amendments.txt
  * aesop.txt
==> passed

Test 7b: check that inverseTransform() calls either close() or flush()
  * amendments.txt.bwt
  * aesop.txt.bwt
==> passed

Test 8a: check transform() on large files
  * rand100K.bin
  * world192.txt
==> passed

Test 8b: check inverseTransform() on large files
  * rand100K.bin.bwt
  * world192.txt.bwt
==> passed

Test 8c: check that inverseTransform(transform()) = original on large files
  * rand100K.bin
  * world192.txt
==> passed


Total: 28/28 tests passed!


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
=> passed     1000       0.00       0.00      10.35
=> passed     2000       0.00       0.00       1.36
=> passed     4000       0.00       0.00       1.53
=> passed     8000       0.00       0.00       1.94
=> passed    16000       0.01       0.00       2.00
=> passed    32000       0.01       0.00       1.87
=> passed    64000       0.01       0.01       2.48
=> passed   128000       0.03       0.01       2.77
=> passed   256000       0.06       0.02       3.04
=> passed   512000       0.13       0.04       2.82
=> passed  1024000       0.27       0.10       2.76
=> passed  2048000       0.56       0.21       2.71
=> passed  4096000       1.22       0.46       2.62

Estimated running time (using last 6 measurements)
    = 8.96e-08 * n^1.08  (R^2 = 1.00)


Tests 14-26: time to create circular suffix array for n random ASCII characters
            and call index(i) for each i

            [ max allowed time = 10 seconds and <= 20x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       4.09
=> passed     2000       0.00       0.00       2.56
=> passed     4000       0.00       0.00       2.32
=> passed     8000       0.00       0.00       3.63
=> passed    16000       0.00       0.00       4.89
=> passed    32000       0.01       0.00       6.24
=> passed    64000       0.01       0.00       5.04
=> passed   128000       0.03       0.00       6.43
=> passed   256000       0.06       0.01       4.44
=> passed   512000       0.12       0.03       4.49
=> passed  1024000       0.25       0.04       5.65
=> passed  2048000       0.54       0.08       6.38
=> passed  4096000       1.20       0.16       7.43

Estimated running time (using last 6 measurements)
    = 6.67e-08 * n^1.10  (R^2 = 1.00)


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
=> passed     1000       0.00       0.00       2.25
=> passed     2000       0.01       0.00       3.24
=> passed     4000       0.01       0.00       3.02
=> passed     8000       0.02       0.01       2.87
=> passed    16000       0.03       0.01       2.71
=> passed    32000       0.06       0.02       2.59
=> passed    64000       0.12       0.05       2.50
=> passed   128000       0.23       0.09       2.41
=> passed   256000       0.44       0.19       2.36

Estimated running time (using last 6 measurements)
     = 4.27e-06 * n^0.93  (R^2 = 1.00)


Tests  13-20: Timing encode() with first n character of abab.txt
             [ max allowed time = 2 seconds and <= 4x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       1.88
=> passed     2000       0.00       0.00       1.85
=> passed     4000       0.01       0.00       1.87
=> passed     8000       0.01       0.01       1.84
=> passed    16000       0.02       0.01       1.84
=> passed    32000       0.04       0.02       1.85
=> passed    64000       0.08       0.04       1.84
=> passed   128000       0.16       0.09       1.83
=> passed   256000       0.32       0.17       1.86

Estimated running time (using last 6 measurements)
     = 1.24e-06 * n^1.00  (R^2 = 1.00)


Tests 21-29: Timing decode() with first n character of dickens.txt
             [ max allowed time = 2 seconds and <= 4x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       1.94
=> passed     2000       0.00       0.00       1.95
=> passed     4000       0.01       0.00       1.98
=> passed     8000       0.01       0.01       2.00
=> passed    16000       0.02       0.01       2.01
=> passed    32000       0.05       0.02       1.92
=> passed    64000       0.09       0.05       2.04
=> passed   128000       0.18       0.09       2.04
=> passed   256000       0.37       0.18       2.06

Estimated running time (using last 6 measurements)
     = 1.55e-06 * n^0.99  (R^2 = 1.00)


Tests 30-38: Timing decode() with first n character of abab.txt
             [ max allowed time = 2 seconds and <= 4x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       2.06
=> passed     2000       0.00       0.00       2.10
=> passed     4000       0.01       0.00       2.09
=> passed     8000       0.01       0.01       2.09
=> passed    16000       0.02       0.01       2.09
=> passed    32000       0.05       0.02       2.09
=> passed    64000       0.09       0.04       2.10
=> passed   128000       0.18       0.09       2.10
=> passed   256000       0.36       0.17       2.09

Estimated running time (using last 6 measurements)
     = 1.43e-06 * n^1.00  (R^2 = 1.00)


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
  * amendments.txt.bwt
==> passed

Tests  5-17: timing transform() with first n character of dickens.txt
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       0.17
=> passed     2000       0.00       0.00       0.63
=> passed     4000       0.00       0.00       0.71
=> passed     8000       0.00       0.00       0.86
=> passed    16000       0.00       0.00       0.57
=> passed    32000       0.00       0.01       0.66
=> passed    64000       0.01       0.01       0.67
=> passed   128000       0.01       0.01       1.03
=> passed   256000       0.03       0.03       1.05
=> passed   512000       0.06       0.05       1.09
=> passed  1024000       0.13       0.12       1.07
=> passed  2048000       0.28       0.26       1.09
=> passed  4096000       0.64       0.58       1.10

Estimated running time as a function of n (using last 6 measurements)
    = 2.31e-08 * n^1.12  (R^2 = 1.00)


Tests 18-30: timing transform() with first n character of random.bin
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       0.99
=> passed     2000       0.00       0.00       1.03
=> passed     4000       0.00       0.00       1.00
=> passed     8000       0.00       0.00       0.97
=> passed    16000       0.00       0.00       1.05
=> passed    32000       0.00       0.00       1.10
=> passed    64000       0.01       0.01       1.07
=> passed   128000       0.02       0.01       1.12
=> passed   256000       0.03       0.03       1.07
=> passed   512000       0.06       0.06       1.08
=> passed  1024000       0.14       0.13       1.07
=> passed  2048000       0.33       0.30       1.09
=> passed  4096000       0.72       0.65       1.10

Estimated running time as a function of n (using last 6 measurements)
    = 2.68e-08 * n^1.12  (R^2 = 1.00)


Tests 31-43: timing transform() with first n character of abab.txt
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       0.79
=> passed     2000       0.00       0.00       0.98
=> passed     4000       0.00       0.00       1.00
=> passed     8000       0.00       0.00       1.00
=> passed    16000       0.00       0.00       1.00
=> passed    32000       0.00       0.00       1.99
=> passed    64000       0.00       0.00       0.95
=> passed   128000       0.00       0.00       1.01
=> passed   256000       0.01       0.01       0.97
=> passed   512000       0.01       0.01       1.00
=> passed  1024000       0.02       0.02       1.02
=> passed  2048000       0.04       0.04       1.01
=> passed  4096000       0.09       0.09       0.99

Estimated running time as a function of n (using last 6 measurements)
    = 2.13e-08 * n^1.00  (R^2 = 1.00)


Tests 44-56: timing inverseTransform() with first n character of dickens.txt
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       0.76
=> passed     2000       0.00       0.00       0.56
=> passed     4000       0.00       0.00       0.43
=> passed     8000       0.00       0.00       0.43
=> passed    16000       0.00       0.00       0.43
=> passed    32000       0.00       0.00       1.10
=> passed    64000       0.00       0.00       0.70
=> passed   128000       0.00       0.00       0.94
=> passed   256000       0.01       0.01       0.67
=> passed   512000       0.02       0.01       1.11
=> passed  1024000       0.04       0.03       1.11
=> passed  2048000       0.09       0.07       1.17
=> passed  4096000       0.30       0.28       1.09

Estimated running time as a function of n (using last 6 measurements)
    = 1.43e-09 * n^1.24  (R^2 = 0.99)


Tests 57-69: timing inverseTransform() with first n character of random.bin
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1024       0.00       0.00       1.05
=> passed     2048       0.00       0.00       1.11
=> passed     4096       0.00       0.00       1.10
=> passed     8192       0.00       0.00       1.12
=> passed    16384       0.00       0.00       1.14
=> passed    32768       0.00       0.00       1.15
=> passed    65536       0.00       0.00       1.19
=> passed   131072       0.00       0.00       1.18
=> passed   262144       0.01       0.01       1.12
=> passed   524288       0.02       0.02       1.08
=> passed  1048576       0.04       0.04       1.09
=> passed  2097152       0.09       0.09       1.04
=> passed  4194304       0.35       0.30       1.15

Estimated running time as a function of n (using last 6 measurements)
    = 4.00e-10 * n^1.33  (R^2 = 0.99)


Tests 70-82: timing inverseTransform() with first n character of abab.txt
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1000       0.00       0.00       1.02
=> passed     2000       0.00       0.00       1.08
=> passed     4000       0.00       0.00       1.13
=> passed     8000       0.00       0.00       1.02
=> passed    16000       0.00       0.00       1.15
=> passed    32000       0.00       0.00       1.14
=> passed    64000       0.00       0.00       1.13
=> passed   128000       0.00       0.00       1.13
=> passed   256000       0.01       0.00       1.14
=> passed   512000       0.01       0.01       1.12
=> passed  1024000       0.02       0.02       1.19
=> passed  2048000       0.04       0.04       1.13
=> passed  4096000       0.08       0.07       1.13

Estimated running time as a function of n (using last 6 measurements)
    = 2.27e-08 * n^0.99  (R^2 = 1.00)


Tests 83-95: timing inverseTransform() with first n character of cyclic.bin
             [ max allowed time = 2 seconds and <= 8x reference ]

                 n    student  reference      ratio
---------------------------------------------------
=> passed     1024       0.00       0.00       1.04
=> passed     2048       0.00       0.00       1.06
=> passed     4096       0.00       0.00       1.13
=> passed     8192       0.00       0.00       1.10
=> passed    16384       0.00       0.00       1.18
=> passed    32768       0.00       0.00       1.14
=> passed    65536       0.00       0.00       1.12
=> passed   131072       0.00       0.00       1.13
=> passed   262144       0.01       0.00       1.71
=> passed   524288       0.02       0.02       1.04
=> passed  1048576       0.04       0.04       1.03
=> passed  2097152       0.08       0.08       1.04
=> passed  4194304       0.18       0.16       1.12

Estimated running time as a function of n (using last 6 measurements)
    = 3.39e-09 * n^1.17  (R^2 = 0.99)


Total: 95/95 tests passed!


================================================================



