#pragma once

void InitEntity(UsedEntities & usedEntities, Entities & entities, Textures & textures, UsedSounds & usedSounds,
	UsedTexts & usedTexts, Font & font);

void InitMapUsedEnemies(vector<Enemy*> & enemiesInLevel, UsedEntities & usedEntities);

void InitTextMoney(Text & text, Font & font);

void InitMusics(UsedMusics & usedMusics);

void InitSounds(UsedSounds & sounds);