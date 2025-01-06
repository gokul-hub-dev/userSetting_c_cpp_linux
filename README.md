# userSetting_c_cpp_linux
Compile:
Cpp:
g++ -fPIC -shared -o libUserSettingsParser.so UserSettingsParser.cpp && \
g++ -o main main.cpp -L. -lUserSettingsParser -std=c++11 -lstdc++fs

C Warper:
g++ -std=c++14 -shared -fPIC UserSettingsParser.cpp -o libUserSettingsParser.so -lstdc++fs
g++ -std=c++14 -shared -fPIC UserSettingsParserWrapper.cpp -L. -lUserSettingsParser -o libUserSettingsParserWrapper.so -lstdc++fs
gcc -c main.c -o main.o
gcc main.o -L. -lUserSettingsParserWrapper -lUserSettingsParser -o main_program -lstdc++ -lpthread -lstdc++fs



run.sh:
#!/bin/bash
rm -rf build
rm -rf main
mkdir build
cd build
cmake ..
make
export LD_LIBRARY_PATH=./build:$LD_LIBRARY_PATH
gcc -o main main.c -I./include -L./build -luserSetting -lstdc++fs -lstdc++
