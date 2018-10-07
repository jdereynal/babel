/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Created by victor,
*/

#include <algorithm>
#include "Sound.hpp"

Sound::Sound(float *data, int size) :
_size(size)
{
	_encodedData = new unsigned char[_size];
	_clearedData = new float[_size];
	std::copy_n(data, _size, _clearedData);
}

Sound::Sound(unsigned char *data, int size, bool encoded)
{
	if (encoded) {
		_encodedData = new unsigned char[_size];
		_clearedData = new float[5 * FRAMESIZE * CHANNEL];
		std::copy_n(data, size, _encodedData);
	}
}


Sound::~Sound()
{
}

unsigned char *Sound::getEncodedData()
{
	return _encodedData;
}

float *Sound::getData()
{
	return _clearedData;
}

int Sound::getSize()
{
	return _size;
}