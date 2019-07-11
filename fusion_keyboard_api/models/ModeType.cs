using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace fusion_keyboard_api.models
{
    public enum ModeType
    {
        Static = 0x01,
        Breathing = 0x02,
        Wave = 0x03,
        FadeOnPress = 0x04,
        Marquee = 0x05,
        Ripple = 0x06,
        FlashOnPress = 0x07,
        Neon = 0x08,
        RainbowMarquee = 0x09,
        Raindrop = 0x0a,
        CircleMarquee = 0x0b,
        Hedge = 0x0c,
        Rotate = 0x0d
    }
}
