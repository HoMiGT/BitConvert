# rm -rf build
# mkdir build
cd build
# conan install ..
cmake install ..
make 
cp ../t.py ./lib/
cd lib
python t.py
cd ../../
cp /home/wpwl/Projects/BitConvert/build/lib/bit_convert.so /home/wpwl/Projects/AlgorithmServer/utils/

