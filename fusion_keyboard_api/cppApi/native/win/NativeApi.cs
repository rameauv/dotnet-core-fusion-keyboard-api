using System;
using System.Runtime.InteropServices;

namespace fusion_keyboard_api
{
    class NativeApi : INativeApi
    {
        [DllImport(@"fusionKeyboardCppApi.dll")]
        public static extern int dllexp_InitApi();
        public int InitApi() => dllexp_InitApi();

        [DllImport(@"fusionKeyboardCppApi.dll")]
        public static extern int dllexp_UninitApi();
        public int UninitApi() => dllexp_UninitApi();

        [DllImport(@"fusionKeyboardCppApi.dll")]
        public static extern int dllexp_GetCurrentMode(ref TMode status);
        public int GetCurrentMode(ref TMode status) => dllexp_GetCurrentMode(ref status);
    }
}
