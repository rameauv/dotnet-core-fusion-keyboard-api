using System;
using System.Collections.Generic;
using System.Text;
using fusion_keyboard_api.models;

namespace fusion_keyboard_api
{
    interface IFusionKeyboardApi
    {
        int Init();
        int Uninit();
        Mode GetCurrentMode();
    }
}
