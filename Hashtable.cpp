#include "HashTable.h"
#include <vector>
#include <cstdlib>


HashTable::HashTable(size_t size) noexcept : _capacity(size), _filled(0)
{
    table.resize(_capacity);
}

size_t HashTable::hash_function(const KeyType &key) const
{
    size_t res = 0;
    for( const auto& i: key)
    {
	res = (res + i) % _capacity;
    }
    return static_cast<size_t>(res); 
} 

HashTable::~HashTable()
{}

void HashTable::insert(const KeyType &key, const ValueType &value)
{
    if (getLoadFactor() > 0.75)
    {
        _capacity *= 2;
        table.resize(_capacity);
        std::vector<std::list<std::pair<KeyType, ValueType>>> tempt;
        tempt.resize(_capacity);
	for (const auto& i: table)
        {
            for (const auto& j: i)
            {
                tempt[hash_function(j.first)].push_back(j);
            }
        }
	table = std::move(tempt);
    }
    for (auto& i: table[hash_function(key)])
    {
	    if (i.first == key)
	    {
		    i.second = value;
		    return;
	    }
    }
    table[hash_function(key)].push_back({key, value});
    ++_filled;
}

bool HashTable::find(const KeyType &key, ValueType &value) const
{
    for (const auto& i: table[hash_function(key)])
    {
        if ( i.first == key)
        {
	    value = i.second;
	    return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key)
{
    size_t size = table[hash_function(key)].size(); 
    table[hash_function(key)] = {};
    _filled -= size;
}

ValueType& HashTable::operator[](const KeyType &key)
{
    size_t index = hash_function(key);
    for (auto& i: table[index])
    {
	    if (i.first == key)
	    {
		    return i.second;
	    }
    }
    return table[index].back().second;
}

double HashTable::getLoadFactor()
{
    return static_cast<double>(_filled)/_capacity;
}
