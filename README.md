## Вариант #24

**Создать структуру для хранения информации о домашнем питомце: его виде, окрасе, кличке.**
**Составить с ее использованием программу вывода информации обо всех питомцах с группировкой по видам (кошки, собаки, прочие).**

## How to compile && etc :

- **Building project**:

```
make build-project
```

It will create build directory with compiled files in it.

- **Running tests**:

```
make run-all-tests
```

It will run all existing tests

- **Getting coverage**:

```
make get-all-coverage
```

It will create folder coverage_output with html file with covered lines
And folder coverage where all gcov/lcov files are stored

- **Getting valgrind leaks**:

```
make valgrind-check-all
```

It will create folder valgrind_output where all valgrind info is stored

## CI :

You can find CI, working on github-actions here. CI has such types of artifacts:
- valgrind-report : valgrind memory check output
- code-coverage-report : code coverage report
- executable : main executable file
