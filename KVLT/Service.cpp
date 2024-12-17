#include "Service.h"

template <typename T>
void Service<T>::create(DataSource<T>& dataSource, const T& item) {
	dataSource.create(item);
}
template <typename T>
T Service<T>::read(DataSource<T>& dataSource) {
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
template class Service<Player>;
template class Service<PlayerInventory>;
template class Service<PlayerWeapon>;
template class Service<Clergy>;