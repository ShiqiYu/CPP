#!/bin/bash
echo "--- Test 1: Basic Math ---"
./calculator 2 + 3
./calculator 2 - 3
./calculator 2 "*" 3
./calculator 2 / 3
echo "--- Test 2: Div by Zero ---"
./calculator 3.14 / 0
echo "--- Test 3: Invalid Input ---"
./calculator a "*" 2
echo "--- Test 4: Big Numbers ---"
./calculator 987654321 "*" 987654321
echo "--- Test 5: Decimals ---"
./calculator 987654321.0 + 0.123456789
echo "--- Test 6: Scientific Notation ---"
./calculator 1.0e200 "*" 1.0e200
echo "--- Test 7: Precision (-p 2) ---"
./calculator -p 2 10 / 3
echo "--- Test 8: Interactive Mode ---"
echo -e "2 + 3\n10 / 3\n-p 2\n10 / 3\nquit" | ./calculator
