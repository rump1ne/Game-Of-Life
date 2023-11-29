#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

class Counter {
private:
  static int generationCount; // Счётчик генераций
public:
  Counter() {
    generationCount++;
  }
};

// Функция для сдвига живых клеток вправо на сдвиг_x и вниз на сдвиг_y
void shiftCells(vector<vector<int>>& cells, int shift_x, int shift_y) {
    int rows = cells.size();
    int cols = cells[0].size();
    vector<vector<int>> temp(rows, vector<int>(cols, 0));

    // Переносим живые клетки на новые позиции
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp[i + shift_y][j + shift_x] = cells[i][j];
        }
    }

    // Обновляем состояние поля
    cells = temp;
}

// Функция для обрезания поля до указанного размера
void trimCells(vector<vector<int>>& cells, int new_rows, int new_cols) {
    int rows = cells.size();
    int cols = cells[0].size();

    // Обновляем состояние поля, обрезая до нового размера
    cells.resize(new_rows);
    for (int i = 0; i < new_rows; i++) {
        cells[i].resize(new_cols, 0);
    }

    // Если новый размер меньше, чем старый, обрезаем только соответствующую часть поля
    if (new_rows < rows) {
        cells.erase(cells.begin() + new_rows, cells.end());
    }
    if (new_cols < cols) {
        for (int i = 0; i < cells.size(); i++) {
            cells[i].erase(cells[i].begin() + new_cols, cells[i].end());
        }
    }
}

int main(){
    setlocale(LC_ALL, "Russian");
    
    // Входные данные
    int initial_rows = 3;
    int initial_cols = 3;
    vector<vector<int>> initial_cells = {{1, 1, 0},
                                         {0, 1, 0},
                                         {0, 0, 1}};

    // Задаем новый размер поля
    int new_rows, new_cols;
    cout << "Введите новый размер поля (количество строк и столбцов): ";
    cin >> new_rows >> new_cols;

    // Проверка и обработка нового размера поля
    if (new_rows >= initial_rows && new_cols >= initial_cols) {
        // Вычисляем сдвиг по осям
        int shift_x = (new_cols - initial_cols) / 2;
        int shift_y = (new_rows - initial_rows) / 2;

        // Увеличиваем размер поля и сдвигаем живые клетки
        shiftCells(initial_cells, shift_x, shift_y);
    } else {
        // Обрезаем поле до нового размера
        trimCells(initial_cells, new_rows, new_cols);
    }

    // Вывод измененного поля
    cout << "Измененное поле:\n";
    for (int i = 0; i < initial_cells.size(); i++) {
        for (int j = 0; j < initial_cells[i].size(); j++) {
            cout << initial_cells[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
