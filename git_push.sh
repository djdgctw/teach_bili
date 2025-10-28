#!/usr/bin/env bash

set -euo pipefail

repo_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$repo_dir"

# 确保在 Git 仓库中运行
if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    echo "错误：当前目录不在 Git 仓库中。" >&2
    exit 1
fi

if ! git remote get-url origin >/dev/null 2>&1; then
    echo "错误：未配置名为 origin 的远程仓库。" >&2
    exit 1
fi

if [[ -z "$(git status --porcelain)" ]]; then
    echo "没有需要提交的更改。"
    exit 0
fi

commit_msg="${1:-Auto commit $(date '+%Y-%m-%d %H:%M:%S')}"

echo ">>> Stage 所有改动..."
git add -A

echo ">>> 提交：$commit_msg"
git commit -m "$commit_msg"

current_branch="$(git rev-parse --abbrev-ref HEAD)"
echo ">>> 推送到远程 origin/$current_branch"
git push origin "$current_branch"

echo ">>> 已完成推送。"

# ./git_push.sh "你的提交信息"
