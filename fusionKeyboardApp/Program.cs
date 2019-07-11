using System;
using System.Runtime.InteropServices;
using fusion_keyboard_api;

namespace fusionKeyboardApp
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var context = new HidSharpFusionKeyboardApiContext())
            {
                var r = context.GetCurrentMode();
                Console.WriteLine(".....................................................");
                Console.WriteLine("Mode:" + r.mode);
                Console.WriteLine("Brightness:" + r.brightness + "/50");
                Console.WriteLine("Color:" + r.color);
                Console.WriteLine("Direction:" + r.direction);
                Console.WriteLine("Speed:" + r.speed);
                Console.WriteLine(".....................................................");
            }
            return;
        }
    }
}
