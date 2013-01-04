#include "ParticleEmitter.h"

#define _USE_MATH_DEFINES
#include <math.h>

ParticleEmitter::ParticleEmitter(float emitterX, float emitterY, int emitterType, int assetID, float emitAngle){
	_emitterX = emitterX;
	_emitterY = emitterY;
	_emitterType = emitterType;
	_assetID = assetID;
	_timeLived = 0;
	_timeToLive = 0;
	_isAlive = true;
	_emitAngle = emitAngle;

	if(_emitterType == EXPLOSION)
		createExplosion();

	if(_emitterType == GEO_TRAIL)
		createTrail();
}

ParticleEmitter::~ParticleEmitter(void){
}

void ParticleEmitter::createExplosion(){

	_timeToLive = 1000;
	
	const int explosionParticles = 10; //Was 20..

	for(int particleCount = 0; particleCount < explosionParticles; particleCount++){
		float angle = (particleCount * (360.0f / explosionParticles));

		_particles.push_back(std::shared_ptr<GameObject>(new GameObject(4, 4, _emitterX, _emitterY, 1.f*cos(angle), 1.f*sin(angle), rand() % 3 + 1.f, angle + 1.5f, 2)));
		_particles.back()->setTexture(_assetID);
	}

}

void ParticleEmitter::createTrail(){

	_timeToLive = 500;
	
	const int trailParticles = 2; //Was 4..

	for(int particleCount = 0; particleCount < trailParticles; particleCount++){

		float randOffsetAngle = static_cast<float>((rand() % 40 - 20) * M_PI / 180.0);

		_particles.push_back(std::shared_ptr<GameObject>(new GameObject(2, 2, _emitterX, _emitterY, 1.f*cos(_emitAngle + randOffsetAngle), 1.f*sin(_emitAngle + randOffsetAngle), rand() % 2 + 1.f, _emitAngle + 1.5f, 2)));
		_particles.back()->setTexture(_assetID);
		_particles.back()->setMaxFrame(32);
	}

}

void ParticleEmitter::update(const float &deltaTime){
	for(std::shared_ptr<GameObject> particle : _particles){
		particle->setX(particle->getX() + (particle->getDirectionX() * particle->getSpeed()) * deltaTime);
		particle->setY(particle->getY() + (particle->getDirectionY() * particle->getSpeed()) * deltaTime);
		particle->updateFrame();
	}

	_timeLived += deltaTime * 10;

	if(_timeLived >= _timeToLive)
		_isAlive = false;
}

std::shared_ptr<GameObject> ParticleEmitter::getParticle(int index){
	return _particles[index];
}

int ParticleEmitter::getAmountParticles(){
	return static_cast<int>(_particles.size());
}

bool ParticleEmitter::getAlive(){
	return _isAlive;
}