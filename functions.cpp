#include "functions.h"
#include <QByteArray>
#include <QDebug>
#include <qdebug.h>

void heapify(QList<int> &hipArray, int heapSize, int nodeIndex) {
  int largest = nodeIndex;
  int left = 2 * nodeIndex + 1;
  int rignt = 2 * nodeIndex + 2;

  if (left < heapSize && hipArray[left] > hipArray[largest]) {
    largest = left;
  }

  if (rignt < heapSize && hipArray[rignt] > hipArray[largest]) {
    largest = rignt;
  }

  if (largest != nodeIndex) {
    std::swap(hipArray[nodeIndex], hipArray[largest]);
    heapify(hipArray, heapSize, largest);
  }
}

void heapBuild(QList<int> &hipArray) {
  int heapSize = hipArray.size();

  for (int i = heapSize / 2 - 1; i >= 0; i--) {
    heapify(hipArray, heapSize, i);
  }
}

void heapSortStep(QList<int> &hipArray, int step) {
  int heapSize = hipArray.size();

  heapBuild(hipArray);

  for (int i = heapSize - 1; i >= heapSize - step && i >= 1; i--) {
    std::swap(hipArray[0], hipArray[i]);
    heapify(hipArray, i, 0);
  }
}

QByteArray parser(QByteArray req) {
  QByteArray response;

  // Парсинг запроса
  QList<QByteArray> parts = req.split('&');

  // Вызов команды
  if (parts.at(0) == "sort") {
    if (parts.size() >= 3) {
      QByteArray step = parts.at(1);
      QList<QByteArray> data = parts.at(2).split(' ');

      // Преобразование данных
      QList<int> hipArray;
      for (const QByteArray &value : data) {
        bool conversionOk;
        int number = value.toInt(&conversionOk);
        if (conversionOk) {
          hipArray.append(number);
        } else {
          response = "Ошибка: неверные входные данные";
          return response;
        }
      }

      // Сортировка до необходимого шага
      if (step.toInt() >= 1 && step.toInt() <= hipArray.size()) {
        heapSortStep(hipArray, step.toInt());

        // Формирование ответа
        response = "Массив на " + step + " шаге сортировки: ";
        for (int i = 0; i < hipArray.size(); i++) {
          response += QByteArray::number(hipArray.at(i));
          if (i < hipArray.size() - 1) {
            response += ' ';
          }
        }
      } else {
        response = "Ошибка: некорректный номер шага";
      }
    } else {
      response = "Ошибка: недостаточное количество параметров функции";
    }
  }
  // Если команда не распознана, отправить сообщение об ошибке
  else {
    response = "Ошибка: неверное название команды";
  }
  return response;
}

void test() {
  
  // Тест 1. проверка корректной работы алгоритма
  QByteArray input1 = "sort&2&10 3 4 6 2 3";
  QByteArray result1 = parser(input1);
  if (result1 == "Массив на 2 шаге сортировки: 4 3 2 3 6 10") {
    qDebug() << "Test 1 completed";
  } else {
    qDebug() << "Test 1 failed";
  }

  // Тест 2. некорректный номер шага
  QByteArray input2 = "sort&0&2 1 3";
  QByteArray result2 = parser(input2);
  if (result2 == "Ошибка: некорректный номер шага") {
    qDebug() << "Test 2 completed";
  } else {
    qDebug() << "Test 2 failed";
  }

  // Test Case 3: недостаточное количество параметров функции
  QByteArray input3 = "sort&3";
  QByteArray result3 = parser(input3);
  if (result3 == "Ошибка: недостаточное количество параметров функции") {
    qDebug() << "Test 3 completed";
  } else {
    qDebug() << "Test 3 failed";
  }

  // Test Case 4: неверное название команды
  QByteArray input4 = "test&1&2 3";
  QByteArray result4 = parser(input4);
  if (result4 == "Ошибка: неверное название команды") {
    qDebug() << "Test 4 completed";
  } else {
    qDebug() << "Test 4 failed";
  }

  // Тест 5. проверка корректной работы алгоритма
  QByteArray input5 = "sort&3&10 3 4 6 2 3";
  QByteArray result5 = parser(input5);
  if (result5 == "Массив на 3 шаге сортировки: 3 3 2 4 6 10") {
    qDebug() << "Test 5 completed";
  } else {
    qDebug() << "Test 5 failed";
  }

  // Тест 6. проверка корректной работы алгоритма
  QByteArray input6 = "sort&4&10 3 4 6 2 3";
  QByteArray result6 = parser(input6);
  if (result6 == "Массив на 4 шаге сортировки: 3 2 3 4 6 10") {
    qDebug() << "Test 6 completed";
  } else {
    qDebug() << "Test 6 failed";
  }

  // Тест 7. проверка корректной работы алгоритма
  QByteArray input7 = "sort&5&10 3 4 6 2 3";
  QByteArray result7 = parser(input7);
  if (result7 == "Массив на 5 шаге сортировки: 2 3 3 4 6 10") {
    qDebug() << "Test 7 completed";
  } else {
    qDebug() << "Test 7 failed";
  }

  // Тест 8. проверка корректной работы алгоритма
  QByteArray input8 = "sort&1&123 54 67 88";
  QByteArray result8 = parser(input8);
  if (result8 == "Массив на 1 шаге сортировки: 88 54 67 123") {
    qDebug() << "Test 8 completed";
  } else {
    qDebug() << "Test 8 failed";
  }

  // Тест 9. проверка корректной работы алгоритма
  QByteArray input9 = "sort&2&123 54 67 88";
  QByteArray result9 = parser(input9);
  if (result9 == "Массив на 2 шаге сортировки: 67 54 88 123") {
    qDebug() << "Test 9 completed";
  } else {
    qDebug() << "Test 9 failed";
  }

  // Тест 10. проверка корректной работы алгоритма
  QByteArray input10 = "sort&3&123 54 67 88";
  QByteArray result10 = parser(input10);
  if (result10 == "Массив на 3 шаге сортировки: 54 67 88 123") {
    qDebug() << "Test 10 completed";
  } else {
    qDebug() << "Test 10 failed";
  }
}