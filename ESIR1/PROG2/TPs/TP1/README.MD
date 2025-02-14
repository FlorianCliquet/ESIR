# HOW TO TEST

## Creating input.txt

```sh
python3 CreateInput.py
```

## CMake Options

### Build with Debug mode
```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
make -C build
```

### Build with AVX optimization
```sh
cmake -B build -DUSE_AVX=ON
make -C build
```

### Build without AVX optimization
```sh
cmake -B build -DUSE_AVX=OFF
make -C build
```

## Run Program 
```sh
time ./build/TP1 < ./build/input.txt > /dev/null
```

## Test Memory

### Ubuntu

```sh
/usr/bin/time -v ./build/TP1 < ./build/input.txt > /dev/null
```
- Look at "Maximum resident set size (kbytes)" to see the most used RAM space
### Windows
```powerhsell
Measure-Process -Id (Get-Process TP1).Id
```