#include "pch.h"
#include "ContactListener.h"
#include "box2d/b2_contact.h"
#include "Bullet.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	//check if fixture A was a bullet
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    //check if fixture B was an enemy
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserDataA && bodyUserDataB)
	{
		const auto objectA = static_cast<Object*>(bodyUserDataA);
		const auto objectB = static_cast<Object*>(bodyUserDataB);

    	if(objectA && objectB)
    	{
    		//	check for bullet hit enemy
			{
				auto bullet = dynamic_cast<Bullet*>( objectA );
				auto enemy = dynamic_cast<Enemy*>( objectB );
    			if(bullet)
    			{
    				bullet->Hit();
    				if(enemy)
    				{
	    				enemy->Kill();
    				}
    				return;
    			}

				//	objects could be reversed
				bullet = dynamic_cast<Bullet*>( objectB );
				enemy = dynamic_cast<Enemy*>( objectA );
				
    			if(bullet)
    			{
    				bullet->Hit();
    				if(enemy)
    				{
	    				enemy->Kill();
    				}
    				return;
    			}
			}
    		//	Check for enemy hit player
			{
				auto player = dynamic_cast<Player*>( objectA );
				auto enemy = dynamic_cast<Enemy*>( objectB );
				if(player && enemy)
				{
					player->Kill();
					enemy->HitPlayer();	
				}
				player = dynamic_cast<Player*>( objectB );
				enemy = dynamic_cast<Enemy*>( objectA );
				if(player && enemy)
				{
					player->Kill();
					enemy->HitPlayer();					
				}
			}
    	}
	}
}
