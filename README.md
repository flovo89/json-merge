# json-merge

This application is used to merge json files together.

## Building
```bash
# With gtests
mkdir build
cd build
cmake ..
make

# Without gtests
mkdir build
cd build
cmake .. -DCOMPILE_GTESTS=off
make
```