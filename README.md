## 3DViewer_v1.0 @zkhrg</h2>

<table>
    <tr>
        <td>
            <img src="./dvi/dvi.webp" alt="video presentation">
        </td>
    </tr>
    <tr>
        <td>
            <p>демонстрация работы программы</p>
        </td>
    </tr>
</table>

## Описание

3DViewer v1.0 — это приложение для визуализации каркасных 3D-моделей. Программа загружает модели из файлов формата .obj и предоставляет возможность их просмотра с поддержкой таких операций, как вращение, масштабирование и перемещение. Модели отображаются в каркасном виде с минимальной задержкой, даже для моделей с большим количеством вершин.

## Структура проекта

```txt
.
├── README.md
├── build
├── dvi
│   ├── 3d_viewer_c_about.html
│   ├── Varela-Regular.ttf
│   └── dvi.webp
└── src
    ├── Makefile
    ├── c_core
    │   ├── dot_obj_parser.c
    │   ├── dot_obj_parser.h
    │   ├── transformations.c
    │   └── transformations.h
    ├── common
    │   └── types.h
    ├── tests
    │   ├── obj_files
    │   │   ├── cube.obj
    │   │   ├── pik.obj
    │   │   ├── plant.obj
    │   │   ├── skull.obj
    │   │   └── test.obj
    │   ├── test.c
    │   ├── test.h
    │   ├── test_dot_obj_parser.c
    │   └── test_transformations.c
    └── views
        ├── 3d_viewer_v1.pro
        ├── main.cc
        ├── mainwindow.cc
        ├── mainwindow.h
        ├── widget.cc
        └── widget.h
```

## Основные возможности

- Загрузка каркасной модели из файла формата .obj (поддержка вершин и рёбер).
- Перемещение модели вдоль осей X, Y, Z.
- Вращение модели вокруг осей X, Y, Z.
- Масштабирование модели на заданный коэффициент.
- Поддержка визуализации моделей с количеством вершин до 1 000 000 без зависания (задержка интерфейса не более 0,5 секунды).
  
## Графический интерфейс

Программа разработана с использованием **Qt** для создания удобного графического интерфейса, который предоставляет:

- Кнопку для выбора файла с моделью и поле для вывода его названия.
- Область визуализации каркасной модели.
- Элементы управления для перемещения, вращения и масштабирования модели.
- Информацию о загруженной модели: название файла, количество вершин и рёбер.

## Технические детали

- Язык программирования: **C**, стандарт C11.
- Использование библиотеки **Qt** для реализации GUI.
- Сборка программы настроена с использованием **Makefile** с поддержкой стандартных целей: `all`, `install`, `uninstall`, `clean`, `test`, `gcov_report`.
- Программа построена в соответствии с принципами структурного программирования.
- В проекте реализовано покрытие модулей, связанных с загрузкой моделей и аффинными преобразованиями, с помощью **unit-тестов**.

## Примеры поддерживаемых аффинных преобразований

- **Перемещение** — позволяет сдвигать модель на заданное расстояние вдоль осей X, Y, Z.
- **Вращение** — вращение модели на заданный угол вокруг своих осей X, Y, Z.
- **Масштабирование** — увеличение или уменьшение модели на заданный коэффициент.

## Производительность

Программа оптимизирована для работы с моделями разного уровня детализации:

- 100 вершин
- 1 000 вершин
- 10 000 вершин
- 100 000 вершин
- 1 000 000 вершин

## Предзависимости

Перед сборкой и запуском программы убедитесь, что на вашем компьютере установлены все необходимые зависимости:

* `Qt5` — для графического интерфейса
* `GCC` — компилятор для сборки программы (поддержка стандарта `C11`)
* `GNU Make` — для автоматической сборки проекта
* `LCOV` — для генерации отчётов о покрытии тестами (опционально)
* `Gcov` — для покрытия тестов (опционально)

## Установка и запуск

1. Склонируйте репозиторий:
    ```bash
    git clone https://github.com/zkhrg/c-objects-viewer.git
    cd c-objects-viewer
    ```

2. Сборка и запуск программы:
    ```bash
    cd src
    make all
    ```

## Тестирование

Для запуска unit-тестов используйте команду:
```bash
make test
```

Для генерации отчёта о покрытии тестами:
```bash
make gcov_report
```
