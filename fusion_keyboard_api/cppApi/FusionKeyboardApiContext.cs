using System;
using System.Collections.Generic;
using System.Text;
using fusion_keyboard_api.models;

namespace fusion_keyboard_api
{
    public class FusionKeyboardApiContext : FusionKeyboardApi, IFusionKeyboardApiContext
    {
        public FusionKeyboardApiContext(): base()
        {
            base.Init();
        }

        ~FusionKeyboardApiContext()
        {
            Dispose();
        }

        public void Dispose()
        {
            base.Uninit();
        }
    }
}
