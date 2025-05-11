Author: **Kotegov Nikita** | B81 | st128906@student.spbu.ru

- Решение систем **A x = b** методом Гаусса с частичным выбором главного элемента
  (алгоритм в `src/gaussian.cpp`).
- Если система вырождена или вход имеет неверный CSV-формат, программа завершится
  с **ненулевым кодом** (проверяется в CI на GitHub Actions).


## Сборка

```bash
# 1 – классическая CMake + Ninja
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build -j

# 2 – однострочник g++ (без тестов)
g++ -std=c++20 -O2 -Wall -Wextra \
    src/gaussian.cpp src/main.cpp -Iinclude -o gauss

Usage:  ./gauss  [input.csv]  [output.csv]
        ./gauss            # читает CSV из stdin, пишет в stdout

#Модульные тесты
ctest --test-dir build

