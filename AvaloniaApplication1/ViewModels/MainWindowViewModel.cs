using System;
using System.Collections.Generic;
using System.Reactive;
using System.Text;
using ReactiveUI;
using fusion_keyboard_api;
using fusion_keyboard_api.models;

namespace AvaloniaApplication1.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        IFusionKeyboardApi _fusionKeyboardApi = new HidSharpFusionKeyboardApiContext();
        public string Greeting => "Welcome to Avalonia!";
        public ReactiveCommand<Unit, Unit> RedHandler { get; }
        public ReactiveCommand<Unit, Unit> GreenHandler { get; }

        public MainWindowViewModel()
        {
            _fusionKeyboardApi.Init();
            RedHandler = ReactiveCommand.Create(RedHandlerFunc);
            GreenHandler = ReactiveCommand.Create(GreenHandlerFunc);
        }

        ~MainWindowViewModel()
        {
            _fusionKeyboardApi.Uninit();
        }
        void RedHandlerFunc()
        {
            Console.WriteLine("red");
            _fusionKeyboardApi.SetMode(new Mode(){brightness = 50, color = ModeColor.Red, mode = ModeType.Static, speed = 1});
        }

        void GreenHandlerFunc()
        {
            Console.WriteLine("green");
            _fusionKeyboardApi.SetMode(new Mode() { brightness = 50, color = ModeColor.Green, mode = ModeType.Static, speed = 1 });
        }
    }
}
