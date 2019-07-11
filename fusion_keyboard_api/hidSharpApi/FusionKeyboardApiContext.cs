using System;
using System.Collections.Generic;
using System.Text;
using fusion_keyboard_api.models;

namespace fusion_keyboard_api
{
    public class HidSharpFusionKeyboardApiContext : HidSharpFusionKeyboardApi, IFusionKeyboardApiContext
    {
        public HidSharpFusionKeyboardApiContext(): base()
        {
            base.Init();
        }

        ~HidSharpFusionKeyboardApiContext()
        {
            Dispose();
        }

        public void Dispose()
        {
            base.Uninit();
        }
    }
}
