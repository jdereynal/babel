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
#define FRAMERATE (44100)
#define BUFFERFRAME (512)
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
};

#endif //BABEL_AAUDIO_HPP
