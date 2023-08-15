#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {
}

GameScene::~GameScene() { 
	delete sprite_;
	delete model_;
	delete player_;
	delete enemy_;
	delete debugCamera_;
}

void GameScene::Initialize() {
	character = TextureManager::Load("NineFox.png");

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	sprite_ = Sprite::Create(character, {100, 50});
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	model_ = Model::Create();
	player_ = new Player();
	enemy_ = new Enemy();
	player_->Initialize(model_,character);
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, {0,3,50}, {0.0f, 0.0f, -0.05f});
	debugCamera_ = new DebugCamera(100, 50);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() { 
	player_->Update();
	enemy_->Update();
	CheckAllCollision();
	debugCamera_->Update();
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_R)) {
		if (isDebugCameraActive == false) {
			isDebugCameraActive = true;
		} else {
			isDebugCameraActive = false;
		}
	}
	#endif
	if (isDebugCameraActive) {
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

	    viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//model_->Draw(worldTransform_, viewProjection_, character);
	enemy_->Draw(viewProjection_);
	player_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	/*sprite_->Draw();*/
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollision() { 
	const std::list<Bullet*>& playerBullets_ = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets_ = enemy_->GetBullets();

	std::list<Collider*> colliders_;
	colliders_.push_back(player_);
	colliders_.push_back(enemy_);

	for (Bullet* playerBullet : playerBullets_) {
		colliders_.push_back(playerBullet);
	}
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		colliders_.push_back(enemyBullet);
	}

	// リストのペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;

		// イテレーターBはイテレーターAの次の要素から回す
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;

			// ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}

	/*#pragma region 自キャラと敵弾の当たり判定
	for (EnemyBullet* bullet : enemyBullets_) {
		CheckCollisionPair(player_, bullet);
	}
	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定

	for (Bullet* bullet : playerBullets_) {
		CheckCollisionPair(bullet, enemy_);
	}
	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定
	for (Bullet* playerBullet : playerBullets_) {
		for (EnemyBullet* enemyBullet : enemyBullets_) {
			CheckCollisionPair(playerBullet, enemyBullet);
		}
	}
	#pragma endregion*/
}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	Vector3 posA = colliderA->GetWorldPosition();
	Vector3 posB = colliderB->GetWorldPosition();
	float length = Length(Subtract(posA, posB));
	// 交差判定
	if (length <= colliderA->GetRadius() + colliderB->GetRadius()) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}