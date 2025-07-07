#! /bin/bash
# 从输入的路径中提取文件名、去掉扩展名，生成一个 .root 文件名
input_name=$1
echo Input: $input_name
file_name="${input_name##*/}"
base_name="${file_name%.*}"
out_name=$base_name.root
echo Output: $out_name
