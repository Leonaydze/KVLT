#ifndef SERVICE_H
#define SERVICE_H

#include <vector>
#include "DataSource.h"

template <typename T>
class Service {
public:
	void create(DataSource<T>& dataSource, const T& item);
	vector<T> read(DataSource<T>& dataSource);
	void update(DataSource<T>& dataSource, const T& item);
	void remove(DataSource<T>& dataSource, int id);
};

#endif // !SERVICE_H