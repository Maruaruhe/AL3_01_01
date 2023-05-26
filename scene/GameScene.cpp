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
	enemy_->Initialize(model_, {0,3,50}, {0.0f, 0.0f, -0.5f});
	debugCamera_ = new DebugCamera(100, 50);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() { 
	player_->Update();
	enemy_->Update();
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
