/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Created by victor,
*/

#pragma once

#include <opus/opus.h>
#include "ICodec.hpp"
#include "SoundSettings.hpp"


class ACodec : public ICodec {
	public:
		ACodec();
		~ACodec();
		int decodeData(unsigned char *, unsigned long, float *);
		int encodeData(float *ptr, int size, unsigned char *dest);
		Sound encodeData(Sound sound) override;
		Sound decodeData(Sound sound) override;
		int getDecodedSize() const {
			return _decodedSize;
		}
	private:
		bool decoderCreate();
		bool encoderCreate();
		bool encoderDestroy();
		bool decoderDestroy();

		int _encodedSize;
		int _decodedSize;
		OpusDecoder *_decoder;
		OpusEncoder *_encoder;
};