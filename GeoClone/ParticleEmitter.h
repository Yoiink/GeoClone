#pragma once

#include <vector>
#include "GameObject.h"

enum ParticleType{ EXPLOSION, GEO_TRAIL };

class ParticleEmitter
{
public:

	ParticleEmitter(void);
	ParticleEmitter(float emitterX, float emitterY, int emitterType, int assetID, float emitAngle = NULL);
	~ParticleEmitter(void);

	void createExplosion();
	void createTrail();

	void update(const float &deltaTime);
	std::shared_ptr<GameObject> getParticle(int index);
	int getAmountParticles();
	bool getAlive();

	//struct Particle{
	//	Particle(float x, float y, float dirX, float dirY){
	//		posX = x;
	//		posY = y;
	//		directionX = dirX;
	//		directionY = dirY;
	//	}

	//	float posX, posY, directionX, directionY;
	//};

private:
	std::vector<std::shared_ptr<GameObject>> _particles;
	float _emitterX, _emitterY, _timeToLive, _timeLived, _emitAngle;
	int _emitterType, _assetID;
	bool _isAlive;

};