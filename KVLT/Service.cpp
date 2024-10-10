#include "Service.h"
#include "Task.h"

template <typename T>
void Service<T>::create(DataSource<T>& dataSource, const T& item) {
	dataSource.create(item);
}
template <typename T>
vector<T> Service<T>::read(DataSource<T>& dataSource) {
	return dataSource.read();
}
template <typename T>
void Service<T>::update(DataSource<T>& dataSource, const T& item) {
	dataSource.update(item);
}
template <typename T>
void Service<T>::remove(DataSource<T>& dataSource, int id) {
	dataSource.remove(id);
}

//explicit implementation
template class Service<Task>;