/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Created by victor,
*/

#pragma once

#include <vector>

class Sound {
	public:
		Sound(float *data, int size);
		~Sound();

		float *getData();
		unsigned char *getEncodedData();
		int getSize();
		void setEncodedSize(int size) {
			_encodedSize = size;
		}
		int getEncodedSize() {
			return _encodedSize;
		}
	private:
		int _size;
		int _encodedSize;
		float *_clearedData;
		unsigned char *_encodedData;
};