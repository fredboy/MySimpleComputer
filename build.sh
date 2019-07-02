if [ ! -d "ctest" ]; then
    git clone https://github.com/bvdberg/ctest.git
fi

cmake CMakeLists.txt
make
./mysimplecomputer_test
