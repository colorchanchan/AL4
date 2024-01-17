#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>


GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	worldTransform_.Initialize();
	viewProjection_.translation_ = {0.0f, 0.0f, 0.0f};
	viewProjection_.rotation_ = {0.0f, 0.0f, 0.0f};

	viewProjection_.Initialize();

	Ground_ = std::make_unique<Ground>();
	GroundModel_.reset(Model::CreateFromOBJ("ground", true));
	Ground_->Initialize(GroundModel_.get());

	Skydome_ = std::make_unique<Skydome>();
	SkydomeModel_.reset(Model::CreateFromOBJ("skydome", true));
	Skydome_->Initialize(SkydomeModel_.get());

	Player_ = std::make_unique<Player>();
	PlayerModel_.reset(Model::CreateFromOBJ("float", true));
	Player_->Initialize(PlayerModel_.get());
}

void GameScene::Update() {
	Ground_->Update();
	Skydome_->Update();
	Player_->Update();
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
	Skydome_->Draw(viewProjection_);
	Ground_->Draw(viewProjection_);
	Player_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
