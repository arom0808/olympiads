from os import system as cmd

complier_path = r"g++.exe"
cmd(compiler_path + " smart.cpp -o smart")
cmd(complier_path + " simple.cpp -o simple")
for i in range(1, 10 ** 9):
    print("Test #%s" % i)
    cmd("python gen.py > test.txt")
    cmd("smart < test.txt > smart_o.txt")
    cmd("simple < test.txt > simple_o.txt")
    f1 = open("smart_o.txt")
    f2 = open("simple_o.txt")
    assert f1.read() == f2.read()
    f1.close()
    f2.close()
