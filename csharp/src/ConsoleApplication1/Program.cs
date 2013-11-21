namespace Vurdalakov
{
    using System;
    using System.IO;

    class Program
    {
        static void Main(string[] args)
        {
//            StringCollection2IEnumerableString.StringCollection2List();

            String path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), @"Internet Explorer\iexplore.exe");
            Console.WriteLine("Long path:  '{0}'", path);

            path = PathExtensions.GetShortPathName(path);
            Console.WriteLine("Short path: '{0}'", path);
            
            path = PathExtensions.GetLongPathName(path);
            Console.WriteLine("Long path:  '{0}'", path);
        }
    }
}
