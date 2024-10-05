SRCS = main.c
OBJS = $(SRCS:.c=.o)
ASMS = $(SRCS:.c=.s)

CC = gcc
CFLAGS = -Wall -g
O3FLAGS = -O3

# 暗黙ルールを使って、.cから.oの生成を自動で処理
# `gcc -c $(CFLAGS)` が自動的に呼び出される

# バイナリ生成
bin: $(OBJS)
	$(CC) -o $@ $(OBJS)

# アセンブリ生成
asm: $(SRCS)
	$(CC) -o $@.s -S $(SRCS)

# プリプロセス生成物出力
pps: $(SRCS)
	$(CC) -o $@.e -E $(SRCS)

# O3最適化付きバイナリ生成
binO3: $(OBJS)
	$(CC) -o $@ $(O3FLAGS) $(OBJS)

# O3最適化付きアセンブリ生成
asmO3: $(SRCS)
	$(CC) -o $@.s -S $(O3FLAGS) $(SRCS)

# クリーンアップ: すべての生成物を削除
.PHONY: clean
clean:
	rm -f $(OBJS) $(ASMS) bin binO3 *.s *.e
