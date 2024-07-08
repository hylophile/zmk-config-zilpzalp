default: watch_draw

keyboard := "zilpzalp"
automounted_as := "XIAO-SENSE"
export zmk_board := "seeeduino_xiao_ble"
export zmk_shield := keyboard + "_ble"

flash_target_dir := "/run/media" / env('USER') / automounted_as
nametag := keyboard + "_firmware"

flash: build
    #!/usr/bin/env bash
    printf "Flashing: Looking for '{{flash_target_dir}}'."
    for i in {1..30}
    do
        if [ -d "{{flash_target_dir}}" ]; then
            printf "\nFound it! Flashing...\n"
            cp ./build/{{nametag}}.uf2 {{flash_target_dir}}
            echo ✅ Flash Success!
            exit 0
        else
            printf "."
        fi
        sleep 1
    done

    echo
    echo "Directory '{{flash_target_dir}}' did not appear within 30 seconds."
    exit 1

build:
    podman build . \
        --build-arg zmk_board \
        --build-arg zmk_shield \
        --tag {{nametag}}
    podman run --name {{nametag}} --replace --detach -t {{nametag}}
    podman cp {{nametag}}:/app/zmk.uf2 ./build/{{nametag}}.uf2
    podman stop {{nametag}}
    @echo ✅ Build Success!


export PATH := "../.venv/bin:" + env('PATH')
keymap := "config" / keyboard + ".keymap"
kmd := "./keymap_drawer"
kmd_parsed := kmd / keyboard + ".yaml"
kmd_config := kmd / "config.yaml"
kmd_svg := kmd / keyboard + ".svg"

watch_draw:
    watchexec \
        --ignore {{kmd_svg}} \
        --ignore {{kmd_parsed}} \
        'just draw'

draw: parse
    keymap --config {{kmd_config}} \
        draw \
        {{kmd_parsed}} \
        > {{kmd_svg}}

parse:
    keymap --config {{kmd_config}} \
        parse \
        --base-keymap {{kmd_parsed}} \
        --zmk-keymap {{keymap}} \
        > {{kmd_parsed}}.new
    mv {{kmd_parsed}}.new {{kmd_parsed}}

