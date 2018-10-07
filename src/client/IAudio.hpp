/*
** EPITECH PROJECT, 2022
** Babel
** File description:
** Created by Swann,
*/
#ifndef BABEL_IAUDIO_HPP
#define BABEL_IAUDIO_HPP

class IAudio {
public:
	virtual void playAudio() = 0;
	virtual void recordAudio() = 0;
	virtual void initialize() = 0;
	virtual void startStream() = 0;
	virtual void openInputStream() = 0;
	virtual void openOutputStream() = 0;
	virtual void closeStream() = 0;
	virtual void terminate() = 0;

private:
};

#endif //BABEL_IAUDIO_HPP
