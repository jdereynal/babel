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
	private:
		int _size;
		float *_clearedData;
		unsigned char *_encodedData;
};