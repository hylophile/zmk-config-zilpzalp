export PATH := "../.venv/bin:" + env('PATH')

board := "zilpzalp"

parsed := board + ".yaml"
config := "config.yaml"
drawn := board + ".svg"
keymap := "config" / board + ".keymap"
svg := board + ".svg"

wdraw:
    watchexec \
        --ignore {{svg}} \
        --ignore {{parsed}} \
        'just draw'

draw: parse
    keymap --config {{config}} \
        draw \
        {{parsed}} \
        > {{svg}}

parse:
    keymap --config {{config}} \
        parse \
        --base-keymap {{parsed}} \
        --zmk-keymap {{keymap}} \
        > {{parsed}}.new
    mv {{parsed}}.new {{parsed}}
