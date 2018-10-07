/*
** EPITECH PROJECT, 2018
** babel
** File description:
** MyAudio
*/

#ifndef MYAUDIO_HPP_
	#define MYAUDIO_HPP_

#include <portaudio.h>
#include <boost/circular_buffer.hpp>
#include <QtCore/QObject>
#include "SoundSettings.hpp"
#include "ACodec.hpp"
#include "Sound.hpp"

#define BUFSIZE 4

class MyAudio : public QObject {
Q_OBJECT
private:
	boost::circular_buffer<float> _buffer{BUFSIZE * FREQUENCY * CHANNEL};
	PaStream *_stream;
	ACodec codec;
public:
	enum TYPE {
		INPUT,
		OUTPUT
	};
	MyAudio();
	~MyAudio();
	bool open(TYPE);
	bool start();
	bool stop();
	bool close();
	int playCallback(float *ptr, unsigned long frames);
	int recordCallback(float *ptr, unsigned long frames);
	PaStream *getStream() { return _stream;}
	boost::circular_buffer<float> *getBuffer() {
		return &_buffer;
	}
signals:
	void readyAudio(void *, int);
};

#endif /* !MYAUDIO_HPP_ */
