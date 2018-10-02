/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Created by victor,
*/

#pragma once

#include <iostream>
#include "Sound.hpp"

class ICodec {
	public:
		virtual Sound encodeData(Sound sound) = 0;
		virtual Sound decodeData(Sound encodedSound) = 0;
};