PAFL=$(pwd)
# cmake -DCMAKE_BUILD_TYPE=Debug -S "$PAFL" -B "$PAFL/build/debug"
cmake -DCMAKE_BUILD_TYPE=Release -S "$PAFL" -B "$PAFL/build/release"