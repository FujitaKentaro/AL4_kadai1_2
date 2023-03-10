#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string.h>
#include "Model.h"


#include "Vector3.h"
#include "Matrix4.h"
#include "Affin.h"

//// 定数バッファ用データ構造体
//struct ViewState
//{
//	XMFLOAT3 eye;
//	XMFLOAT3 target;
//	XMFLOAT3 up;
//
//	XMMATRIX view;       // ワールド → ビュー変換行列
//	XMMATRIX projection; // ビュー → プロジェクション変換行列
//};

/// <summary>
/// 3Dオブジェクト
/// </summary>
class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	/*using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;*/



	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

	

private: // 定数
	static const int division = 50;					// 分割数
	static const float radius;				// 底面の半径
	static const float prizmHeight;			// 柱の高さ
	static const int planeCount = division * 2 + division * 2;		// 面の数
	static const int vertexCount = planeCount * 3;		// 頂点数

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

	/*/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const Vector3& GetEye() { return eye; }

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetEye(Vector3 eye);

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const Vector3& GetTarget() { return target; }

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetTarget(Vector3 target);*/

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	//static void CameraMoveVector(Vector3 move);

	
	/*static const XMFLOAT3& GetEye() { return eye; }

	static void SetEye(XMFLOAT3 eye);

	static const XMFLOAT3& GetTarget() { return target; }

	static void SetTarget(XMFLOAT3 target);*/

	static float FieldOfViewY(float focalLengs, float sensor);
	

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;


	//// ビュー行列
	//static Matrix4 matView;
	//// 射影行列
	//static Matrix4 matProjection;
	//// 視点座標
	//static Vector3 eye;
	//// 注視点座標
	//static Vector3 target;
	//// 上方向ベクトル
	//static Vector3 up;

	//static Matrix4 viewProjectionMatrix;
	//static Matrix4 viewMatrixInv;

	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;

private:// 静的メンバ関数

	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="window_width">画面横幅</param>
	/// <param name="window_height">画面縦幅</param>
	static void InitializeCamera(int window_width, int window_height);

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static void InitializeGraphicsPipeline();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

public: // メンバ関数
	
	bool Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const Vector3& GetPosition() const { return position; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const Vector3& position) { this->position = position; }

	const Vector3& GetScale() const { return scale; }

	void SetScale(const Vector3& scale) { this->scale = scale; }

	const Vector3& GetRotate() const { return rotation; }

	void SetRotate(const Vector3& rotation) { this->rotation = rotation; }

	Object3d* GetParent() const { return parent; }

	void SetParent(Object3d* parent) { this->parent = parent; }


	//setter
	void SetModel(Model* model) { this->model = model; }


	static void MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);

	static void MakeLookL(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& mat);

	static Matrix4 MakeInverse(const Matrix4* mat);

private: // メンバ変数
	public:
	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ

	// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	Vector3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation = { 0,0,0 };
	// ローカル座標
	Vector3 position = { 0,0,0 };
	// ローカルワールド変換行列
	Matrix4 matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
	//モデル
	Model* model = nullptr;

	static float win_wi, win_hi;
public:
	static float focalLengs;
	bool flag = 0;

};