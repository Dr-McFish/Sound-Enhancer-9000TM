# Sound-Enhanser-9000TM

VST3 plugin that make your sound better <br>

![Thumbnail](https://user-images.githubusercontent.com/61105022/153748899-77d65c75-5a56-4b79-ae04-336cab0063c4.PNG)

## `/!\` Disclaimer `/!\`

Just to make things clear, this is a joke plugin that realy doesnt do anything interesting

## Build instuctions

Method I am using. If you want to, you can use other stuff than Visual Studio, run `cmake.exe --help` to see other options, but you have to figure them out yourself.

### Prerequisites

 * [cmake](cmake.org)
 * [VST SDK](https://developer.steinberg.help/display/VST)
 * Visual Studio (aternatively you can use something else)
 
 ### Instructions
 
 1. modify `CMakeLists.txt` to indicate the location of the Stienberg SDK folder on your computer
 
 2. open command line and type this:
 
 ```cmd
 >mkdir build
 >cd build
 >cmake.exe -G "Visual Studio 16 2019" ..
 ```
 
 this should generate the VS solution
 
 3. Run Visual Studio as admin. I don't like it, but I can't find a way around this without modifing group policy, which is exclusive to Windows Pro.
 
 4. Open the solution and build the plugin(Ctrl B). You may want to change it from Debug to Relese mode as well.
 
 5. result will be outputed to `build\VST3\Release\Placebo_Plugin.vst3\Contents\x86_64-win`. Done
