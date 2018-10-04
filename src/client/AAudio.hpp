/*
** EPITECH PROJECT, 2022
** Babel
** File description:
** Created by Swann,
*/

#include <vector>
#include "IAudio.hpp"

#ifndef BABEL_AAUDIO_HPP
#define BABEL_AAUDIO_HPP

#define CHANNELS (2)
#define FRAMERATE (48000)
#define BUFFERFRAME (480)
#define DURATION (5)

#define PA_SAMPLE_TYPE paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE (0.0f)

typedef struct s_portAudioData
{
	unsigned long 	index;
	unsigned long  	maxIndex;
	SAMPLE	*recorded;
}	t_portAudioData;

class AAudio : IAudio
{
public:
	AAudio();
	void recordAudio();
	void playAudio();
	void initialize();
	void startStream();
	void openInputStream();
	void openOutputStream();
	void closeStream();
	void terminate();
private:
	t_portAudioData _portAudioData;
	void *_stream;
	unsigned long _samples;
	unsigned long _bytes;
	public:
	t_portAudioData get_portAudioData() const
	{
		return _portAudioData;
	}

	void set_portAudioData(const t_portAudioData &_portAudioData)
	{
		AAudio::_portAudioData = _portAudioData;
	}

	void *get_stream() const
	{
		return _stream;
	}

	void set_stream(void *_stream)
	{
		AAudio::_stream = _stream;
	}

	unsigned long get_samples() const
	{
		return _samples;
	}

	void set_samples(unsigned long _samples)
	{
		AAudio::_samples = _samples;
	}

	unsigned long get_bytes() const
	{
		return (_bytes / sizeof(SAMPLE));
	}

	void set_bytes(unsigned long _bytes)
	{
		AAudio::_bytes = _bytes;
	}
};

#endif //BABEL_AAUDIO_HPP
