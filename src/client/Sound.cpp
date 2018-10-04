/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Created by victor,
*/

#include "Sound.hpp"

Sound::Sound(float *data, int size) :
_size(size), _clearedData(data)
{
	_encodedData = new unsigned char[_size];
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