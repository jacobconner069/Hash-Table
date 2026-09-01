#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include<fstream>
#include<iostream>

template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size) : current_size{0}{
    vec.resize(prime_below(size));
}

template<typename K, typename V>
HashTable<K, V>::~HashTable(){
    makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K& k) const{
    auto & whichList = vec[myhash(k)];
    for (auto it = whichList.begin(); it != whichList.end(); ++it){
        if (it->first == k){
            return true;
        }
    }
    return false;

}

template<typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V>& kv) const{
    auto & whichList = vec[myhash(kv.first)];
    for (auto it = whichList.begin(); it != whichList.end(); ++it){
        if (it->first == kv.first && it->second == kv.second){
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V>& kv){
    auto & whichList = vec[myhash(kv.first)];
    for (auto it = whichList.begin(); it != whichList.end(); ++it){
        if (it->first == kv.first){
            if(it->second == kv.second){
                return false; // already exists
            }
            it->second = kv.second; 
            return true; 
        }
    }

    whichList.push_back(kv);
    if (++current_size > vec.size()){
        rehash();
    }
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V>&& kv){
    auto & whichList = vec[myhash(kv.first)];
    for (auto it = whichList.begin(); it != whichList.end(); ++it){
        if (it->first == kv.first){
            if(it->second == kv.second){
                return false; // already exists
            }
            it->second = std::move(kv.second);
            return true;
        }
    }

    whichList.push_back(std::move(kv));
    if (++current_size > vec.size()){
        rehash();
    }
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& k){
    auto & whichList = vec[myhash(k)];
    for (auto it = whichList.begin(); it != whichList.end(); ++it){
        if (it->first == k){
            whichList.erase(it);
            --current_size;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear(){
    makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char* filename){
    std::ifstream infile(filename);
    if (!infile){
        return false;
    }
    K key;
    V value;
    while (infile >> key >> value){
        insert(std::make_pair(key, value));
    }
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::dump() const{
    for (size_t i = 0; i < vec.size(); ++i){
        std::cout << "v[" << i << "]: ";
        for (const auto& kv : vec[i]){
            if(kv->next != nullptr){
                std::cout << kv.first << " " << kv.second << ": ";
            } else {
                std::cout << kv.first << " " << kv.second << " ";
            }
        }
        std::cout << std::endl;
    }
}

template<typename K, typename V>
size_t HashTable<K, V>::size() const{
    return current_size;
}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) const{
    std::ofstream outfile(filename);
    if (!outfile){
        return false;
    }
    for (const auto& bucket : vec){
        for (const auto& kv : bucket){
            outfile << kv.first << " " << kv.second << std::endl;
        }
    }
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::makeEmpty(){
    for (auto& bucket : vec){
        bucket.clear();
    }
    current_size = 0;
}

template<typename K, typename V>
void HashTable<K, V>::rehash(){
    std::vector<std::list<std::pair<K, V>>> oldVec = vec;
    vec.resize(prime_below(2 * oldVec.size()));
    for (auto& bucket : vec){
        bucket.clear();
    }
    current_size = 0;
    for (const auto& bucket : oldVec){
        for (const auto& kv : bucket){
            insert(kv);
        }
    }
}

template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k) const{
    std::hash<K> hashFunc;
    return hashFunc(k) % vec.size();
}

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	    return n;
      --n;
    }

  return 2;
}

template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

#endif
