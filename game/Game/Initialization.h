#pragma once

void InitEntity(UsedEntities & usedEntities, Entities & entities, Textures & textures, UsedSounds & usedSounds,
	UsedTexts & usedTexts);

void InitMeteorSpawnTimer(Timer & meteorSpawnTimer);
void InitEvilLaughTimer(Timer & timer);

void InitEnemySpawn(UsedEntities & usedEntities);

void InitTextMoney(UsedTexts & usedTexts);

void InitMusics(UsedMusics & usedMusics);

void InitSounds(UsedSounds & sounds);