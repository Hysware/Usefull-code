#!/bin/bash

## used to test cpu usage rate
while true; do
    # 获取所有逻辑核的数量
    TOTAL_CORES=$(nproc)
    # 使用 mpstat 检测每个核的 idle 时间（1秒间隔，1次采样）
    # 统计 idle > 50% 的核数（即利用率 <50%）
    LOW_LOAD_CORES=$(mpstat -P ALL 6 2 | awk '/Average:/ && $2 ~ /[0-9]/ {if ($12 > 50) print $2}' | wc -l)

    # 计算利用率低于50%的核占比
    if [ "$LOW_LOAD_CORES" -ge "100" ]; then
        echo "[$(date)] Low CPU usage detected ($LOW_LOAD_CORES cores idle >50%). Launching 'run'..."
        ./run  # 替换为你的程序路径
        break  # 启动后退出循环（若需持续监控，移除此行）
    else
        echo "[$(date)] CPU usage high. Waiting..."
    fi

    sleep 60  # 每60秒检测一次（避免频繁检查）
done                                  
