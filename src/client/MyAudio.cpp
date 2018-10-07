/*
** EPITECH PROJECT, 2018
** babel
** File description:
** MyAudio
*/

#include <iostream>
#include "MyAudio.hpp"

int playHandler(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	MyAudio *audio = reinterpret_cast<MyAudio *>(userData);
	return audio->playCallback((float *)output, frameCount);
}

int recordHandler(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	MyAudio *audio = reinterpret_cast<MyAudio *>(userData);
	return audio->recordCallback((float *)input, frameCount);
}

MyAudio::MyAudio() : _stream(nullptr)
{
	PaError paErr;
	if ((paErr = Pa_Initialize()) != paNoError)
		std::cout << "PortAudio : initialization failed " << Pa_GetErrorText(paErr) << std::endl;
}

MyAudio::~MyAudio()
{
	PaError paErr;
	if ((paErr = Pa_Terminate()) != paNoError)
		std::cout << "PortAudio : terminate failed" << Pa_GetErrorText(paErr) << std::endl;
}

bool MyAudio::close()
{
	PaError paErr;

	if ((paErr = Pa_CloseStream(_stream)) != paNoError)
		std::cout << "PortAudio : Close stream failed " << Pa_GetErrorText(paErr) << std::endl;
	return paErr == paNoError;
}

bool MyAudio::open(TYPE type)
{
	PaError paErr;
	PaStreamParameters params;

	params.device = type == OUTPUT ? Pa_GetDefaultOutputDevice() : Pa_GetDefaultInputDevice();
	params.channelCount = CHANNEL;
	params.sampleFormat = PA_SAMPLE_TYPE;
	auto info = Pa_GetDeviceInfo(params.device);
	params.suggestedLatency = type == OUTPUT ? info->defaultLowOutputLatency : info->defaultLowInputLatency;
	params.hostApiSpecificStreamInfo = nullptr;

	if (type == OUTPUT) {
		paErr = Pa_OpenStream(&_stream, nullptr, &params, FREQUENCY, FRAMESIZE, paClipOff, playHandler, this);
	} else {
		paErr = Pa_OpenStream(&_stream, &params, nullptr, FREQUENCY, FRAMESIZE, paClipOff, recordHandler, this);
	}
	return paErr == paNoError;
}

bool MyAudio::start()
{
	PaError paErr;

	if ((paErr = Pa_StartStream(_stream) != paNoError))
		std::cout << "PortAudio : Can't start stream " << Pa_GetErrorText(paErr) << std::endl;
	return paErr == paNoError;
}

bool MyAudio::stop()
{
	PaError paErr;

	if ((paErr = Pa_StopStream(_stream) != paNoError))
		std::cout << "PortAudio : Can't stop stream " << Pa_GetErrorText(paErr) << std::endl;
	return paErr == paNoError;
}

int MyAudio::playCallback(float *ptr, unsigned long frameCount)
{
	if (_buffer.size() >= frameCount * CHANNEL) {
		auto pair = _buffer.array_one();
		for (unsigned long i = 0; i < frameCount * CHANNEL; i++) {
			ptr[i] = pair.first[i];
			_buffer.pop_front();
		}
	} else {
		for (unsigned long i = 0; i < frameCount * CHANNEL; i++)
			ptr[i] = 0.0f;
	}
	return paContinue;
}

int MyAudio::recordCallback(float *ptr, unsigned long frameCount)
{
	for (unsigned long i = 0; i < frameCount * CHANNEL; i++)
		if (ptr != nullptr)
			_buffer.push_back(ptr[i]);
		else
			_buffer.push_back(0.0f);
	if (_buffer.size() >= frameCount * CHANNEL * 5) {
		auto pair = _buffer.array_one();
		unsigned char *dest = new unsigned char[pair.second];
		int size = codec.encodeData(pair.first, pair.second, dest);
		emit readyAudio(dest, size);
		_buffer.clear();
	}
	return paContinue;
}