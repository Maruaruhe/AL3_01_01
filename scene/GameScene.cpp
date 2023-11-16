#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <fstream>
#include "AABB.h"

GameScene::GameScene() {
}

GameScene::~GameScene() { 
	//delete sprite_;
	delete model_;

	delete player_;
	delete debugCamera_;
	//delete enemy_;
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	for (Enemy* enemy : zWall) {
		delete enemy;
	}
	for (Enemy* enemy : xWall) {
		delete enemy;
	}
	for (Enemy* enemy : floorEnemies_) {
		delete enemy;
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}

	delete skydome_;
	delete modelSkydome_;
	delete railCamera_;
}

void GameScene::Initialize() {
	character = TextureManager::Load("player.png");
	//TextureManager::Load("reticle.png");

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//sprite_ = Sprite::Create(character, {100, 50});
	worldTransform_.Initialize();

	viewProjection_.farZ = 1000;
	viewProjection_.Initialize();

	model_ = Model::Create();
	reticle_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	player_ = new Player();
	//player_->Initialize(model_, reticle_, character,{0,0,30});
	player_->Initialize(model_, reticle_, character,{0,0,0});

	debugCamera_ = new DebugCamera(100, 50);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//LoadEnemyPopDate("./Resources/enemyPop.csv");
	UpdateEnemyPopCommands("./Resources/enemyPop/enemyPop.csv",&enemies_);
	UpdateEnemyPopCommands("./Resources/enemyPop/zWall.csv",&zWall);
	UpdateEnemyPopCommands("./Resources/enemyPop/xWall.csv",&xWall);
	UpdateEnemyPopCommands("./Resources/enemyPop/floor.csv",&floorEnemies_);
	ResetTime();

	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);

	railCamera_ = new RailCamera();
	railCamera_->Initialize({0, 0, 0}, {0, 0, 0});

	//player_->SetParent(&railCamera_->GetWorldTransform());
}

void GameScene::Update() { 
	railCamera_->Update();

	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();

	player_->Update(viewProjection_);
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
	});

	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}

	for (Enemy* enemy : zWall) {
		enemy->Update();
	}
	for (Enemy* enemy : xWall) {
		enemy->Update();
	}
	for (Enemy* enemy : floorEnemies_) {
		enemy->Update();
	}





	for (TimedCall* timedCall : timedCalls_) {
		timedCall->Update();
	}

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}
	CheckAllCollision();
	player_->GiveWorld().UpdateMatrix();
	skydome_->Update();

	railCamera_->SetPosition(player_->GivePreWorld().translation_);
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
	//skydome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	//enemy_->Draw(viewProjection_);
	for (Enemy* enemy : enemies_) {
		enemy->Draw(viewProjection_);
	}
	/*for (Enemy* enemy : zWall) {
		enemy->Draw(viewProjection_);
	}
	for (Enemy* enemy : xWall) {
		enemy->Draw(viewProjection_);
	}
	for (Enemy* enemy : floorEnemies_) {
		enemy->Draw(viewProjection_);
	}*/


	/*for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}*/

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	player_->DrawUI();
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
	const std::list<EnemyBullet*>& eBullets_ = GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();
	// posA = player_->GiveWorld().translation_;

	for (EnemyBullet* bullet : eBullets_) {
		posB = bullet->GetWorldPosition();

		Vector3 distance = Subtract(posA, posB);
		if (std::pow(distance.x, 2) + std::pow(distance.y, 2) + std::pow(distance.z, 2) <= 3 * 3) {
			// player_->OnCollision();
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	for (Enemy* enemy : zWall) {
		posA = enemy->GetWorldPosition();

		for (Bullet* bullet : playerBullets_) {
			posB = bullet->GetWorldPosition();

			Vector3 distance = Subtract(posA, posB);
			if (std::pow(distance.x, 2) + std::pow(distance.y, 2) + std::pow(distance.z, 2) <=
			    3 * 3) {
				enemy->OnCollision();
				bullet->OnCollision();
			}
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	for (Bullet* playerBullet : playerBullets_) {
		for (EnemyBullet* eBullet : enemyBullets_) {
			posA = playerBullet->GetWorldPosition();
			posB = eBullet->GetWorldPosition();

			Vector3 distance = Subtract(posA, posB);
			if (std::pow(distance.x, 2) + std::pow(distance.y, 2) + std::pow(distance.z, 2) <=
			    3 * 3) {
				playerBullet->OnCollision();
				eBullet->OnCollision();
			}
		}
	}
#pragma endregion

#pragma region 自と敵の当たり判定
	// PvsE(&floorEnemies_);
	// PvsE(&zWall);
	// PvsE(&xWall);
	Vector3 distance{};

	posA = player_->GetWorldPosition();
	for (Enemy* enemy : enemies_) {
		AABB a = CreateAABB(player_->GiveWorld());
		AABB b = CreateAABB(enemy->GiveWorld());

		if (IsCollision(a, b)) {
			player_->SetOnCollision(true);

			// x軸
			if (player_->GetMove().x < 0) {
				distance.x = a.min.x - b.max.x;
			} else if ((player_->GetMove().x > 0)) {
				distance.x = a.max.x - b.min.x;
			}

			if (player_->GetVelocity().x >= fabs(distance.x)) {
				player_->SetPositionX(posA.x - distance.x);
				player_->GiveWorld().UpdateMatrix();
			}

			// y軸
			if (player_->GetMove().y < 0) {
				distance.y = a.min.y - b.max.y;
			} else if (player_->GetMove().y > 0) {
				distance.y = a.max.y - b.min.y;
			}

				if (player_->GetVelocity().y >= fabs(distance.y)) {
				player_->SetPositionY(posA.y - distance.y);
				player_->GiveWorld().UpdateMatrix();
			}

			// z軸
			if (player_->GetMove().z < 0) {
				distance.z = a.min.z - b.max.z;
			} else if (player_->GetMove().z > 0) {
				distance.z = a.max.z - b.min.z;
			}
		} else {
			player_->SetOnCollision(false);
		}

		if (player_->GetVelocity().z >= fabs(distance.z)) {
			player_->SetPositionZ(posA.z - distance.z);
			player_->GiveWorld().UpdateMatrix();
		}
	}
}
	#pragma endregion

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { 
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::Fire() {
	assert(player_);
	for (Enemy* enemy : zWall) {
		Vector3 distance = Subtract(enemy->GetWorldPosition(), player_->GetWorldPosition());
		Vector3 normalize = Normalize(distance);
		Vector3 velocity = {};
		velocity.x = -normalize.x;
		velocity.y = -normalize.y;
		velocity.z = -normalize.z;

		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, enemy->GetWorldPosition(), velocity);

		enemyBullets_.push_back(newBullet);
	}
}

void GameScene::ResetTime() {

	Fire();

	std::function<void(void)> callback = std::bind(&GameScene::ResetTime, this);
	TimedCall* timedCall = new TimedCall(callback, 30);
	timedCalls_.push_back(timedCall);
}

std::stringstream GameScene::LoadEnemyPopDate(const std::string& directoryPath) { 

	std::ifstream file;
	file.open(directoryPath);
	assert(file.is_open());

	std::stringstream enemyPopCommands;
	enemyPopCommands << file.rdbuf();

	file.close();
	return enemyPopCommands;
}

void GameScene::UpdateEnemyPopCommands(const std::string& filename, std::list<Enemy*>* enemies) { 

	std::string line;
	std::stringstream enemyPopCommands = LoadEnemyPopDate(filename);
	while (getline(enemyPopCommands, line)) {
		std::istringstream line_stream(line);
		std::string word;
		getline(line_stream, word, ',');
		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float sx = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float sy = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float sz = (float)std::atof(word.c_str());

			spawnEnemy(Vector3(x, y, z), Vector3(sx, sy, sz), enemies);
			//break;
		}
	}
}

void GameScene::spawnEnemy(Vector3 pos, Vector3 scale, std::list<Enemy*>* enemies) {
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(model_, {pos.x, pos.y, pos.z}, scale);
	newEnemy->SetGameScene(this);
	enemies->push_back(newEnemy);
}

void GameScene::PvsE(std::list<Enemy*>* enemies) {
	Vector3 posA, posB;

	posA = player_->GetWorldPosition();
	for (Enemy* enemy : *enemies) {
		posB = enemy->GetWorldPosition();
		AABB a = CreateAABB(player_->GiveWorld());
		AABB b = CreateAABB(enemy->GiveWorld());
		/*Direction direction = CheckDirection(a, b);
		player_->SetDirection(direction);*/
		if (IsCollision(a, b)) {
			player_->SetOnCollision(true);
			// x軸
			if (input_->PushKey(DIK_A)) {
				float distance = a.min.x - b.max.x;
				if (player_->GetVelocity().x >= -distance) {
					player_->SetPosition({posA.x - distance, posA.y, posA.z});
				}
			}
			if (input_->PushKey(DIK_D)) {
				float distance = a.max.x - b.min.x;
				if (player_->GetVelocity().x >= distance) {
					player_->SetPosition({posA.x - distance, posA.y, posA.z});
				}
			}

			// z軸
			if (input_->PushKey(DIK_Q)) {
				float distance = a.min.z - b.max.z;
				if (player_->GetVelocity().z >= -distance) {
					player_->SetPosition({posA.x, posA.y, posA.z - distance});
				}
			}
			if (input_->PushKey(DIK_E)) {
				float distance = a.max.z - b.min.z;
				if (player_->GetVelocity().z >= distance) {
					player_->SetPosition({posA.x, posA.y, posA.z - distance});
				}
			}

			// y軸
			if (input_->PushKey(DIK_S)) {
				float distance = a.min.y - b.max.y;
				if (player_->GetVelocity().y >= -distance) {
					player_->SetPosition({posA.x, posA.y - distance, posA.z});
				}
			}
			if (input_->PushKey(DIK_W)) {
				float distance = a.max.y - b.min.y;
				if (player_->GetVelocity().y >= distance) {
					player_->SetPosition({posA.x, posA.y - distance, posA.z});
				}
			}
			break;
		} else {
			player_->SetOnCollision(false);
		}
	}
}