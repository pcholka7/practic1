#include <iostream>
#include <stdexcept>
#include <memory>

template<typename T>
struct BucketList
{
private:
    struct Element
    {
        std::string key;    // Ключ
        T value;            // Значение
        std::unique_ptr<Element> next; // Указатель на следующий элемент

        Element(const std::string& key, const T& value)
            : key(key), value(value), next(nullptr) {}
    };

    std::unique_ptr<Element> first;  // Первый элемент списка
    Element* last;                   // Последний элемент списка

public:
    BucketList() : last(nullptr) {}

    bool isEmpty() const
    {
        return !first;
    }

    T fetch(const std::string& key) const
    {
        Element* currentElement = first.get();
        while (currentElement && currentElement->key != key)
            currentElement = currentElement->next.get();

        if (currentElement)
            return currentElement->value;

        throw std::runtime_error("Key not found");
    }

    void insert(const std::string& key, const T& value)
    {
        auto newElement = std::make_unique<Element>(key, value);
        if (isEmpty())
        {
            first = std::move(newElement);
            last = first.get();
            return;
        }

        last->next = std::move(newElement);
        last = last->next.get();
    }

    void erase(const std::string& key)
    {
        if (isEmpty()) return;

        if (first->key == key)
        {
            first = std::move(first->next);
            if (!first) last = nullptr;
            return;
        }

        Element* previous = first.get();
        Element* current = previous->next.get();

        while (current)
        {
            if (current->key == key)
            {
                previous->next = std::move(current->next);
                if (!previous->next) last = previous;
                return;
            }
            previous = current;
            current = current->next.get();
        }
    }

    void display() const
    {
        Element* currentElement = first.get();
        while (currentElement)
        {
            std::cout << "[" << currentElement->key << ": " << currentElement->value << "] ";
            currentElement = currentElement->next.get();
        }
        std::cout << std::endl;
    }

    void displayValues() const
    {
        Element* currentElement = first.get();
        while (currentElement)
        {
            std::cout << "[" << currentElement->value << "] ";
            currentElement = currentElement->next.get();
        }
    }
};

template<typename T>
struct HashTable
{
private:
    uint32_t tableSize;
    std::unique_ptr<BucketList<T>[]> table;
    uint32_t currentElements;

    uint32_t computeHash(const std::string& key) const
    {
        uint32_t hash = 5381;
        for (char c : key)
        {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % tableSize;
    }

public:
    HashTable() : tableSize(20), currentElements(0)
    {
        table = std::make_unique<BucketList<T>[]>(tableSize);
    }

    HashTable(int size) : tableSize(size), currentElements(0)
    {
        table = std::make_unique<BucketList<T>[]>(tableSize);
    }

    void insertElement(const std::string& key, const T& value)
    {
        uint32_t index = computeHash(key);  // Получаем индекс
        try {
            // Пытаемся получить текущее значение по ключу
            T currentValue = table[index].fetch(key);
            // Если значение существует, перезаписываем его
            table[index].erase(key);  // Удаляем старое значение
            table[index].insert(key, value);  // Добавляем новое значение
        }
        catch (const std::runtime_error&) {
           
            table[index].insert(key, value);
            currentElements += 1;  // Увеличиваем размер хэш-таблицы
        }
    }

    T fetchElement(const std::string& key)
    {
        uint32_t index = computeHash(key);  // Получаем индекс
        return table[index].fetch(key);  // Возвращаем значение
    }

    void deleteElement(const std::string& key)
    {
        uint32_t index = computeHash(key);  // Получаем индекс
        table[index].erase(key);  // Удаляем элемент
        currentElements -= 1;  // Уменьшаем размер хэш-таблицы
    }

    uint32_t size() const
    {
        return currentElements;
    }

    void display() const
    {
        for (uint32_t i = 0; i < tableSize; ++i)
        {
            std::cout << "Bucket " << i << ": ";
            table[i].display();
        }
    }

    void displayValues() const
    {
        for (uint32_t i = 0; i < tableSize; ++i)
        {
            std::cout << "Bucket " << i << ": ";
            table[i].displayValues();
        }
    }
};
