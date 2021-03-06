#include "Game.hpp"

// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(HW16A179　牧　和輝)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(HW16A179　牧　和輝)
// TODO: 砲台を青い壁に沿って上下に動かす。(HW16A078　小林　大輪)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(HW16A078　小林　大輪)
// TODO: スコアのサイズを大きくする。(HW16A062　木下　誠也)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(HW16A062　木下　誠也)
// TODO: PlayBGM()関数を使って、BGMを再生する。(HW16A130　東出　和也)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(HW16A130　東出　和也)


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
int     cannon;         //!< 砲台の速度
bool    cannonCan;      //!< 砲台の判定


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-310, -150);
    targetRect = Rect(280, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
//<<<<<<< HEAD
    cannon = 100;
    cannonCan = true;
//=======
    PlayBGM("bgm_maoudamashii_8bit07.mp3");  // TODO: PlayBGM()関数を使って、BGMを再生する。(G)
//>>>>>>> shooting/HW16A130
}


// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
          PlaySound("se_maoudamashii_explosion06.mp3");  // TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)
        
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 200 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_system27.mp3");  // TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)
        }
        
        // ターゲットに当たらない場合
        if (bulletPos.x >= 335) {
            // 弾を発射可能な状態に戻す
            bulletPos.x = -999;
        }
    }
    
    // 雲の移動
    if (cloudPos.x > -999) {
        cloudPos.x += 100 * Time::deltaTime;
        // 雲の移動判定
        if (cloudPos.x >= 380) {
            //雲を初期位置に戻す
            cloudPos.x = -550;
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);


    
    // 砲台の移動
    if (cannonPos.y <= -60 && cannonCan) {
        cannonPos.y += cannon * Time::deltaTime;
    }
    if(cannonPos.y >= -60)
    {
        cannonCan = false;
    }
    if (cannonPos.y >= -160 && cannonCan == false) {
        cannonPos.y -= cannon * Time::deltaTime;
    }
    if(cannonPos.y <= -160)
    {
        cannonCan = true;
    }
    
    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
//<<<<<<< HEAD

//=======
    SetFont("nicoca_v1.ttf", 50.0f);
    DrawText(FormatString("%05d", score), Vector2(-319, 199), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-320, 200), Color::white);
}
//>>>>>>> shooting/HW16A062

