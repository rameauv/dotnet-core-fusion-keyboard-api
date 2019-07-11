using System.Runtime.InteropServices;

namespace fusion_keyboard_api
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct TMode
    {
        [MarshalAs(UnmanagedType.U4)]
        public uint mode;
        [MarshalAs(UnmanagedType.U4)]
        public uint speed;
        [MarshalAs(UnmanagedType.U4)]
        public uint brightness;
        [MarshalAs(UnmanagedType.U4)]
        public uint color;
    }
}