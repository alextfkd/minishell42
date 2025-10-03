# 1. バージョンを固定したベースイメージを使用
FROM ubuntu:22.04

# 環境変数でユーザー情報などを定義
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# 2. 必要なパッケージをすべて一度にインストールする
#    - DEBIAN_FRONTEND=noninteractive はインストール中の対話プロンプトを無効化します
#    - sudoとzshをここでインストールします
#    - 最後にキャッシュをクリアしてイメージサイズを削減します
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    sudo \
    zsh \
    build-essential \
    libbsd-dev \
    make \
    curl \
    git \
    valgrind \
    clang \
    clang-format \
    vim \
    ssh \
    lldb \
    python3-pip \
    man-db \
    locales \
    x11-apps \
    libx11-dev \
    libxext-dev \
    python3-venv \
    iputils-ping \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# 3. セキュリティ向上のため、一般ユーザーを作成
#    - sudoとzshをインストールした後でユーザーを作成します
#    - /etc/sudoers.d ディレクトリを先に作成しておく必要があります
RUN mkdir -p /etc/sudoers.d && \
    groupadd --gid $USER_GID $USERNAME && \
    useradd --uid $USER_UID --gid $USER_GID -m $USERNAME --shell /bin/zsh && \
    echo "$USERNAME ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/$USERNAME && \
    chmod 0440 /etc/sudoers.d/$USERNAME

# --- ここからユーザーを切り替えて作業 ---
USER $USERNAME
WORKDIR /home/$USERNAME

# zshrcをコピー（ローカルの.zshrcファイルが必要です）
COPY --chown=$USERNAME:$USERNAME .zshrc /home/$USERNAME/.zshrc

# uvのインストール
RUN curl -LsSf https://astral.sh/uv/install.sh | sh
ENV PATH="/home/$USERNAME/.local/bin:$PATH"

# ツールのインストール
RUN uv tool install norminette && \
    uv tool install c-formatter-42

# シンボリックリンクの作成
RUN rm /home/$USERNAME/.local/share/uv/tools/c-formatter-42/lib/python3.10/site-packages/c_formatter_42/data/clang-format-linux && \
    ln -s /usr/bin/clang-format \
    /home/$USERNAME/.local/share/uv/tools/c-formatter-42/lib/python3.10/site-packages/c_formatter_42/data/clang-format-linux

# francinetteのインストール
RUN bash -c "$(curl -fsSL https://raw.github.com/xicodomingues/francinette/master/bin/install.sh)" && \
    /home/$USERNAME/francinette/tester.sh -u

# vimプラグインのセットアップ
RUN mkdir -p /home/$USERNAME/.vim/plugin
COPY --chown=$USERNAME:$USERNAME 42header/plugin/stdheader.vim /home/$USERNAME/.vim/plugin/

# デフォルトのコマンド
CMD ["zsh"]