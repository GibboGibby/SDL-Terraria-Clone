#include "AssetManager.h"

AssetManager* AssetManager::instance = NULL;

AssetManager* AssetManager::Instance()
{
	if (instance == NULL)
		instance = new AssetManager();

	return instance;
}

void AssetManager::Release()
{
	delete instance;
	instance = NULL;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (auto tex : mTextures)
	{
		if (tex.second != NULL)
		{
			SDL_DestroyTexture(tex.second);
		}
	}

	mTextures.clear();

	for (auto text : mText)
		if (text.second != NULL)
			SDL_DestroyTexture(text.second);
	mText.clear();

	for (auto font : mFonts)
		if (font.second != NULL)
			TTF_CloseFont(font.second);

	mFonts.clear();
}

SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + filename);

	if (mTextures[fullpath] == nullptr)
		mTextures[fullpath] = Graphics::Instance()->LoadTexture(fullpath);

	return mTextures[fullpath];
}

TTF_Font* AssetManager::GetFont(std::string file, int size)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + file);
	std::string key = fullPath + (char)size;

	if (mFonts[key] == nullptr)
	{
		mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
		if (mFonts[key] == nullptr)
		{
			printf("Font Loading Error: Font-%s Error-%s\n", file.c_str(), TTF_GetError());
		}
	}

	return mFonts[key];

}

SDL_Texture* AssetManager::GetText(std::string text, std::string file, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(file, size);

	std::string key = text + file + (char)size + (char)color.r + (char)color.g + (char)color.b;

	if (mText[key] == nullptr)
		mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);

	return mText[key];
}

Mix_Music* AssetManager::GetMusic(std::string file)
{
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + file);

	if (mMusic[fullpath] == nullptr)
	{
		mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
	}

	if (mMusic[fullpath] == NULL)
		printf("Music loading error: file - %s, error - %s\n", file.c_str(), Mix_GetError());
	
	return mMusic[fullpath];
}

Mix_Chunk* AssetManager::GetSFX(std::string file)
{
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + file);

	if (mSFX[fullpath] == nullptr)
	{
		mSFX[fullpath] = Mix_LoadWAV(fullpath.c_str());
	}

	if (mSFX[fullpath] == NULL)
		printf("SFX loading error: file - %s, error - %s\n", file.c_str(), Mix_GetError());

	return mSFX[fullpath];
}