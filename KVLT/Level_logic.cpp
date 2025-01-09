#include "Level_logic.h"

double _lastUpdateTime = static_cast <double>(0);
/// <summary>
/// A function to indicate that the code is stopped for a while
/// </summary>
/// <param name="interval - "> The time for which the code will stop</param>
/// <returns></returns>
bool TriggerEvent(float interval) {
	float currentTime = static_cast<float>(GetTime());

	if (currentTime - _lastUpdateTime >= interval) {
		_lastUpdateTime = currentTime;

		return true;
	}

	return false;
}

double _lUT = static_cast <double>(0);
/// <summary>
/// A function to indicate that the code is stopped for a while
/// </summary>
/// <param name="interval - "> The time for which the code will stop</param>
/// <returns></returns>
bool TakeDamageTime(float interval) {
	float currentTime = static_cast<float>(GetTime());

	if (currentTime - _lUT >= interval) {
		_lUT = currentTime;

		return true;
	}

	return false;
}

_gameScreen _currentScreen = mainMenu;

_gameScreen GetCurrentGameScreen() {
	return _currentScreen;
}
void SetCurrentScreen(_gameScreen curScreen) {
	_currentScreen = curScreen;
}

_gameScreen lastScreen = GetCurrentGameScreen();

_gameScreen GetLastGameScreen() {
	return lastScreen;
}
void SetLastGameScreen(_gameScreen gameScreen) {
	lastScreen = gameScreen;
}

Vector2 _lastPlayerPosition = {};

Vector2 GetLastPlayerPosition() {
	return _lastPlayerPosition;
}
void SetLastPlayerPosition(Vector2 lastPlayerPosition) {
	_lastPlayerPosition = lastPlayerPosition;
}

Priest priest = Priest({ 2900, 910 });

Boulder boulderTest = Boulder({ 2640.0f, 100.0f }, 50.0f, WHITE);

Vector2 _lastAltarPosition = {};
Altar _altars[5];

Texture2D _deathScreen;
Sound _deathScreenS;
Texture2D _backgrounds[5];
Texture2D _grounds[5];

Font font;

Vampire _vampire[4];

Font GetCurrentFont() {
	return font;
}

void Init()
{
	_deathScreen = LoadTexture("Sprites\\Death_screen.png");
	_deathScreenS = LoadSound("Sounds\\Death_screen.mp3");
	SetSoundVolume(_deathScreenS, 0.8f);
	_vampire[0] = Vampire({3600.0f, 900.0f});
	_vampire[0].Init();
	_altars[0] = Altar();
	_altars[1] = Altar({3200.0f, 900.0f});
	_altars[1].Init();
	font = LoadFont("Font.png");;
	priest.Init();
	boulderTest.Init();

	_backgrounds[0] = LoadTexture("Background\\Battleground4_t.png");
	_backgrounds[0].width = static_cast<int>(_backgrounds[0].width * 1.7f);
	_backgrounds[0].height = static_cast<int>(_backgrounds[0].height * 1.5f);

	_grounds[0] = LoadTexture("Background\\Ground4.png");
	_grounds[0].width = static_cast<int>(_grounds[0].width * 1.7f);
	_grounds[0].height = static_cast<int>(_grounds[0].height / 1.5f);

	_backgrounds[1] = LoadTexture("Background\\Battleground1_t.png");
	_backgrounds[1].width = static_cast<int>(_backgrounds[0].width * 1.7f);
	_backgrounds[1].height = static_cast<int>(_backgrounds[0].height * 1.2f);

	_grounds[1] = LoadTexture("Background\\Ground1.png");
	_grounds[1].width = static_cast<int>(_grounds[1].width * 2.7f);
	_grounds[1].height = static_cast<int>(_grounds[1].height / 1.5f);
}

template <typename T>
void EnemyAttacksThePlayer(T& enemy, Player& player) {
	if (player.GetPlayerHealth() > 0 && player.GetPlayerPositionX() + 128 >= enemy.GetEnemyPosX() + 20 && player.GetPlayerPositionX() <= enemy.GetEnemyPosX() + 120
		&& player.GetPlayerPositionY() + 128 >= enemy.GetEnemyPosY() - 30 && player.GetPlayerPositionY() <= enemy.GetEnemyPosY() + 140 && enemy.GetEnemyHealth() > 0) {
		if (TakeDamageTime(enemy.GetEnemyAttackSpeed())) {
			player.PlayerTakesDamage(enemy.GetEnemyDamage());
			player.DamageSound();
			if (typeid(enemy) == typeid(Vampire)) {
				enemy.StealHP(2);
			}
		}
	}
}

template <typename T>
void PlayerAttacksEnemy(T& enemy, Player& player, PlayerWeapon& pw) {
	if (player.GetPlayerHealth() > 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && enemy.TakeDamageTime(pw.GetWeaponSpeed())) {
		pw.AttackSound();
		if (player.GetPlayerPositionX() + 128 >= enemy.GetEnemyPosX() - 80 && player.GetPlayerPositionX() <= enemy.GetEnemyPosX() + 212
			&& player.GetPlayerPositionY() >= enemy.GetEnemyPosY() - 80 && player.GetPlayerPositionY() + 128 <= enemy.GetEnemyPosY() + 212) {
			enemy.EnemyGetDamage(pw.GetWeaponDamage());
		}
	}
}

template <typename T>
void EnemyGoesToThePlayer(T& enemy, Player& player) {
	if (player.GetPlayerPositionX() + 128 >= enemy.GetEnemyPosX() - 250
		&& player.GetPlayerPositionX() + 128 <= enemy.GetEnemyPosX() + 128 && enemy.GetEnemyHealth() > 0) {
		enemy.EnemyMoveX(-enemy.GetEnemySpeed());
		enemy.SetFrameRecWidth(-enemy.GetFrameRecWidth());
	}
	if (player.GetPlayerPositionX() + 128 <= enemy.GetEnemyPosX() + 378
		&& player.GetPlayerPositionX() >= enemy.GetEnemyPosX() && enemy.GetEnemyHealth() > 0) {
		enemy.EnemyMoveX(enemy.GetEnemySpeed());
		enemy.SetFrameRecWidth(enemy.GetFrameRecWidth());
	}
}

template <typename T>
bool EnemyOnGround(T& enemy, Ground& ground) {
	return (enemy.GetEnemyPosX() + 80 >= ground.GetGroundPositionX() && enemy.GetEnemyPosX() <= ground.GetGroundPositionX() + ground.GetGroundWidth()
		&& enemy.GetEnemyPosY() + 132 >= ground.GetGroundPositionY() + 15 && enemy.GetEnemyPosY() <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}

bool PlayerOnGround(Player& player, Ground& ground) {
	return (player.GetPlayerPositionX() + 88 >= ground.GetGroundPositionX() && player.GetPlayerPositionX() + 40 <= ground.GetGroundPositionX() + ground.GetGroundWidth()
		&& player.GetPlayerPositionY() + 128 >= ground.GetGroundPositionY() + 15 && player.GetPlayerPositionY() + 108 <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}

bool PlayerCantWalk(Player& player, Border& border) {
	if (player.GetPlayerPositionX() + 120 >= border.GetBorderPosX() && player.GetPlayerPositionX() + 120 <= border.GetBorderPosX() + 10
		&& player.GetPlayerPositionY() + 131 >= border.GetBorderPosY() + 1 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 1) {
		player.SetPlayerCanWalk(-1);
		return true;
	}
	if (player.GetPlayerPositionX() + 21 <= border.GetBorderPosX() + border.GetBorderWidth() && player.GetPlayerPositionX() + 21 >= border.GetBorderPosX() + border.GetBorderWidth() - 10
		&& player.GetPlayerPositionY() + 131 >= border.GetBorderPosY() + 1 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 1) {
		player.SetPlayerCanWalk(1);
		return true;
	}
	if (player.GetPlayerPositionX() + 120 >= border.GetBorderPosX() + 20 && player.GetPlayerPositionX() + 64 <= border.GetBorderPosX() + border.GetBorderWidth() / 2
		&& player.GetPlayerPositionY() + 128 >= border.GetBorderPosY() + 30 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 20) {
		player.SetPlayerPositionX(static_cast<float>(border.GetBorderPosX() - 130));
		return true;
	}
	if (player.GetPlayerPositionX() + 11 <= border.GetBorderPosX() + border.GetBorderWidth() - 20 && player.GetPlayerPositionX()  + 64 >= border.GetBorderPosX() + border.GetBorderWidth() / 2
		&& player.GetPlayerPositionY() + 128 >= border.GetBorderPosY() + 30 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 20) {
		player.SetPlayerPositionX((static_cast<float>(border.GetBorderPosX() + border.GetBorderWidth() + 5)));
		return true;
	}
	player.SetPlayerCanWalk(0);
	return false;
}

bool PlayerWasAtAltar(Player& player, Altar& altar) {
	if (player.GetPlayerPositionX() + 128 >= altar.GetAltarPosX() - 40 && player.GetPlayerPositionX() <= altar.GetAltarPosX() + 168
		&& player.GetPlayerPositionY() + 20 >= altar.GetAltarPosY() - 20 && player.GetPlayerPositionY() + 108 <= altar.GetAltarPosY() + 148) {
		DrawTextEx(font, "PRESS E TO HEAL\n\n    AT  ALTAR", {altar.GetAltarPosX() - 50, altar.GetAltarPosY() - 60}, 30, 2, RAYWHITE);
		if (IsKeyDown(KEY_E)) {
			altar.RegeneratePlayerHealth(player);
			altar.SetPlayerWasAtAltar(true);
			_lastAltarPosition.x = altar.GetAltarPosX();
			_lastAltarPosition.y = altar.GetAltarPosY();
			DrawTextEx(font, "Your soul is so rotten...", { player.GetPlayerPositionX() - 50, player.GetPlayerPositionY() + 180 }, 24, 2, WHITE);
			return true;
		}
	}
	return false;
}


void ResurrectionPlayer(Player& player, Altar* altar) {
	unsigned short int i = 0;

	while(i < 5) {
		if (altar[i].GetPlayerWasAtAltar()) {
			player.SetPlayerHealth(player.GetMaxPlayerHealth() / 2);
			player.SetPlayerPositionV(_lastAltarPosition);
			SetCurrentScreen(lastScreen);
			return;
		}
		if (altar[i].GetPlayerWasAtAltar() && _lastAltarPosition.x != altar[i].GetAltarPosX() && _lastAltarPosition.y != altar[i].GetAltarPosY()) {
			altar[i].SetPlayerWasAtAltar(false);
		}
		++i;
	}

	SetCurrentScreen(mainMenu);
	player.Nullification();

	return;
}

template<typename T>
bool PlayerCanTalkWithNpc(Player& player, T& other) {
	return (player.GetPlayerPositionX() + 128 >= other.GetNpcPosX() - 40 && player.GetPlayerPositionX() <= other.GetNpcPosX() + 168
		&& player.GetPlayerPositionY() + 20 >= other.GetNpcPosY() - 20 && player.GetPlayerPositionY() + 108 <= other.GetNpcPosY() + 148);
}

bool UpgradePlayerLevel(Player& player, Priest& priest) {
	if (IsKeyPressed(KEY_E) && PlayerCanTalkWithNpc(player, priest) && !priest.NpcDeath() && !player.PlayerDeath()) {
		SetLastPlayerPosition(player.GetPlayerPositionV());
		_currentScreen = UpgradeLevels;
		return true;
	}
	return false;
}

bool PlayerEnabledButton(Player& player, Button& button) {
	if (player.GetPlayerPositionX() + 128 >= button.GetButtonPosX() && player.GetPlayerPositionX() <= button.GetButtonPosX() + button.GetButtonWidth()
		&& player.GetPlayerPositionY() + 120 >= button.GetButtonPosY() && player.GetPlayerPositionY() + 128 <= button.GetButtonPosY() + button.GetButtonHeight() + 20) {
		button.EnableButton(true);
		return true;
	}
	if (button.IsButtonEnabled()) {
		return true;
	}
	return false;
}

void DropBoulder(Boulder& boulder, Button button, Ground ground) {
	if (button.curAction == Button::_buttonAction::DROP && button.IsButtonEnabled()) {
		if (boulder.BoulderPosY() + boulder.GetBoulderRadius() - 3 <= ground.GetGroundPositionY()) {
			boulder.MoveVerticallyDown();
		}
		else {
			boulder.BoulderSpeedNull();
		}
	}
}

void MoveBoulder(Boulder& boulder, Button button, Ground ground, int key, float distance) {
	if (button.curAction == Button::_buttonAction::MOVE && button.IsButtonEnabled()) {
		if (boulder.BoulderPosY() + boulder.GetBoulderRadius() - 2 <= ground.GetGroundPositionY()) {
			boulder.MoveVerticallyDown();
		}
		else {
			boulder.MoveHorizontally(key, distance);
		}
	}
}

void DropThorn(Thorn& thorn, Button button, Ground ground) {
	if (button.curAction == Button::_buttonAction::DROP && button.IsButtonEnabled() && thorn.GetThornDirection() == Thorn::DOWN) {
		if (thorn.GetThornPosY() + thorn.GetThornHeight() - 3 <= ground.GetGroundPositionY()) {
			thorn.MoveVerticallyDown();
		}
		else {
			thorn.ThornSpeedNull();
		}
	}
}

void BoulderKillPlayer(Player& player, Boulder& boulder) {
	if (boulder.GetBoulderRadius() + boulder.BoulderPosY() + 3 >= player.GetPlayerPositionY() && player.GetPlayerPositionY() + 128 >= boulder.BoulderPosY() - 3 && player.GetPlayerPositionX() + 80 >= boulder.BoulderPosX() + 3
		&& player.GetPlayerPositionX() + 48 <= boulder.BoulderPosX() + boulder.GetBoulderRadius() - 3 && boulder.GetBoulderSpeedH() >= 0.1f && boulder.GetBoulderSpeed() >= 0.1f) {
		player.PlayerTakesDamage(player.GetMaxPlayerHealth() + 10);
	}
}
void ThornKillPlayer(Player& player, Thorn thorn) {
	if (thorn.GetThornPosY() + thorn.GetThornHeight() + 3 >= player.GetPlayerPositionY() && player.GetPlayerPositionY() + 128 >= thorn.GetThornPosY() - 3 && player.GetPlayerPositionX() + 80 >= thorn.GetThornPosX() + 3
		&& player.GetPlayerPositionX() + 48 <= thorn.GetThornPosX() + thorn.GetThornWidth() - 3 && thorn.GetThornSpeed() >= 0.1f && thorn.GetThornDirection() == Thorn::DOWN) {
		player.PlayerTakesDamage(player.GetMaxPlayerHealth() + 10);
		return;
	}
	if (thorn.GetThornPosY() + thorn.GetThornHeight() + 3 >= player.GetPlayerPositionY() && player.GetPlayerPositionY() + 128 >= thorn.GetThornPosY() - 3 && player.GetPlayerPositionX() + 80 >= thorn.GetThornPosX() + 3
		&& player.GetPlayerPositionX() + 48 <= thorn.GetThornPosX() + thorn.GetThornWidth() - 3 && thorn.GetThornSpeed() < 0.1f && thorn.GetThornDirection() == Thorn::UP && TakeDamageTime(1.0f)) {
		player.PlayerTakesDamage(10);
		return;
	}
}

Camera2D _playerCamera;

Ground mainGroundFloor = Ground({ { -1000.0f , 1000.0f } , 14400, 1500, DARKGRAY });

//Border  = Border({ 500, 800 }, RAYWHITE, 40, 1000);
Ground _firstG = Ground({ 500.0f, 875.0f }, 150, 30, RAYWHITE);
Ground _secondG = Ground({850.0f, 750.0f }, 150, 30, RAYWHITE);

Border _border = Border({ 1200.0f, 650.0f }, 1000, 150,  DARKGRAY);
Ground _borderG = Ground({ 1200.0f, 650.0f }, 150, 20, DARKGRAY);

Border _groundBorder = Border({ 1349.0f, 650.0f }, 50, 450, DARKBROWN);
Border _border2 = Border({ 1798.0f, -600.0f }, 1300, 810, DARKGRAY);

Border _borderAlt = Border({ 2600.0f, -300.0f }, 3000, 40, DARKGRAY);

Button buttonTest = Button({ 2640.0f, 990.0f }, Button::_buttonAction::MOVE);

void LEVEL_T_LOGIC(Player& player, PlayerWeapon& pw) {
	if (!UpgradePlayerLevel(player, priest)) {
		player.PlayerController();
	}
	if (player.IsPlayerJump() && !player.PlayerMaxJump() && player.GetPlayerCanJump()) {
		player.MoveVertically();
	}
	else if (PlayerOnGround(player, mainGroundFloor) || PlayerOnGround(player, _firstG) || PlayerOnGround(player, _secondG) 
		|| PlayerOnGround(player, _borderG)) {
		player.SetPlayerCanJump(true);
		PlaySound(player._jump);
	}
	else if (player.PlayerMaxJump() || !player.IsPlayerJump()) {
		player.SetPlayerCanJump(false);
		player.MoveVerticallyDown();
	}

	if (PlayerCantWalk(player, _border)) {
		PlayerCantWalk(player, _border);
	}
	else if (PlayerCantWalk(player, _border2)) {
		PlayerCantWalk(player, _border2);
	}
	else if (PlayerCantWalk(player, _borderAlt)) {
		PlayerCantWalk(player, _borderAlt);
	}
	if (PlayerEnabledButton(player, buttonTest)) {
		MoveBoulder(boulderTest, buttonTest, mainGroundFloor, 1, 500);
	}
	BoulderKillPlayer(player, boulderTest);

	unsigned short int i = 0;
	while(i < 5) {
		PlayerWasAtAltar(player, _altars[i]);
		++i;
	}

	unsigned short int k = 0;
	while (k < 4) {
		PlayerAttacksEnemy(_vampire[k], player, pw);
		EnemyGoesToThePlayer(_vampire[k], player);
		EnemyAttacksThePlayer(_vampire[k], player);
		++k;
	}

	if (player.PlayerDeath()) {
		EndMode2D();
		SetCurrentScreen(DEATH_SCREEN);
		PlaySound(_deathScreenS);
	}
}
	
void LEVEL_T_DRAW(Player& player) {
	BeginMode2D(_playerCamera);
	
	DrawTexture(_backgrounds[0], -500, -300, WHITE);
	DrawTexture(_grounds[0], -500, 700, WHITE);
	DrawTexture(_backgrounds[1], 2610, -150, WHITE);
	DrawTexture(_grounds[1], 2610, 630, WHITE);

	_playerCamera.target = { player.GetPlayerPositionX(), player.GetPlayerPositionY() - 200 };
	_playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
	_playerCamera.zoom = 1.0f;
	_playerCamera.rotation = 0.0f;

	DrawTextEx(font, "PRESS WASD TO MOVE", {-200.0f, 700.0f }, 30, 3, RAYWHITE);
	DrawTextEx(font, "PRESS SHIFT TO MOVE FASTER", { -270.0f, 730.0f }, 30, 3, RAYWHITE);

	DrawTextEx(font, "PRESS SPACE TO JUMP", {400.0f, 700.0f }, 30, 3, RAYWHITE);

	DrawTextEx(font, "JUMP DOWN", { 1485.0f, 500.0f }, 30, 3, RAYWHITE);

	DrawTextEx(font, "PUSH ALT TO DASH", { 2250.0f, 800.0f }, 30, 3, RAYWHITE);
	DrawTextEx(font, "(come close)", { 2300.0f, 830.0f }, 30, 3, RAYWHITE);

	_firstG.GroundDraw();
	_secondG.GroundDraw();
	_groundBorder.Draw();
	_border.Draw();
	_border2.Draw();
	_borderAlt.Draw();

	buttonTest.Draw();

	//mainGroundFloor.GroundDraw();

	boulderTest.Draw();

	player.Draw();

	priest.Draw();

	_altars[1].Draw();
	_vampire[0].Draw();

	if (PlayerCanTalkWithNpc(player, priest)) {
		DrawTextEx(font, "PRESS E TO TALK", { priest.GetNpcPosX() - 70.0f, priest.GetNpcPosY() - 100.0f }, 30, 2, RAYWHITE);
	}
}

void DEATH_SCREEN_DRAW(Player& player)
{
	DrawTextEx(font, "YOU ARE DEAD", { 690.0f, 100.0f }, 84, 4, WHITE);
	DrawTextEx(font, "PRESS SPACE TO REVIVE", { 820.0f, 1000.0f }, 24, 2, RAYWHITE);

	DrawTexture(_deathScreen, 720, 300, WHITE);

	if (player.PlayerDeath() && (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_ESCAPE))) {
		ResurrectionPlayer(player, _altars);
	}
}


bool WhereWasPlayer(Player& player) {
	unsigned short int i = 0;
	while(i < 5) {
		if (_altars[i].GetPlayerWasAtAltar() && player.PlayerDeath()) {
			player.SetPlayerPositionV(_lastAltarPosition);
			SetCurrentScreen(lastScreen);
			return true;
		}
		++i;
	}
	return false;
}

void Restart(){
	boulderTest = Boulder({ 2640.0f, 100.0f }, 50.0f, WHITE);
	boulderTest.Init();

	_vampire[0] = Vampire({ 3600.0f, 900.0f });
	_vampire[0].Init();

	_altars[0] = Altar();
	_altars[1] = Altar({ 3200.0f, 900.0f });
	_altars[1].Init();

	buttonTest = Button({ 2640.0f, 990.0f }, Button::_buttonAction::MOVE);
	buttonTest.EnableButton(false);
}
