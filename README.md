# Advent of Code

- `adventofcode2024/` contains C solutions.
- `adventofcode2025/` contains Java solutions (11/12 completed).

## 2024 in C

make -C adventofcode2024
./adventofcode2024/bin/day01

## 2025 in Java

cd adventofcode2025
mkdir -p bin
find src -name '*.java' -exec javac -d bin {} +
java -cp bin App
