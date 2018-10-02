/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Created by victor,
*/

#include "ACodec.hpp"

ACodec::ACodec() :
_encodedSize(0), _decodedSize(0), _decoder(nullptr), _encoder(nullptr)
{
	decoderCreate();
	encoderCreate();
}

ACodec::~ACodec()
{
	decoderDestroy();
	encoderDestroy();
}

bool ACodec::decoderCreate()
{
	int error;

	_decoder = opus_decoder_create(FREQUENCY, CHANNELS, &error);
	if (error != OPUS_OK) {
		std::cerr << "Decoder couldn't be created" << std::endl;
		return (false);
	}
	return (true);
}

bool ACodec::encoderCreate()
{
	int error;

	_encoder = opus_encoder_create(FREQUENCY, CHANNELS, OPUS_APPLICATION_VOIP, &error);
	if (error != OPUS_OK) {
		std::cerr << "Encoder couldn't be created" << std::endl;
		return (false);
	}
	return (true);
}

Sound ACodec::encodeData(Sound sound)
{
	if (_encoder != nullptr) {
		_encodedSize = opus_encode_float(_encoder, sound.getData(),
			FRAMESIZE, sound.getEncodedData(), sound.getSize());
		if (_encodedSize < 0)
			std::cerr << "Encoding of data failed..." << std::endl;
	}
	return (sound);
}

Sound ACodec::decodeData(Sound sound)
{
	if (_decoder != nullptr) {
		_decodedSize = opus_decode_float(_decoder, sound.getEncodedData(),
			sound.getSize(), sound.getData(), FRAMESIZE, 0);
		if (_decodedSize < 0)
			std::cerr << "Decoding of data failed..." << std::endl;
	}
	return (sound);
}

bool ACodec::encoderDestroy()
{
	if (_encoder) {
		opus_encoder_destroy(_encoder);
		return (true);
	}
	return (false);
}

bool ACodec::decoderDestroy()
{
	if (_decoder) {
		opus_decoder_destroy(_decoder);
		return (true);
	}
	return (false);
}