FROM docker.io/zmkfirmware/zmk-build-arm:stable AS build

WORKDIR /app
RUN git clone https://github.com/zmkfirmware/zmk.git

WORKDIR /app/zmk
RUN west init --local app
RUN west update

WORKDIR /app/zmk/app
COPY ./config /app/config

ARG zmk_board
ARG zmk_shield
RUN west build \
  --board ${zmk_board} \
  -- \
  -DSHIELD=${zmk_shield} \
  -DZMK_CONFIG=/app/config \
  -DZMK_EXTRA_MODULES=/app/config/zmk-helpers-repo

RUN cp /app/zmk/app/build/zephyr/zmk.uf2 /app/zmk.uf2

ENTRYPOINT ["bash"]
