#pragma once
#include <iostream>
#include <string>
#include <fstream>

template <typename T>
class DynamicVector {
private:
    T* data;          // Указатель на массив
    int currentSize;  // Текущий размер
    int capacity;     // Объем выделенной памяти

    void resizeIfNeeded() {
        if (currentSize == capacity) {
            int newCapacity = capacity * 2;
            T* newData = new T[newCapacity];
            for (int i = 0; i < currentSize; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

public:
    DynamicVector()
        : data(new T[1]), currentSize(0), capacity(1) {}

    DynamicVector(const DynamicVector& other)
        : data(new T[other.capacity]), currentSize(other.currentSize), capacity(other.capacity) {
        for (int i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicVector& operator=(const DynamicVector& other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.capacity];
            currentSize = other.currentSize;
            capacity = other.capacity;
            for (int i = 0; i < currentSize; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~DynamicVector() {
        delete[] data;
    }

    void pushBack(const T& value) {
        resizeIfNeeded();
        data[currentSize++] = value;
    }

    void insert(const T& value, int index) {
        if (index < 0 || index > currentSize) {
            throw std::out_of_range("Index out of range!");
        }
        resizeIfNeeded();
        for (int i = currentSize; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++currentSize;
    }

    void erase(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range!");
        }
        for (int i = index; i < currentSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        --currentSize;
    }

    T at(int index) const {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }

    void set(const T& value, int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range!");
        }
        data[index] = value;
    }

    int size() const {
        return currentSize;
    }

    int capacityUsed() const {
        return capacity;
    }

    void print() const {
        for (int i = 0; i < currentSize; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }

    void saveToFile(const std::string& filename, bool overwrite = true) const {
        std::ios_base::openmode mode = overwrite ? std::ios::trunc : std::ios::app;
        std::ofstream file(filename, mode);
        if (!file) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }
        for (int i = 0; i < currentSize; ++i) {
            file << data[i] << "\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
            return;
        }
        T value;
        while (file >> value) {
            pushBack(value);
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }
};
