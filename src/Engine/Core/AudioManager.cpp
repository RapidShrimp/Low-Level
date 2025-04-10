#pragma once
#include "AudioManager.h"
#include "Engine/Core/Libs/GameFunctionLib.h"

void AudioManger::PlaySound(std::string AudioFilePath, unsigned int Priority)
{
	//sf::SoundBuffer Buffer;
	//if (!Buffer.loadFromFile(AudioFilePath)) {
	//	Debug::Log(nullptr, Error, "No File Found for Audio");
	//	return;
	//}

	//sf::Sound NewSound(Buffer);
	//NewSound.play();
}

void AudioManger::PlayMusic(std::string MusicFilePath, bool IsLooping)
{
	//sf::Music Music;

	//if (!Music.openFromFile(MusicFilePath)) {
	//	Debug::Log(nullptr, Error, "No File Found for Music");
	//	return;
	//}
}
