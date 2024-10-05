#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define NUM (1024*1024*512)

int main() {
    // キャッシュサイズを大きく超える配列を作成
    uint32_t* bigTable = (uint32_t*)malloc(NUM * sizeof(uint32_t));
    for(int i = 0; i < NUM; i++) {
        bigTable[i] = i;    // 初期化として：配列内の全ての変数に、自分自身の配列添字を書き込む
    }

    // キャッシュの効果を確かめられるように、アクセス対象の変数を確認
    #if 1
    const uint64_t targetIndexes[16] = {
        (NUM/16)*1 ,
        (NUM/16)*2 ,
        (NUM/16)*3 ,
        (NUM/16)*4 ,
        (NUM/16)*5 ,
        (NUM/16)*6 ,
        (NUM/16)*7 ,
        (NUM/16)*8 ,
        (NUM/16)*9 ,
        (NUM/16)*10,
        (NUM/16)*11,
        (NUM/16)*12,
        (NUM/16)*13,
        (NUM/16)*14,
        (NUM/16)*15,
        NUM
    };   // 四分位位置へのアクセス
    #else
    const uint64_t targetIndexes[16] = {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16
    };                       // 配列頭位置へのアクセス
    #endif

    uint32_t sum = 0;        // アクセス対象の変数群の総和（この数値に意味はない）
    uint32_t karamawari = 0; // キャッシュを汚すためのアクセス対象の変数群の総和(この数値に意味はない)

    // キャッシュが効くようなアクセスパターンの時に処理時間が短くなっていることを確認するために処理時間を計測する
    clock_t startClock, endClock;  // 開始時刻と終了時刻を保存する変数
    double diff = 0;                 // 開始時刻と終了時刻の差（の合計）を保存する変数

    for(int testNum=0; testNum < 100; testNum++) { // 処理時間の変化がわかりやすいよう、100回繰り返す
        printf("%u...", testNum);
        {
            /* 処理開始前のクロックを取得 */
            startClock = clock();
            {
                // 本望の処理
                for (int i = 0; i < 16; i++) {
                    int targetIndex = targetIndexes[i] - 1; 
                    sum += bigTable[targetIndex];           // ★ここでキャッシュヒット率が大きく変わる
                }

            }
            /* 処理終了後のクロックを取得 */
            endClock = clock();

            diff += (double)(endClock - startClock);
        }

        // （キャッシュを汚すために再度配列要素へアクセス）
        for (int i = 0 / 2; i < 1024 * 1024; i++) {
            karamawari += bigTable[i + (NUM / 2)];   // オフセットとして NUM/2 をつけることで、配列中腹へアクセス
        }
    }

    /* 計測時間を表示 */
    puts("\n");
    printf("sum :%u\n", sum);
    printf("time:%f(sec) @100times\n", (double)(diff) / CLOCKS_PER_SEC);
    printf("karamawari:%d\n", karamawari);   // karamawariループの最適化抑制のためprintf

    return 0;
}