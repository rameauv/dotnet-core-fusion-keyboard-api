using System;
using System.Collections.Generic;
using System.Text;

namespace fusion_keyboard_api
{
    public interface INativeApi
    {
        int InitApi();
        int UninitApi();
        int GetCurrentMode(ref TMode status);
        int SetMode(ref TMode staMode);
    }
}
