using System;
using System.Collections.Generic;
using System.Text;
using fusion_keyboard_api.models;

namespace fusion_keyboard_api
{
    public interface IFusionKeyboardApi
    {
        int Init();
        int Uninit();
        Mode GetCurrentMode();
        void SetMode(Mode mode);
        void SetColorMatrix();
    }
}
