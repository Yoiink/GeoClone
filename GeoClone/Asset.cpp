#include "Asset.h"
#include <vector>


Asset::Asset(void) : _width(0), _height(0), _soundID(0), _maxFrames(0), _assetData(0), _assetName(""), _assetID(0)
{
}

Asset::~Asset(void)
{
	//Loop over and delete the exploded asset data created
	for(BYTE* frame : _assetArray){
		delete[] frame;
	}

	//Had to initialise as _assetData(0) due to an asset not loading data. - Possibly due to sound file does not have any assetData!
	delete[] _assetData;

}

//Load the asset, assetType is either LOAD_IMAGE or LOAD_AUDIO
bool Asset::Load(const std::string &assetPath, int assetType, std::string assetName, int assetID){

	_assetName = assetName;
	_assetID = assetID;

	if(assetType == LOAD_IMAGE){
		if(HAPI->LoadTexture(assetPath, &_assetData, &_width, &_height)){
			return true;
		} else {
			HAPI->UserMessage("Unable to load '" + assetPath + "'. \n\n GeoClone will now close.", "Error Loading");
			return false;
		}
	} else if(assetType == LOAD_AUDIO) {
		if(HAPI->LoadSound(assetPath, &_soundID)){
			return true;
		} else {
			HAPI->UserMessage("Unable to load '" + assetPath + "'. \n\n GeoClone will now close.", "Error Loading");
			return false;
		}
	} else {
		return false;
	}
}

//Loads an animation from the previously loaded asset, it will take frames specified from the width and height from top left to right, and continue's down the image.
bool Asset::loadAnimation(int numFrames, int frameWidth, int frameHeight){

	_maxFrames = numFrames;

	int sizeOfFrame = (frameWidth * frameHeight) * 4;
	_assetArray.reserve(sizeOfFrame * numFrames);

	int startFrameX = 0;
	int startFrameY = 0;

	for(int curFrame = 0; curFrame < numFrames; curFrame++){

		BYTE* frameData = new BYTE[sizeOfFrame];

		if(startFrameX * frameWidth >= _width){
			startFrameX = 0;
			startFrameY++;
		}


		int startOffset =  (((startFrameY * frameHeight) * _width) * 4) + (startFrameX * frameWidth) * 4;

		for(int curY = 0; curY < frameHeight; curY++){
			memcpy(&frameData[(curY * frameWidth) * 4], &_assetData[startOffset + ((curY * _width) * 4)], (frameWidth * 4));		//Copy the strip of pixels to the frameData
		}

		startFrameX++;
		_assetArray.push_back(frameData);

	}

	//Now setup the texture width/height to that of the animated frames (By default, it will be bigger)
	_width = frameWidth;
	_height = frameHeight;

	return true;

}

BYTE* Asset::getTexture() const{
	return _assetData;
}

BYTE* Asset::getTexture(int frameNumber) const{
	return _assetArray[frameNumber];
}

const int Asset::getSound() const{
	return _soundID;
}

const int Asset::getWidth() const{
	return _width;
}

const int Asset::getHeight() const{
	return _height;
}

int Asset::getMaxFrame() const{
	return _maxFrames;
}

std::string Asset::getName() const{
	return _assetName;
}

int Asset::getID() const{
	return _assetID;
}