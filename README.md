# Монте-Карло для оценки европейского опциона
![CI](https://github.com/VacheslavSamoletov/C-SoftwareEngineering-Project-Stub/actions/workflows/ci.yml/badge.svg)

Учебный проект курса «Программная инженерия и C++ для количественного анализа
и алгоритмической торговли» (Вега Институт, 2026).

Моделирование цены актива геометрическим броуновским движением (GBM)
и оценка опциона методом Монте-Карло. Результаты воспроизводимы через seed.

## Структура

| Папка | Содержимое |
|---|---|
| `src/core/` | ядро: численные методы, не зависит от ввода-вывода |
| `src/` | точка входа `main.cpp` |
| `tests/` | unit-тесты (GoogleTest) |
| `benchmarks/` | бенчмарки (Google Benchmark) |
| `docs/` | требования, архитектура, ADR |

## Сборка

Требования: CMake ≥ 3.16, компилятор с C++17 (проверено на GCC 13), Ninja.

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/main
```

## Тесты

```bash
ctest --test-dir build --output-on-failure
```

## Бенчмарк

Скорость `mc::generate_gbm_path` для n_steps = 252, 10 000 и 1 000 000
(Google Benchmark). Запускать после сборки в Release:

```bash
./build/benchmarks/gbm_bench
```

## Документация

Doxygen-документация: https://vacheslavsamoletov.github.io/C-SoftwareEngineering-Project-Stub/
