#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>
#include <zmk-helpers/helper.h>

#define APT 0
#define NUM 1
#define NAV 2
#define SYM 3
#define FUN 4

// &lt {
//     quick_tap_ms = <170>;
// };

&caps_word {
    continue-list = <UNDERSCORE MINUS BSPC LSHFT RSHFT>;
};

ZMK_BEHAVIOR(sch, macro,
            bindings = <
        		    &macro_tap &kp S
        		    &macro_release &kp RSHIFT
        		    &macro_tap &kp C &kp H
	          >;
)

ZMK_BEHAVIOR(qu, macro, 
            bindings = <
        		    &macro_tap &kp Q
        		    &macro_release &kp RSHIFT
        		    &macro_tap &kp U
	          >;
)

ZMK_BEHAVIOR(sklsft, macro, 
            bindings = <
        		    &macro_tap &sk LSHIFT
	          >;
)

#define CMP RGUI

ZMK_BEHAVIOR(ae, macro,
    bindings = <&kp CMP &kp DQT &kp A>;
)

ZMK_BEHAVIOR(oe, macro,
    bindings = <&kp CMP &kp DQT &kp O>;
)

ZMK_BEHAVIOR(ue, macro,
    bindings = <&kp CMP &kp DQT &kp U>;
)

ZMK_BEHAVIOR(sz, macro,
    bindings = <&kp CMP &kp S &kp S>;
)



// tap: qmark | shift + tap: excl
ZMK_BEHAVIOR(qexcl, mod_morph,
    bindings = <&kp QMARK>, <&kp EXCL>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)



#define COMBO(NAME, BINDINGS, KEYPOS) \
combo_##NAME { \
    timeout-ms = <20>; \
    bindings = <BINDINGS>; \
    key-positions = <KEYPOS>; \
};

/ {
    combos {
        compatible = "zmk,combos";
/* usually on base layer */
         COMBO(q, &kp Q, 1 2)
        COMBO(z, &kp Z, 18 19)
        COMBO(v, &kp V, 0 1)
        COMBO(ae, &ae, 15 26)
        COMBO(oe, &oe, 17 26)
        COMBO(ue, &ue, 6 26)
        COMBO(sz, &sz, 9 25)
        COMBO(sch, &sch, 9 18)
        COMBO(qexcl, &qexcl, 15 22)
        COMBO(slash, &kp SLASH, 22 23)
        COMBO(dash, &kp MINUS, 21 22)
//        COMBO(enter, &kp ENTER, 21 22 23)
        COMBO(enter, &kp ENTER, 11 20)
        COMBO(sqt, &kp SQT, 16 23)
        COMBO(esc, &kp ESC, 14 21)
/* parentheticals */
        COMBO(lbrc, &kp LBRC, 0 9)
        COMBO(lbkt, &kp LBKT, 1 10)
        COMBO(lpar, &kp LPAR, 2 11)
        COMBO(lt, &kp LT, 3 12)
        COMBO(gt, &kp GT, 4 13)
        COMBO(rpar, &kp RPAR, 5 14)
        COMBO(rbkt, &kp RBKT, 6 15)
        COMBO(rbrc, &kp RBRC, 7 16)
/* caps */
        COMBO(caps, &caps_word, 11 14)
        COMBO(capslock, &kp CAPSLOCK, 0 7)
/* deletion */
        COMBO(bspc, &kp BSPC, 10 19)
        // COMBO(del, &kp DEL, 6 7)
        // COMBO(delword, &kp LC(BSPC), 5 7)
/* alternative shifting */
    };
};

//     __________________________  __________________________
//    /     0  |  1  |  2  |  3  \/   4 |   5 |   6 |   7    \
// |  8  |  9  | 10  | 11  | 12  /\  13 |  14 |  15 |  16 | 17  |
//    \    18  | 19  | 20    /        \    21 |  22 |  23   /
//          \    24  | 25  /            \  26 |  27    /
//           --------------              --------------


/ {

    behaviors {
        hl: homerow_mods_left {
            compatible = "zmk,behavior-hold-tap";
            #binding-cells = <2>;
            // flavor = "tap-preferred";
            flavor = "balanced";
            tapping-term-ms = <150>;
            quick-tap-ms = <100>;
            // global-quick-tap;
            bindings = <&kp>, <&kp>;
            // opposite side hand keys
            hold-trigger-key-positions = <4 5 6 7 13 14 15 16 17 21 22 23 24 25 26 27>;
        };
        hr: homerow_mods_right {
            compatible = "zmk,behavior-hold-tap";
            #binding-cells = <2>;
            
            // flavor = "tap-preferred";
            flavor = "balanced";
            tapping-term-ms = <150>;
            quick-tap-ms = <100>;
            // global-quick-tap;
            bindings = <&kp>, <&kp>;
            // opposite side hand keys
            hold-trigger-key-positions = <0 1 2 3 8 9 10 11 12 18 19 20 24 25 26 27>;
        };

        // weird bugs?????????????
        my_lt: my_layer_taps {
            compatible = "zmk,behavior-hold-tap";
            #binding-cells = <2>;
            
            // flavor = "tap-preferred";
            flavor = "balanced";
            tapping-term-ms = <150>;
            quick-tap-ms = <100>;
            // global-quick-tap;
            bindings = <&mo &kp>;
            // non-thumb keys
            // hold-trigger-key-positions = <0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23>;
        };

        skq: sticky_key_quick_release {
            compatible = "zmk,behavior-sticky-key";
            #binding-cells = <1>;
            
            bindings = <&kp>;
            release-after-ms = <1000>;
            quick-release;
            ignore-modifiers;
        };

        mosk: layer_and_sticky {
            compatible = "zmk,behavior-hold-tap";
            #binding-cells = <2>;
            
            flavor = "tap-preferred";
            tapping-term-ms = <150>;
            // quick-tap-ms = <100>;
            bindings = <&mo>, <&skq>;
        };

        dotcol: dot_colon {
            compatible = "zmk,behavior-mod-morph";
            #binding-cells = <0>;
            
            bindings = <&kp DOT>, <&kp COLON>;
            mods = <(MOD_LSFT|MOD_RSFT)>;
        };
        comsem: comma_semicolon {
            compatible = "zmk,behavior-mod-morph";
            #binding-cells = <0>;
            
            bindings = <&kp COMMA>, <&kp SEMI>;
            mods = <(MOD_LSFT|MOD_RSFT)>;
        };
    };
};
