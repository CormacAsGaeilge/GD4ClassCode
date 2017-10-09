#include "World.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow & window) 
	:mWindow(window), mWorldView(window.getDefaultView()),
	mTextures(),mSceneGraph(),mSceneLayers(),
	mWorldBounds(0.f,0.f,mWorldView.getSize().x, 2000.f),
	mSpawnPosition(mWorldView.getSize.x/2.f,mWorldBounds.height - mWorldView.getSize.y/2),
	mScrollSpeed(-50.f), mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();
	//Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	//Scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	//Move the player sideways, scout planes follow the leader
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//If the player touches the borders then flip direction
	if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left+mWorldBounds.width - 150) {
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}
	//apply the movements
	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
}

void World::buildScene()
{
}

//try and write the build scene method