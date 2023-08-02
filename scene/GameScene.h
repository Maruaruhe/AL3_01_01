#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include"DebugCamera.h"
#include "RailCamera.h"
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

/// <summary>
/// 衝突判定と応答
/// </summary>
	void CheckAllCollision();

/// <summary>
/// 敵弾を追加する
/// </summary>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	const std::list<EnemyBullet*>& GetBullets() const { return enemyBullets_; }

	void Fire();
	void ResetTime();

	void LoadEnemyPopDate();
	void UpdateEnemyPopCommands();

	void spawnEnemy(Vector3 pos);


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	//Sprite* sprite_ = nullptr;
	Model* model_ = nullptr;
	Model* reticle_ = nullptr;

	Player* player_ = nullptr;
	//Enemy* enemy_ = nullptr;

	std::list<Enemy*> enemies_;

	Model* modelSkydome_ = nullptr;
	Skydome* skydome_ = nullptr;

	RailCamera* railCamera_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t character = 0;

	bool isDebugCameraActive = false;
	DebugCamera* debugCamera_ = nullptr;


	std::list<EnemyBullet*> enemyBullets_;
	std::list<TimedCall*> timedCalls_;

	std::stringstream enemyPopCommands;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
