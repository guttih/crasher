# crasher
Program which crashes when asked to


## Development


### Build a release version

From the repository root directory, run the following commands:

```bash
cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Release
cmake --build build/
```

### Build a debug version

- Possibly you will need to install the debug version of the libraries. For example, on Ubuntu, you can install the debug version of the `libboost-dev` package by running the following command:
    ```bash
    sudo apt-get install libboost-dev-dbg
    ```
    or in in centos
    ```bash
    sudo yum install boost-devel
    ```

- Possibly you will also need to install for the standard library
```bash
sudo apt-get install libstdc++
```


From the repository root directory, run the following commands:

```bash
cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Debug
cmake --build build/
d run the application with help switch
./build/crasher -h
```

### Launching the application
```bash     
#And run the application with help switch
./build/crasher/crasher -h
```
