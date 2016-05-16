/* ----------------------------------------------------------------
# This source code is an example from my CodeBlog:
# http://codeblog.vurdalakov.net
#
# Copyright (c) 2013 Vurdalakov
# http://www.vurdalakov.net
# vurdalakov@gmail.com
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
---------------------------------------------------------------- */

namespace Vurdalakov
{
    using System;
    using System.IO;

    class Program
    {
        static void Main(string[] args)
        {
#if false
            StringCollection2IEnumerableString.StringCollection2List();
#endif

#if false
            String path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), @"Internet Explorer\iexplore.exe");
            Console.WriteLine("Long path:  '{0}'", path);

            path = PathExtensions.GetShortPathName(path);
            Console.WriteLine("Short path: '{0}'", path);
            
            path = PathExtensions.GetLongPathName(path);
            Console.WriteLine("Long path:  '{0}'", path);
#endif

#if true
            Console.WriteLine("{0} keyboard(s) are attached", Keyboard.GetKeyboardCount());
#endif
        }
    }
}
