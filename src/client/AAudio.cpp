/*
** EPITECH PROJECT, 2022
** Babel
** File description:
** Created by Swann,
*/

#include <portaudio.h>
#include <iostream>
#include <zconf.h>
#include "AAudio.hpp"

int recordCallback(const void *input, void *output, unsigned long frameCount,
	const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	(void) output;
	(void) timeInfo;
	(void) statusFlags;
	int finished;
	unsigned long buffer;
	auto *paData = (t_portAudioData *)userData;
	auto *read_ptr = (const SAMPLE*)input;
	unsigned long frames = paData->maxIndex - paData->index;
	SAMPLE *write_ptr = &paData->recorded[paData->index * CHANNELS];

	if (frames < frameCount)
	{
		buffer = frames;
		finished = paComplete;
	}
	else
	{
		buffer = frameCount;
		finished = paContinue;
	}
	if (input == nullptr)
		for (unsigned long i = 0; i < buffer; i++)
		{
			*write_ptr++ = SAMPLE_SILENCE;
			if (CHANNELS == 2)
				*write_ptr++ = SAMPLE_SILENCE;
		}
	else
		for (unsigned long i = 0; i < buffer; i++)
		{
			*write_ptr++ = *read_ptr++;
			if (CHANNELS == 2)
				*write_ptr++ = *read_ptr++;
		}
	paData->index += buffer;
	return (finished);
}

int playCallback(const void *input, void *output, unsigned long frameCount,
	const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	(void) input;
	(void) timeInfo;
	(void) statusFlags;
	unsigned long  i;
	int finished;
	auto *paData = (t_portAudioData *)userData;
	SAMPLE *read_ptr = &paData->recorded[paData->index * CHANNELS];
	unsigned long  frames = paData->maxIndex - paData->index;
	auto *write_ptr = (SAMPLE*) output;

	if (frames < frameCount)
	{
		for (i = 0; i < frames; i++)
		{
			*write_ptr++ = *read_ptr++;
			if (CHANNELS == 2)
				*write_ptr++ = *read_ptr++;
		}
		for (; i < frameCount; i++)
		{
			*write_ptr++ = 0;
			if (CHANNELS == 2)
				*write_ptr++ = 0;
		}
		paData->index += frames;
		finished = paComplete;
	}
	else
	{
		for (i = 0; i < frameCount; i++)
		{
			*write_ptr++ = *read_ptr++;
			if (CHANNELS == 2)
				*write_ptr++ = *read_ptr++;
		}
		paData->index += frameCount;
		finished = paContinue;
	}
	return (finished);
}

AAudio::AAudio()
{
	PaStream *stream = nullptr;
	unsigned long  bytes;
	unsigned long  samples;
	unsigned long  totFrame;

	_stream = stream;
	_portAudioData.maxIndex = totFrame = DURATION * FRAMERATE;
	samples = totFrame * CHANNELS;
	bytes = samples * sizeof(SAMPLE);
	_portAudioData.recorded = (SAMPLE *)malloc(bytes);
	for (unsigned long i = 0; i < samples; i++)
		_portAudioData.recorded[i] = 0;
}

void AAudio::recordAudio()
{
	while ((Pa_IsStreamActive(_stream)) == 1)
		Pa_Sleep(1000);
}

void AAudio::playAudio()
{
	while ((Pa_IsStreamActive(_stream)) == 1)
		Pa_Sleep(100);
}

void AAudio::startStream()
{
	PaError paErr;

	if ((paErr = Pa_StartStream(_stream) != paNoError))
		std::cout << "PortAudio : Can't start stream "
			<< Pa_GetErrorText(paErr) << std::endl;
}

void AAudio::initialize()
{
	PaError paErr;

	if ((paErr = Pa_Initialize()) != paNoError)
		std::cout << "PortAudio : initialization failed "
			<< Pa_GetErrorText(paErr) << std::endl;
}

void AAudio::terminate()
{
	PaError paErr;

	if ((paErr = Pa_Terminate()) != paNoError)
		std::cout << "PortAudio : terminate failed"
			<< Pa_GetErrorText(paErr) << std::endl;
}

void AAudio::closeStream()
{
	PaError paErr;

	if ((paErr = Pa_CloseStream(_stream)) != paNoError)
		std::cout << "PortAudio : Close stream failed "
			<< Pa_GetErrorText(paErr) << std::endl;
}

void AAudio::openOutputStream()
{
	PaError paErr;
	PaStreamParameters output;

	_portAudioData.index = 0;
	output.device = Pa_GetDefaultOutputDevice();
	output.channelCount = CHANNELS;
	output.sampleFormat = PA_SAMPLE_TYPE;
	output.suggestedLatency = Pa_GetDeviceInfo((output.device))->defaultLowOutputLatency;
	output.hostApiSpecificStreamInfo = nullptr;

	if ((paErr = Pa_OpenStream(&_stream, nullptr, &output, FRAMERATE, BUFFERFRAME, paClipOff, playCallback, &_portAudioData)))
		std::cout << "PortAudio : can't Open stream " << Pa_GetErrorText(paErr) << std::endl;
}

void AAudio::openInputStream()
{
	PaError paErr;
	PaStreamParameters input;

	input.device = Pa_GetDefaultInputDevice();
	input.channelCount = CHANNELS;
	input.sampleFormat = PA_SAMPLE_TYPE;
	input.suggestedLatency = Pa_GetDeviceInfo((input.device))->defaultLowInputLatency;
	input.hostApiSpecificStreamInfo = nullptr;

	if ((paErr = Pa_OpenStream(&_stream, &input, nullptr, FRAMERATE, BUFFERFRAME, paClipOff, recordCallback, &_portAudioData)))
		std::cout << "PortAudio : can't Open stream " << Pa_GetErrorText(paErr) << std::endl;
}

// Main Example Audio
// g++ AAudio.cpp IAudio.hpp AAudio.hpp --std=c++17 -lrt -lasound -ljack -lpthread -lportaudio -Wall -Werror -Wextra

/*int main()
{
	AAudio portAudio;

	portAudio.initialize();

	portAudio.openInputStream(); ////////////////////////////
	portAudio.startStream();
	portAudio.recordAudio();	//record
	portAudio.closeStream();    /////////////////////////////

	portAudio.openOutputStream(); /////////////////////////////
	portAudio.startStream();
	portAudio.playAudio();		//play
	portAudio.closeStream(); /////////////////////////////

	portAudio.terminate();
}*/