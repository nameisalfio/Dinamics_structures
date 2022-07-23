#ifndef VERTEX_H
#define VERTEX_H

template<typename T>
class vertex{

		T key;

		template<typename C>
		friend class Graph;

	public:

		vertex(T key) : key(key){}

		vertex() : vertex(NULL){}

		bool operator== (vertex<T>& v){return this->key == v.key;}

		T get_key(){return key;}

		friend ostream& operator<< (ostream& os, const vertex<T> v){ return os << v.key;}
};

#endif