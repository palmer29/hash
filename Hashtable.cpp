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
"hashtable.cpp" [dos] 89L, 1886B                                                83,37         Bot
