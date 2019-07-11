using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading;
using fusion_keyboard_api.models;
using HidSharp;

namespace fusion_keyboard_api
{
    public class HidSharpFusionKeyboardApi : IFusionKeyboardApi
    {
        private HidStream _stream;

        public HidSharpFusionKeyboardApi()
        {
        }

        static HidStream GetFusionKbdStream()
        {
            var loader = new HidDeviceLoader();
            var devices = loader.GetDevices(0x1044, 0x7a39);
            var filteredDeviceList = new FilteredDeviceList();

            foreach (var device in devices)
            {
                if (device.GetMaxFeatureReportLength() != 0x09)
                    continue;
                HidStream stream;
                device.TryOpen(out stream);
                if (stream != null && stream.CanWrite && stream.CanWrite)
                    return stream;
            }

            return null;
        }

        public int Init()
        {
            var stream = GetFusionKbdStream();
            if (stream == null)
                return -1;
            _stream = stream;
            return 0;
        }

        public int Uninit()
        {
            _stream.Close();
            return 0;
        }

        public Mode GetCurrentMode()
        {
            var buff = new byte[9];
            buff[0] = 0x00;
            buff[1] = 0x88; //Kind
            buff[2] = 0x00; //reserved
            buff[3] = 0x00; // Mode
            buff[4] = 0x00; //speed
            buff[5] = 0x00; // brightness
            buff[6] = 0x00; // color
            buff[7] = 0x00; // direction
            buff[8] = Checksum(buff); //checksum
            _stream.SetFeature(buff);
            _stream.GetFeature(buff);
            var mode = new Mode
            {
                brightness = buff[5],
                color = (ModeColor)buff[6],
                direction = buff[7],
                mode = (ModeType)buff[3],
                speed = buff[4]
            };
            return mode;
        }

        public void SetMode(Mode mode)
        {
            var buff = new byte[9];
            buff[0] = 0x00;
            buff[1] = 0x08; //Kind
            buff[2] = 0x00; //reserved
            buff[3] = (byte)mode.mode; // Mode
            buff[4] = 0x05; //speed
            buff[5] = mode.brightness; // brightness
            buff[6] = (byte)mode.color; // color
            buff[7] = mode.direction; // direction
            buff[8] = Checksum(buff); //checksum
            _stream.SetFeature(buff);
        }
        static byte Checksum(byte[] buff)
        {
            var checksum = new byte();
            checksum = 0;
            for (int k = 1; k <= 7; k++)
            {
                checksum = (byte)(checksum + buff[k]);
            }
            checksum = (byte)(255 - checksum);
            return checksum;
        }
    }
}
