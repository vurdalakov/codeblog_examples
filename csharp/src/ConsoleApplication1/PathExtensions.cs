namespace Vurdalakov
{
    using System;
    using System.IO;
    using System.Runtime.InteropServices;
    using System.Text;

    public static class PathExtensions
    {
        public static String GetShortPathName(String longPath)
        {
            StringBuilder shortPath = new StringBuilder(longPath.Length + 1);

            if (0 == PathExtensions.GetShortPathName(longPath, shortPath, shortPath.Capacity))
            {
                return longPath;
            }
            
            return shortPath.ToString();
        }

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern Int32 GetShortPathName(String path, StringBuilder shortPath, Int32 shortPathLength);

        public static String GetLongPathName(String shortPath)
        {
            StringBuilder longPath = new StringBuilder(1024);

            if (0 == PathExtensions.GetLongPathName(shortPath, longPath, longPath.Capacity))
            {
                return shortPath;
            }

            return longPath.ToString();
        }

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern Int32 GetLongPathName(String shortPath, StringBuilder longPath, Int32 longPathLength);
    }
}
