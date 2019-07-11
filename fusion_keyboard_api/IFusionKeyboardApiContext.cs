using System;
using System.Collections.Generic;
using System.Text;
using fusion_keyboard_api.models;

namespace fusion_keyboard_api
{
    interface IFusionKeyboardApiContext: IDisposable, IFusionKeyboardApi
    {
        void Dispose();
    }
}