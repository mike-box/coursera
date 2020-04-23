See the Assessment Guide for information on how to interpret this report.

ASSESSMENT SUMMARY

Compilation:  PASSED
API:          PASSED

Spotbugs:     PASSED
PMD:          PASSED
Checkstyle:   PASSED

Correctness:  25/37 tests passed
Memory:       No tests available for autograding.
Timing:       No tests available for autograding.

Aggregate score: 70.81%
[ Compilation: 5%, API: 5%, Style: 0%, Correctness: 90% ]

ASSESSMENT DETAILS

The following files were submitted:
----------------------------------
 823 Apr  8 15:18 CMYKtoRGB.java
 900 Apr  8 15:18 GreatCircle.java
 497 Apr  8 15:18 HelloGoodbye.java
 448 Apr  8 15:18 HelloWorld.java
 575 Apr  8 15:18 RightTriangle.java


********************************************************************************
*  COMPILING                                                                    
********************************************************************************


% javac HelloWorld.java
*-----------------------------------------------------------

% javac HelloGoodbye.java
*-----------------------------------------------------------

% javac RightTriangle.java
*-----------------------------------------------------------

% javac GreatCircle.java
*-----------------------------------------------------------

% javac CMYKtoRGB.java
*-----------------------------------------------------------


================================================================


Checking the APIs of your programs.
*-----------------------------------------------------------
HelloWorld:

HelloGoodbye:

RightTriangle:

GreatCircle:

CMYKtoRGB:

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

% custom checkstyle checks for HelloWorld.java
*-----------------------------------------------------------

% custom checkstyle checks for HelloGoodbye.java
*-----------------------------------------------------------

% custom checkstyle checks for RightTriangle.java
*-----------------------------------------------------------

% custom checkstyle checks for GreatCircle.java
*-----------------------------------------------------------

% custom checkstyle checks for CMYKtoRGB.java
*-----------------------------------------------------------


================================================================


********************************************************************************
*  TESTING CORRECTNESS
********************************************************************************

Testing correctness of HelloWorld
*-----------------------------------------------------------
Running 2 total tests.

Test 1: check output format
  % java HelloWorld 
  Hello, World

  % java HelloWorld 
  Hello, World

==> passed

Test 2: check correctness
  * java HelloWorld 
  * java HelloWorld 
==> passed


HelloWorld Total: 2/2 tests passed!


================================================================
Testing correctness of HelloGoodbye
*-----------------------------------------------------------
Running 6 total tests.

Test 1: check output format
  % java HelloGoodbye Kevin Bob
  Hello Kevin and Bob.
  Goodbye Kevin and Bob.

  % java HelloGoodbye Alejandra Bahati
  Hello Alejandra and Bahati.
  Goodbye Alejandra and Bahati.

==> passed

Test 2: check correctness using names from assignment specification
  * java HelloGoodbye Kevin Bob
    - failed with command-line arguments = 'Kevin Bob'
    - second line of output does not reverse names
    - reference output:
      Hello Kevin and Bob.
      Goodbye Bob and Kevin.
    - student output:
      Hello Kevin and Bob.
      Goodbye Kevin and Bob.

  * java HelloGoodbye Alejandra Bahati
    - failed with command-line arguments = 'Alejandra Bahati'
    - second line of output does not reverse names
    - reference output:
      Hello Alejandra and Bahati.
      Goodbye Bahati and Alejandra.
    - student output:
      Hello Alejandra and Bahati.
      Goodbye Alejandra and Bahati.

==> FAILED

Test 3: check correctness using fixed names
  * java HelloGoodbye Chandra Deshi
    - failed with command-line arguments = 'Chandra Deshi'
    - second line of output does not reverse names
    - reference output:
      Hello Chandra and Deshi.
      Goodbye Deshi and Chandra.
    - student output:
      Hello Chandra and Deshi.
      Goodbye Chandra and Deshi.

  * java HelloGoodbye Ayşe María
    - failed with command-line arguments = 'Ayşe María'
    - second line of output does not reverse names
    - reference output:
      Hello Ayşe and María.
      Goodbye María and Ayşe.
    - student output:
      Hello Ayşe and María.
      Goodbye Ayşe and María.

  * java HelloGoodbye Wayan Taiyeo
    - failed with command-line arguments = 'Wayan Taiyeo'
    - second line of output does not reverse names
    - reference output:
      Hello Wayan and Taiyeo.
      Goodbye Taiyeo and Wayan.
    - student output:
      Hello Wayan and Taiyeo.
      Goodbye Wayan and Taiyeo.

  * java HelloGoodbye Ástfríður Bedřiška
    - failed with command-line arguments = 'Ástfríður Bedřiška'
    - second line of output does not reverse names
    - reference output:
      Hello Ástfríður and Bedřiška.
      Goodbye Bedřiška and Ástfríður.
    - student output:
      Hello Ástfríður and Bedřiška.
      Goodbye Ástfríður and Bedřiška.

==> FAILED

Test 4: check correctness when two names are the same
  * java HelloGoodbye Turing Turing
  * java HelloGoodbye Lovelace Lovelace
  * java HelloGoodbye Hopper Hopper
  * java HelloGoodbye Knuth Knuth
==> passed

Test 5: check correctness using random names
  * java HelloGoodbye Ludmila Radislava
    - failed with command-line arguments = 'Ludmila Radislava'
    - second line of output does not reverse names
    - reference output:
      Hello Ludmila and Radislava.
      Goodbye Radislava and Ludmila.
    - student output:
      Hello Ludmila and Radislava.
      Goodbye Ludmila and Radislava.

  * java HelloGoodbye Zlatinka Cletus
    - failed with command-line arguments = 'Zlatinka Cletus'
    - second line of output does not reverse names
    - reference output:
      Hello Zlatinka and Cletus.
      Goodbye Cletus and Zlatinka.
    - student output:
      Hello Zlatinka and Cletus.
      Goodbye Zlatinka and Cletus.

  * java HelloGoodbye Jaunius Rénald
    - failed with command-line arguments = 'Jaunius Rénald'
    - second line of output does not reverse names
    - reference output:
      Hello Jaunius and Rénald.
      Goodbye Rénald and Jaunius.
    - student output:
      Hello Jaunius and Rénald.
      Goodbye Jaunius and Rénald.

  * java HelloGoodbye Yiğit Pim
    - failed with command-line arguments = 'Yiğit Pim'
    - second line of output does not reverse names
    - reference output:
      Hello Yiğit and Pim.
      Goodbye Pim and Yiğit.
    - student output:
      Hello Yiğit and Pim.
      Goodbye Yiğit and Pim.

  * java HelloGoodbye Memduh Vidosav
    - failed with command-line arguments = 'Memduh Vidosav'
    - second line of output does not reverse names
    - reference output:
      Hello Memduh and Vidosav.
      Goodbye Vidosav and Memduh.
    - student output:
      Hello Memduh and Vidosav.
      Goodbye Memduh and Vidosav.

==> FAILED

Test 6: test correctness using many random names
  * 10 pairs of random names
    - failed with command-line arguments = 'Piety Polat'
    - second line of output does not reverse names
    - reference output:
      Hello Piety and Polat.
      Goodbye Polat and Piety.
    - student output:
      Hello Piety and Polat.
      Goodbye Piety and Polat.

    - failed on trial 1 of 10

  * 100 pairs of random names
    - failed with command-line arguments = 'Theofilaktos Annushka'
    - second line of output does not reverse names
    - reference output:
      Hello Theofilaktos and Annushka.
      Goodbye Annushka and Theofilaktos.
    - student output:
      Hello Theofilaktos and Annushka.
      Goodbye Theofilaktos and Annushka.

    - failed on trial 1 of 100

  * 1000 pairs of random names
    - failed with command-line arguments = 'Piermario Francisca'
    - second line of output does not reverse names
    - reference output:
      Hello Piermario and Francisca.
      Goodbye Francisca and Piermario.
    - student output:
      Hello Piermario and Francisca.
      Goodbye Piermario and Francisca.

    - failed on trial 1 of 1000

  * 10000 pairs of random names
    - failed with command-line arguments = 'Jürina Jouko'
    - second line of output does not reverse names
    - reference output:
      Hello Jürina and Jouko.
      Goodbye Jouko and Jürina.
    - student output:
      Hello Jürina and Jouko.
      Goodbye Jürina and Jouko.

    - failed on trial 1 of 10000

==> FAILED


HelloGoodbye Total: 2/6 tests passed!


================================================================
Testing correctness of RightTriangle
*-----------------------------------------------------------
Running 11 total tests.

Test 1: check output format for inputs from assignment specification
  % java RightTriangle 3 4 5
  true

  % java RightTriangle 13 12 5
  true

  % java RightTriangle 1 2 3
  false

  % java RightTriangle -3 4 -5
  false

==> passed

Test 2: check correctness of inputs from assignment specification
  * java RightTriangle 3 4 5
  * java RightTriangle 13 12 5
  * java RightTriangle -3 4 -5
==> passed

Test 3: inputs with a^2 + b^2 = c^2
  * java RightTriangle 4 3 5
  * java RightTriangle 5 12 13
  * java RightTriangle 15 8 17
  * java RightTriangle 7 24 25
  * java RightTriangle 20 21 29
  * java RightTriangle 35 12 37
  * java RightTriangle 9 40 41
  * java RightTriangle 28 45 53
  * java RightTriangle 12 35 37
  * java RightTriangle 60 11 61
  * java RightTriangle 16 63 65
  * java RightTriangle 16 63 65
  * java RightTriangle 56 35 65
    - reference output = 'false'
    - student   output = 'true'

  * java RightTriangle 55 48 73
  * java RightTriangle 13 84 85
  * java RightTriangle 13 84 85
  * java RightTriangle 36 77 85
  * java RightTriangle 39 80 89
  * java RightTriangle 65 72 97
==> FAILED

Test 4: inputs with a^2 + c^2 = b^2
  * java RightTriangle 3 5 4
  * java RightTriangle 5 13 12
  * java RightTriangle 8 17 15
  * java RightTriangle 7 25 24
  * java RightTriangle 20 29 21
  * java RightTriangle 12 37 35
  * java RightTriangle 9 41 40
  * java RightTriangle 28 53 45
  * java RightTriangle 12 37 35
  * java RightTriangle 11 61 60
==> passed

Test 5: inputs with b^2 + c^2 = a^2
  * java RightTriangle 5 4 3
  * java RightTriangle 13 5 12
  * java RightTriangle 17 15 8
  * java RightTriangle 25 7 24
  * java RightTriangle 29 21 20
  * java RightTriangle 37 12 35
  * java RightTriangle 41 40 9
  * java RightTriangle 53 45 28
  * java RightTriangle 37 12 35
  * java RightTriangle 61 11 60
==> passed

Test 6: inputs that are not Pythagorean triples
  * java RightTriangle 5 5 5
    - reference output = 'false'
    - student   output = 'true'

  * java RightTriangle 3 4 6
    - reference output = 'false'
    - student   output = 'true'

  * java RightTriangle 5 12 14
    - reference output = 'false'
    - student   output = 'true'

==> FAILED

Test 7: inputs with zeros
  * java RightTriangle 0 0 1
  * java RightTriangle 0 0 0
  * java RightTriangle 0 1 1
  * java RightTriangle 0 10 10
==> passed

Test 8: inputs with negative values
  * java RightTriangle 3 4 -5
  * java RightTriangle -3 4 5
  * java RightTriangle -3 -4 5
  * java RightTriangle -3 -4 -5
  * java RightTriangle -2147483648 -2147483648 -2147483648
    - reference output = 'false'
    - student   output = 'true'

  * java RightTriangle 0 0 -2147483648
  * java RightTriangle -5 -12 13
==> FAILED

Test 9: random Pythagorean triples
  * 10000 random Pythagorean triples between 1 and 100
  * 10000 random Pythagorean triples between 1 and 1000
  * 10000 random Pythagorean triples between 1 and 10000
==> passed

Test 10: random non-Pythagorean triples
  * 10000 random non-Pythagorean triples between 1 and 100
    - reference output = 'false'
    - student   output = 'true'
    - java RightTriangle 59 29 59
    - false positive on trial 1 of 10000

  * 10000 random non-Pythagorean triples between 1 and 1000
    - reference output = 'false'
    - student   output = 'true'
    - java RightTriangle 429 392 139
    - false positive on trial 1 of 10000

  * 10000 random non-Pythagorean triples between 1 and 10000
    - reference output = 'false'
    - student   output = 'true'
    - java RightTriangle 9995 9062 2517
    - false positive on trial 1 of 10000

==> FAILED

Test 11: random Pythagorean triples (large integers)
  * 10000 random Pythagorean triples between 1 and 100000
  * 10000 random Pythagorean triples between 1 and 1000000
  * 10000 random Pythagorean triples between 1 and 10000000
  * 10000 random Pythagorean triples between 1 and 100000000
==> passed

Bonus Test: random non-Pythagorean triples with (a*a + b*b == c*c) or
            (a*a + c*c == b*b) or (b*b + c*c == a*a) due to arithmetic overflow
  * 50 random overflow Pythagorean triples between 1 and 100000
    - reference output = 'false'
    - student   output = 'true'
    - java RightTriangle 38953 62984 34487
    - false positive on trial 1 of 50

  * 50 random overflow Pythagorean triples between 1 and 1000000
    - reference output = 'false'
    - student   output = 'true'
    - java RightTriangle 548368 580540 45596
    - false positive on trial 18 of 50

  * 50 random overflow Pythagorean triples between 1 and 10000000
    - reference output = 'false'
    - student   output = 'true'
    - java RightTriangle 8890719 23991 8866772
    - false positive on trial 4 of 50

  * 50 random overflow Pythagorean triples between 1 and 100000000
==> FAILED


RightTriangle Total: 7/11 tests passed!


================================================================
Testing correctness of GreatCircle
*-----------------------------------------------------------
Running 11 total tests.

Test 1: check output format for inputs from assignment specification
  % java GreatCircle 40.35 74.65 48.87 -2.33
  5902.927099258561 kilometers

  % java GreatCircle 48.87 -2.33 40.35 74.65
  5902.927099258561 kilometers

==> passed

Test 2: check correctness of inputs from assignment specification
  * java GreatCircle 40.35 74.65 48.87 -2.33
  * java GreatCircle 48.87 -2.33 40.35 74.65
==> passed

Test 3: check random pairs of cities
  * Yunxian, China and Entebbe, Uganda
  * David, Panama and Iguala, Mexico
  * Barinas, Venezuela and Brisbane, Australia
  * Novomoskovsk, Russia and Canton, United States
  * Palma, Spain and Kota, India
  * Kazan, Russia and Sangli, India
  * Coventry, United Kingdom and Dawei, Burma
  * Kenosha, United States and Bandar-e Bushehr, Iran
  * Linhares, Brazil and Tamale, Ghana
  * Heihe, China and Dingzhou, China
==> passed

Test 4: check corner cases
  * java GreatCircle 0 0 0 0
  * java GreatCircle 90 90 90 90
  * java GreatCircle 0 90 0 -90
  * java GreatCircle 90 0 -90 0
  * java GreatCircle 90 90 -90 0
  * java GreatCircle 90 90 -90 -90
  * java GreatCircle 0 180 0 0
  * java GreatCircle 0 180 0 180
  * java GreatCircle 0 0 0 -180
==> passed

Test 5: check that distance between (x1, y1) and (x2, y2)
        equals the distance between (x2, y2) and (x1, y1)
  * 1000 random points with latitude and longitude in [20.0, 70.0]
  * 1000 random points with latitude and longitude in [-70.0, -20.0]
  * 1000 random points with latitude and longitude in [-90.0, 90.0]
  * 1000 random points with latitude in [-90.0, 90.0] and longitude in [-180.0, 180.0]
==> passed

Test 6: check that distance between a point and itself is 0
  * 1000 random points with latitude and longitude [20.0, 70.0]
  * 1000 random points with latitude and longitude [-70.0, -20.0]
  * 1000 random points with latitude and longitude [-90.0, 90.0]
  * 1000 random points with latitude [-90.0, 90.0] and longitude [-180.0, 180.0]
==> passed

Test 7: check that distance between two antipodal points = pi * radius
  * 10 random antipodal points
  * 100 random antipodal points
  * 1000 random antipodal points
==> passed

Test 8: check random pairs of cities
  * 100 random pairs of cities
  * 1000 random pairs of cities
  * 10000 random pairs of cities
==> passed

Test 9: check distance between two random points
  * 1000 random points with latitude and longitude [20.0, 70.0]
  * 1000 random points with latitude and longitude [-70.0, -20.0]
  * 1000 random points with latitude and longitude [-90.0, 90.0]
  * 1000 random points with latitude [-90.0, 90.0] and longitude [-180.0, 180.0]
==> passed

Test 10: check distance between two random nearby points
  * 1000 random pairs of points within 1.000000 kilometers
  * 1000 random pairs of points within 0.010000 kilometers
  * 1000 random pairs of points within 0.000100 kilometers
  * 1000 random pairs of points within 0.000001 kilometers
==> passed

Test 11: check distance between two random nearly antipodal points
  * 1000 random pairs of points within 1.000000 kilometers of being antipodal
  * 1000 random pairs of points within 0.010000 kilometers of being antipodal
  * 1000 random pairs of points within 0.000100 kilometers of being antipodal
  * 1000 random pairs of points within 0.000001 kilometers of being antipodal
==> passed


GreatCircle Total: 11/11 tests passed!


================================================================
Testing correctness of CMYKtoRGB
*-----------------------------------------------------------
Running 7 total tests.

Test 1: check output format
  % java CMYKtoRGB 0.0 1.0 0.0 0.0
  red   = 255
  green = 0
  blue  = 255

  % java CMYKtoRGB 0.0 0.4392156862745098 1.0 0.0
  red   = 255
  green = 143
  blue  = 0

==> passed

Test 2: check correctness of inputs from assignment specification
  * java CMYKtoRGB 0.0 1.0 0.0 0.0
  * java CMYKtoRGB 0.0 0.4392156862745098 1.0 0.0
==> passed

Test 3: check various inputs
  * java CMYKtoRGB 0.18 0.32 0.0 0.29
  * java CMYKtoRGB 1.0 0.58 0.0 0.33
    - failed with command-line arguments:
      1.0 0.58 0.0 0.33
    - reference output:
      red   = 0
      green = 72
      blue  = 171
    - student output:
      red   = 0
      green = 71
      blue  = 170

  * java CMYKtoRGB 0.0 1.0 0.75 0.50
    - failed with command-line arguments:
      0.0 1.0 0.75 0.50
    - reference output:
      red   = 128
      green = 0
      blue  = 32
    - student output:
      red   = 127
      green = 0
      blue  = 31

  * java CMYKtoRGB 0.0 0.14 0.70 0.15
    - failed with command-line arguments:
      0.0 0.14 0.70 0.15
    - reference output:
      red   = 217
      green = 186
      blue  = 65
    - student output:
      red   = 216
      green = 186
      blue  = 65

==> FAILED

Test 4: check corner cases
  * java CMYKtoRGB 0.0 0.0 0.0 0.0
  * java CMYKtoRGB 1.0 0.0 0.0 0.0
  * java CMYKtoRGB 0.0 1.0 0.0 0.0
  * java CMYKtoRGB 0.0 0.0 1.0 0.0
  * java CMYKtoRGB 0.0 0.0 0.0 1.0
  * java CMYKtoRGB 1.0 1.0 0.0 0.0
  * java CMYKtoRGB 1.0 0.0 1.0 0.0
  * java CMYKtoRGB 1.0 0.0 0.0 1.0
  * java CMYKtoRGB 0.0 1.0 1.0 0.0
  * java CMYKtoRGB 0.0 1.0 0.0 1.0
  * java CMYKtoRGB 0.0 0.0 1.0 1.0
  * java CMYKtoRGB 1.0 1.0 1.0 0.0
  * java CMYKtoRGB 1.0 1.0 0.0 1.0
  * java CMYKtoRGB 1.0 0.0 1.0 1.0
  * java CMYKtoRGB 0.0 1.0 1.0 1.0
  * java CMYKtoRGB 1.0 1.0 1.0 1.0
==> passed

Test 5: check that various RGB values can be generated
  * (255,  79,   0)  International Orange (Aerospace)
  * (114, 160, 193)  Air Superiority Blue
  * (220, 220, 220)  Gainsboro
  * (255, 130,  67)  Mango Tango
    - failed with command-line arguments:
      0.0 0.4901960784313726 0.7372549019607844 0.0
    - reference output:
      red   = 255
      green = 130
      blue  = 67
    - student output:
      red   = 255
      green = 130
      blue  = 66
  * (215,  59,  62)  Jasper
    - failed with command-line arguments:
      0.0 0.7255813953488373 0.7116279069767442 0.1568627450980392
    - reference output:
      red   = 215
      green = 59
      blue  = 62
    - student output:
      red   = 215
      green = 58
      blue  = 62
  * (183, 132, 167)  Opera Mauve
==> FAILED

Test 6: check that various RGB values can be generated
  * 10 random RGB values
    - failed with command-line arguments:
      0.0 0.5675675675675677 0.22972972972972974 0.41960784313725485
    - reference output:
      red   = 148
      green = 64
      blue  = 114
    - student output:
      red   = 148
      green = 63
      blue  = 114
    - failed on trial 3 of 10

  * 100 random RGB values
    - failed with command-line arguments:
      0.7641509433962265 0.839622641509434 0.0 0.1686274509803921
    - reference output:
      red   = 50
      green = 34
      blue  = 212
    - student output:
      red   = 49
      green = 33
      blue  = 212
    - failed on trial 4 of 100

  * 1000 random RGB values
    - failed with command-line arguments:
      0.34615384615384615 0.9923076923076923 0.0 0.4901960784313726
    - reference output:
      red   = 85
      green = 1
      blue  = 130
    - student output:
      red   = 85
      green = 0
      blue  = 130
    - failed on trial 1 of 1000

  * 10000 random RGB values
    - failed with command-line arguments:
      0.15671641791044782 0.0 0.791044776119403 0.4745098039215686
    - reference output:
      red   = 113
      green = 134
      blue  = 28
    - student output:
      red   = 112
      green = 134
      blue  = 27
    - failed on trial 1 of 10000

==> FAILED

Test 7: check random inputs
  * 100 random CMYK values that are multiples of 0.5
    - failed with command-line arguments:
      0.5 1.0 0.5 0.0
    - reference output:
      red   = 128
      green = 0
      blue  = 128
    - student output:
      red   = 127
      green = 0
      blue  = 127
    - failed on trial 1 of 100

  * 100 random CMYK values that are multiples of 0.25
    - failed with command-line arguments:
      0.0 0.5 1.0 0.0
    - reference output:
      red   = 255
      green = 128
      blue  = 0
    - student output:
      red   = 255
      green = 127
      blue  = 0
    - failed on trial 1 of 100

  * 100 random CMYK values that are multiples of 0.125
    - failed with command-line arguments:
      0.25 0.875 0.875 0.25
    - reference output:
      red   = 143
      green = 24
      blue  = 24
    - student output:
      red   = 143
      green = 23
      blue  = 23
    - failed on trial 1 of 100

  * 1000 random CMYK values that are multiples of 0.0625
    - failed with command-line arguments:
      0.0 0.0 0.5 0.8125
    - reference output:
      red   = 48
      green = 48
      blue  = 24
    - student output:
      red   = 47
      green = 47
      blue  = 23
    - failed on trial 1 of 1000

  * 1000 random CMYK values that are multiples of 0.03125
    - failed with command-line arguments:
      0.28125 0.03125 0.5625 0.5625
    - reference output:
      red   = 80
      green = 108
      blue  = 49
    - student output:
      red   = 80
      green = 108
      blue  = 48
    - failed on trial 1 of 1000

  * 1000 random CMYK values that are multiples of 0.015625
    - failed with command-line arguments:
      0.890625 0.90625 0.84375 0.84375
    - reference output:
      red   = 4
      green = 4
      blue  = 6
    - student output:
      red   = 4
      green = 3
      blue  = 6
    - failed on trial 1 of 1000

==> FAILED


CMYKtoRGB Total: 3/7 tests passed!


================================================================