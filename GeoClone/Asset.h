#pragma once

#include <HAPI_lib.h>
#include <memory>
#include <vector>

enum assetType{LOAD_IMAGE, LOAD_AUDIO};

class Asset
{
public:
	Asset(void);
	~Asset(void);

	bool Load(const std::string &assetPath, int assetType, std::string assetName, int assetID);
	bool loadAnimation(int numFrames, int frameWidth, int frameHeight);

	//Getters
	BYTE* getTexture() const;
	BYTE* getTexture(int frameNumber) const;
	const int getSound() const;
	const int getWidth() const;
	const int getHeight() const;
	int getMaxFrame() const;
	std::string getName() const;
	int getID() const;

private:
	std::vector<BYTE*> _assetArray;
	
	BYTE* _assetData;
	int _width, _height, _soundID, _maxFrames, _assetID;

	std::string _assetName;
};

