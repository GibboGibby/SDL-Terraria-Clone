#include "AudioManager.h"

AudioManager* AudioManager::instance = NULL;

AudioManager* AudioManager::Instance()
{
	if (instance == NULL)
		instance = new AudioManager();

	return instance;
}

void AudioManager::Release()
{
	delete instance;
	instance = NULL;
}

AudioManager::AudioManager()
{
	mAssetMgr = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		printf("Mixer init error: %s\n", Mix_GetError());
}

AudioManager::~AudioManager()
{
	mAssetMgr = NULL;
	Mix_Quit();
}


void AudioManager::PlayMusic(std::string file, int loops)
{
	Mix_PlayMusic(mAssetMgr->GetMusic(file), loops);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::PlaySFX(std::string file, int loops, int channel)
{
	Mix_PlayChannel(channel, mAssetMgr->GetSFX(file), loops);
}