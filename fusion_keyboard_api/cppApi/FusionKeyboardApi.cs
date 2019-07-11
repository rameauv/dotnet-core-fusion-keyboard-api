using System;
using System.Collections.ObjectModel;
using System.Linq;
using fusion_keyboard_api.models;

namespace fusion_keyboard_api
{
    public class FusionKeyboardApi: IFusionKeyboardApi
    {
        private INativeApi _nativeApi;
        private bool _init;

        public FusionKeyboardApi()
        {
            _nativeApi = new NativeApi();
            _init = false;
        }

        public int Init()
        {
            if (_init)
                return 0;
            var r =_nativeApi.InitApi();
            if (r == 0)
                _init = true;
            return r;
        }

        public int Uninit()
        {
            if (!_init)
                return 0;
            var r = _nativeApi.UninitApi();
            if (r == 0)
            {
                _init = false;
            }
            return r;
        }

        public Mode GetCurrentMode()
        {
            var tMode = new TMode();
            var r = _nativeApi.GetCurrentMode(ref tMode);
            if (r != 0)
                return null;
            var mode = new Mode
            {
                brightness = tMode.brightness,
                mode = (ModeType) tMode.mode,
                color = (ModeColor) tMode.color,
                speed = tMode.speed
            };
            return mode;
        }

        public void SetMode(Mode mode)
        {
            var tMode = new TMode
            {
                brightness = mode.brightness,
                mode = (byte)mode.mode,
                color = (byte)mode.color,
                speed = 0x05
            };
            var r = _nativeApi.SetMode(ref tMode);
        }
    }
}
