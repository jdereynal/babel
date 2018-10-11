/*
** EPITECH PROJECT, 2018
** babel
** File description:
** SoundSettings
*/

#ifndef SOUNDSETTINGS_HPP_
	#define SOUNDSETTINGS_HPP_

#include <portaudio.h>

#define PA_SAMPLE_TYPE paFloat32
#define SAMPLE_SILENCE (0.0f)

constexpr auto CHANNEL = 1;
constexpr auto FRAMESIZE = 480;
constexpr auto FREQUENCY = 24000;

#endif /* !SOUNDSETTINGS_HPP_ */
