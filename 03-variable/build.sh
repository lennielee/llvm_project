#!/usr/bin/env bash
set -e  # 任何一步失败就退出

BUILD_DIR=build

# 若目录已存在就删掉
if [ -d "$BUILD_DIR" ]; then
    echo "Found $BUILD_DIR — removing ..."
    rm -rf "$BUILD_DIR"
fi

# 重新创建并进入
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# 配置 & 编译
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
