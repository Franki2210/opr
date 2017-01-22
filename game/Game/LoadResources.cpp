#include "Header.h"
#include "LoadResources.h"

bool LoadTowerTextures(sf::Texture & tower1, sf::Texture & tower2, sf::Texture & tower3)
{
	return tower1.loadFromFile(PATH_TO_TEXTURES + "towers/gun_turret.png") &&
		tower2.loadFromFile(PATH_TO_TEXTURES + "towers/twin_gun_turret.png") &&
		tower3.loadFromFile(PATH_TO_TEXTURES + "towers/laser_turret.png");
}
bool LoadEnemiesTextures(TexturesEnemy & enemy1, TexturesEnemy & enemy2, TexturesEnemy & enemy3)
{
	return enemy1.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy1_run.png") &&
		enemy1.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy1_attack.png") &&
		enemy2.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy2_run.png") &&
		enemy2.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy2_attack.png") &&
		enemy3.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy3_run.png") &&
		enemy3.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy3_attack.png");
}
bool LoadPlayerTextures(TexturesPlayer & player)
{
	return player.idle.loadFromFile(PATH_TO_TEXTURES + "player_idle.png") &&
		player.run.loadFromFile(PATH_TO_TEXTURES + "player_run.png");
}
bool LoadPortalTexture(sf::Texture & portal)
{
	return portal.loadFromFile(PATH_TO_TEXTURES + "portal.png");
}
bool LoadCoinTexture(sf::Texture & coin)
{
	return coin.loadFromFile(PATH_TO_TEXTURES + "coin.png");
}
bool LoadMapTexture(sf::Texture & map)
{
	return map.loadFromFile(PATH_TO_TEXTURES + "map/map.png");
}
bool LoadBonusesTextures(TextureBonuses & bonuses)
{
	return bonuses.damageIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/damage_increase.png") &&
		bonuses.healthIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/health_increase.png") &&
		bonuses.speedIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/speed_increase.png") &&
		bonuses.fireAccelTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/fire_acceleration.png");
}
bool LoadBulletsTexture(TexturesBullets & bullets)
{
	return bullets.gunShot.loadFromFile(PATH_TO_TEXTURES + "bullets/bullet.png") &&
		bullets.twinGunShot.loadFromFile(PATH_TO_TEXTURES + "bullets/twin_bullet.png") &&
		bullets.laserShot.loadFromFile(PATH_TO_TEXTURES + "bullets/laser_bullet.png");
}
bool LoadMeteorTextures(TexturesMeteor & meteor)
{
	return meteor.texture.loadFromFile(PATH_TO_TEXTURES + "meteor/meteor.png") &&
		meteor.shadow.loadFromFile(PATH_TO_TEXTURES + "meteor/meteor_shadow.png") &&
		meteor.pointArrival.loadFromFile(PATH_TO_TEXTURES + "meteor/point_arrival.png");
}
bool LoadExplosionTexture(sf::Texture & explosion)
{
	return explosion.loadFromFile(PATH_TO_TEXTURES + "explosion/explosion.png");
}
bool LoadTowerExplosionTexture(sf::Texture & explosion)
{
	return explosion.loadFromFile(PATH_TO_TEXTURES + "explosion/explosion2.png");
}
bool LoadVignetteTexture(sf::Texture & vignette)
{
	return vignette.loadFromFile(PATH_TO_TEXTURES + "vignette.png");
}
bool LoadToxicCloudTexture(sf::Texture & toxicCloud)
{
	return toxicCloud.loadFromFile(PATH_TO_TEXTURES + "toxic_cloud.png");
}
bool LoadEnemyExplosionTexture(sf::Texture & enemyExplosion)
{
	return enemyExplosion.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy_explosion.png");
}

bool LoadTextures(Textures & textures)
{
	return LoadTowerTextures(textures.tower1, textures.tower2, textures.tower3) &&
		LoadEnemiesTextures(textures.enemy1, textures.enemy2, textures.enemy3) &&
		LoadPlayerTextures(textures.player) && 
		LoadPortalTexture(textures.portal) &&
		LoadPortalTexture(textures.portal) && 
		LoadCoinTexture(textures.coin) &&
		LoadMapTexture(textures.map) && 
		LoadBonusesTextures(textures.bonuses) &&
		LoadBonusesTextures(textures.bonuses) && 
		LoadBulletsTexture(textures.bullets) &&
		LoadMeteorTextures(textures.meteor) && 
		LoadExplosionTexture(textures.explosion) &&
		LoadTowerExplosionTexture(textures.towerExplosion) &&
		LoadVignetteTexture(textures.vignette) && 
		LoadToxicCloudTexture(textures.toxicCloud) &&
		LoadEnemyExplosionTexture(textures.enemyExplosion);
}

bool LoadShotsSounds(ShotSounds & gunShots, ShotSounds & laserShots)
{
	return gunShots.shot1Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/gunshot1.ogg") &&
		gunShots.shot2Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/gunshot2.ogg") &&
		gunShots.shot3Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/gunshot3.ogg") &&
		laserShots.shot1Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/laser1.ogg") &&
		laserShots.shot1Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/laser2.ogg") &&
		laserShots.shot1Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/laser3.ogg");
}
bool LoadStepSounds(StepsSounds & steps)
{
	return steps.step1.loadFromFile(PATH_TO_SOUNDS + "walking/walk1.ogg") &&
		steps.step2.loadFromFile(PATH_TO_SOUNDS + "walking/walk2.ogg") &&
		steps.step3.loadFromFile(PATH_TO_SOUNDS + "walking/walk3.ogg") &&
		steps.step4.loadFromFile(PATH_TO_SOUNDS + "walking/walk4.ogg");
}
bool LoadPlaceTowerSound(OneSound & placeTower)
{
	return placeTower.soundBuf.loadFromFile(PATH_TO_SOUNDS + "place_tower/place.ogg");
}
bool LoadDropItemSound(OneSound & dropItem)
{
	return dropItem.soundBuf.loadFromFile(PATH_TO_SOUNDS + "drop_item.wav");
}
bool LoadEvilLaughSound(OneSound & evilLaugh)
{
	return evilLaugh.soundBuf.loadFromFile(PATH_TO_SOUNDS + "evil_laugh.ogg");
}
bool LoadExplosionSound(OneSound & explosion)
{
	return explosion.soundBuf.loadFromFile(PATH_TO_SOUNDS + "explosion.ogg");
}
bool LoadHeartbeatSound(OneSound & heartbeat)
{
	return heartbeat.soundBuf.loadFromFile(PATH_TO_SOUNDS + "heartbeat.ogg");
}

bool LoadSounds(UsedSounds & sounds)
{
	return LoadShotsSounds(sounds.gunShots, sounds.laserShots) &&
		LoadStepSounds(sounds.steps) && LoadPlaceTowerSound(sounds.placeTower) &&
		LoadDropItemSound(sounds.dropItem) && LoadEvilLaughSound(sounds.evilLaugh) &&
		LoadExplosionSound(sounds.explosion) && LoadHeartbeatSound(sounds.heartbeat);
}

bool LoadFont(sf::Font & font)
{
	return font.loadFromFile(PATH_TO_FONTS + "font.ttf");
}