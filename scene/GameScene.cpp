#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {
}

GameScene::~GameScene() { 
	//delete sprite_;
	delete model_;

	delete player_;
	delete debugCamera_;
	delete enemy_;

	delete skydome_;
	delete modelSkydome_;
}

void GameScene::Initialize() {
	character = TextureManager::Load("NineFox.png");

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//sprite_ = Sprite::Create(character, {100, 50});
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	player_ = new Player();
	player_->Initialize(model_, character);

	debugCamera_ = new DebugCamera(100, 50);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	enemy_ = new Enemy();
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, {0, 3, 50}, {0.0f, 0.0f, -0.05f});

	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
}

void GameScene::Update() { 
	player_->Update();
	enemy_->Update();
	CheckAllCollision();
	skydome_->Update();
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
	skydome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);

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
	Vector3 posA, posB;

	const std::list<Bullet*>& playerBullets_ = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets_ = enemy_->GetBullets();

	#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets_) {
		posB = bullet->GetWorldPosition();

		Vector3 distance = Subtract(posA, posB);
		if (std::pow(distance.x, 2) + std::pow(distance.y, 2) + std::pow(distance.z, 2) <=3 * 3) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定
	posA = enemy_->GetWorldPosition();

	for (Bullet* bullet : playerBullets_) {
		posB = bullet->GetWorldPosition();

		Vector3 distance = Subtract(posA, posB);
		if (std::pow(distance.x, 2) + std::pow(distance.y, 2) + std::pow(distance.z, 2) <= 3 * 3) {
			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定
	for (Bullet* playerBullet : playerBullets_) {
		for (EnemyBullet* enemyBullet : enemyBullets_) {
			posA = playerBullet->GetWorldPosition();
			posB = enemyBullet->GetWorldPosition();

			Vector3 distance = Subtract(posA, posB);
			if (std::pow(distance.x, 2) + std::pow(distance.y, 2) + std::pow(distance.z, 2) <=
			    3 * 3) {
				playerBullet->OnCollision();
				enemyBullet->OnCollision();
			}
		}
	}
	#pragma endregion
}