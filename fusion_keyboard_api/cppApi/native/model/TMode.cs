using System.Runtime.InteropServices;

namespace fusion_keyboard_api
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct TMode
    {
        [MarshalAs(UnmanagedType.U4)]
        public byte mode;
        [MarshalAs(UnmanagedType.U4)]
        public byte speed;
        [MarshalAs(UnmanagedType.U4)]
        public byte brightness;
        [MarshalAs(UnmanagedType.U4)]
        public byte color;
    }
}