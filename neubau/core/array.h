/*
 * array.h
 *
 *  Created on: 14-Apr-2009
 *      Author: fushunpoon
 */

#ifndef ARRAY_H_
#define ARRAY_H_

/**
 * Creates a new 2D array on the heap of a particular type.
 * @param row
 * @param col
 * @return
 */
template<typename T>
T **new_2DArr(int row, int col) {
	T **p = new T *[row];
	for (int j = 0; j < row; ++j){
		p[j] = new T[col];
	}
	return p;
}

/**
 * Deletes a 2D array of the heap of a particular type, given
 * the size in rows.
 * @param p
 * @param row
 */
template<typename T>
void delete_2DArr(T **p, int row) {
	for(int j = 0; j<row;++j){
		delete [] p[j];
	}
	delete [] p;
}



#endif /* ARRAY_H_ */
