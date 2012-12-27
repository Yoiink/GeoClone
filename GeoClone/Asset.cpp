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

	//for(int frame = 0; frame < _assetArray.size(); frame++){
	//	delete _assetArray[frame];
	//	//_assetArray[frame] = NULL;
	//}

	//Had to initialise as _assetData(0) due to an asset not loading data. - Possibly due to sound file does not have any assetData!
	delete[] _assetData;

}

bool Asset::Load(const std::string &assetPath, int assetType, std::string assetName, int assetID){

	_assetName = assetName;
	_assetID = assetID;

	if(assetType == LOAD_IMAGE){
		if(HAPI->LoadTexture(assetPath, &_assetData, &_width, &_height)){
			//_assetArray.push_back(_assetData);
			//delete _assetData;
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

bool Asset::loadAnimation(int numFrames, int frameWidth, int frameHeight){

	//delete[] _assetArray.front();
	//_assetArray.pop_back();
	//_assetArray.empty();
	//_assetArray.pop_back();

	_maxFrames = numFrames;

	int sizeOfFrame = (frameWidth * frameHeight) * 4;
	_assetArray.reserve(sizeOfFrame * numFrames);

	//BYTE* tempData = new BYTE[frameWidth * 4];

	int startFrameX = 0;
	int startFrameY = 0;

	for(int curFrame = 0; curFrame < numFrames; curFrame++){

		BYTE* frameData = new BYTE[sizeOfFrame];

		if(startFrameX * frameWidth >= _width){
			startFrameX = 0;
			startFrameY++;
		}

		//int startOffset = (((startFrameY * frameHeight) * _width) + (startFrameX * frameWidth)) * 4;
		int startOffset =  (((startFrameY * frameHeight) * _width) * 4) + (startFrameX * frameWidth) * 4;

		for(int curY = 0; curY < frameHeight; curY++){
			//Copy to the array
			memcpy(&frameData[(curY * frameWidth) * 4], &_assetData[startOffset + ((curY * _width) * 4)], (frameWidth * 4));

			//_assetArray.insert(_assetArray.end(), _assetData + (startOffset + ((curY * _width) * 4)), _assetData + ((startOffset + ((curY * _width) * 4)) + (frameWidth * 4)));

			//int frameDataOffset = (curY * frameWidth) * 4;
			//int assetDataOffset = 0 + (curY * _width) * 4;
			//int frameJump = frameWidth * 4;
		}

		startFrameX++;
		_assetArray.push_back(frameData);
		//delete[] frameData;

	}

	////Now setup the texture width/height to that of the animated frames
	_width = frameWidth;
	_height = frameHeight;

	//delete[] _assetArray.front();
	//_assetArray.pop_back();

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