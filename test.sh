cmake --build build
cd accipit/tests
python3 test.py ../../build/compiler lab1
python3 test.py ../../build/compiler lab2
python3 test.py ../../build/compiler lab3

