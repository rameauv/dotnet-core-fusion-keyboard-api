using System;
using System.Runtime.InteropServices;
using fusion_keyboard_api;

namespace fusionKeyboardApp
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var context = new FusionKeyboardApiContext())
            {
                var r = context.GetCurrentMode();
                Console.WriteLine(".....................................................");
                Console.WriteLine("Mode:" + r.mode);
                Console.WriteLine("Brightness:" + r.brightness + "/50");
                Console.WriteLine("Speed:" + r.speed);
                Console.WriteLine("Color:" + r.color);
                Console.WriteLine(".....................................................");
            }
            return;
        }
    }
}
