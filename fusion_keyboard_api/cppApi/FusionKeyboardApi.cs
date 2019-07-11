using System;
using System.Collections.ObjectModel;
using System.Linq;
using fusion_keyboard_api.models;
using LibUsbDotNet.Info;
using LibUsbDotNet.Main;

namespace fusion_keyboard_api
{
    public class FusionKeyboardApi: IFusionKeyboardApi
    {
        private INativeApi _nativeApi;

        public FusionKeyboardApi()
        {
            _nativeApi = new NativeApi();
        }

        public int Init()
        {
            return _nativeApi.InitApi();
        }

        public int Uninit()
        {
            return _nativeApi.UninitApi();
        }

        public Mode GetCurrentMode()
        {
            var tstatus = new TMode();
            var r = _nativeApi.GetCurrentMode(ref tstatus);
            if (r != 0)
                return null;
            var status = new Mode
            {
                brightness = tstatus.brightness,
                mode = (ModeType) tstatus.mode,
                color = (ModeColor) tstatus.color,
                speed = tstatus.speed
            };
            return status;
        }
    }
}
