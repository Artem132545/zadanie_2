#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <cstdlib>

class redirect_output_wrapper
{
    std::streambuf* const old_buf;
    std::ostream& stream;

public:
    redirect_output_wrapper(std::ostream& src)
        : old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper()
    {
        stream.rdbuf(old_buf);
    }

    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};

template <typename T>
void readValidNumber(T& value, const std::string& prompt,const T& a, const T& b = std::numeric_limits<T>::max())
{
    while (true)
    {
        std::cout << prompt;

        if (std::cin.peek() == EOF)
            std::exit(1);

        if (std::cin.peek() == ' ' ||
            std::cin.peek() == '\t' ||
            std::cin.peek() == '\n')
        {
            std::cout << "Wrong input" << std::endl;
            std::cin.ignore(10000, '\n');
            continue;
        }

        std::cin >> value;

        if (std::cin.fail() || std::cin.peek() != '\n')
        {
            if (std::cin.eof())
                std::exit(1);

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Wrong input" << std::endl;
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (value < a || value > b)
        {
            std::cout << "Wrong range" << std::endl;
            continue;
        }

        std::cerr << value << std::endl;
        return;
    }
}

inline void readValidName(std::string& name,const std::string& prompt)
{
    while (true)
    {
        std::cout << prompt;

        if (!std::getline(std::cin, name))
            std::exit(1);

        if (name.empty() ||
            name.front() == ' ' ||
            name.front() == '\t' ||
            name.back() == ' ' ||
            name.back() == '\t')
        {
            std::cout << "Wrong name" << std::endl;
            continue;
        }

        std::cerr << name << std::endl;
        return;
    }
}

template <typename Item>
void PrintID(const std::unordered_map<int, Item>& items)
{
    std::cout << "All ID: ";

    for (const auto& item : items)
        std::cout << item.first << " ";

    std::cout << '\n';
}

inline void PrintID(const std::vector<int>& ids)
{
    std::cout << "All ID: ";

    for (int id : ids)
        std::cout << id << " ";

    std::cout << '\n';
}

template <typename Item, typename Filter, typename T>
std::vector<int> findAndOutputObjectsByFilter(const std::unordered_map<int, Item>& items,Filter filter,const T& parameter)
{
    std::vector<int> result;

    for (const auto& item : items)
    {
        if (filter(item.second, parameter))
        {
            result.push_back(item.first);
            std::cout << item.second << '\n';
        }
    }

    return result;
}

template <typename Item>
bool checkByName(const Item& item, const std::string& name)
{
    return item.getName().find(name) != std::string::npos;
}

inline bool isFound(int id, const std::vector<int>& found_result)
{
    for (int x : found_result)
        if (x == id)
            return true;

    return false;
}

inline bool isDuplicate(int id, const std::vector<int>& selected_ids)
{
    for (int x : selected_ids)
        if (x == id)
            return true;

    return false;
}

inline std::vector<int> inputSpecificIDs(const std::vector<int>& found_result)
{
    std::vector<int> selected_ids;

    PrintID(found_result);

    while (true)
    {
        int id;

        readValidNumber(id, "Enter ID (0 - finish): ", 0);

        if (id == 0)
            break;

        if (!isFound(id, found_result))
        {
            std::cout << "ID is not among found pipes\n";
            continue;
        }

        if (isDuplicate(id, selected_ids))
        {
            std::cout << "ID already selected\n";
            continue;
        }

        selected_ids.push_back(id);
        std::cout << "ID selected\n";
    }

    return selected_ids;
}

template <typename Item>
void deleteObjectsByFilter( std::unordered_map<int, Item>& items, const std::vector<int>& result)
{
    for (int id : result)
        items.erase(id);
}
