/* ----------------------------------------------------------------
# This source code is an example from my CodeBlog:
# http://codeblog.vurdalakov.net
#
# Copyright (c) 2012 Vurdalakov
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

namespace LinqTest
{
    using System;
    using System.Collections.Generic;

    class Program
    {
        static void Main(String[] args)
        {
            List<Plugin> plugins = ParseXml.Example1(@"..\..\Xml\example1.xml");
            PrintPlugins(1, plugins);

            plugins = ParseXml.Example2(@"..\..\Xml\example2.xml");
            PrintPlugins(2, plugins);

            plugins = ParseXml.Example3(@"..\..\Xml\example3.xml");
            PrintPlugins(3, plugins);

            plugins = ParseXml.Example4(@"..\..\Xml\example4.xml", "UI");
            PrintPlugins(4, plugins);
        }

        static void PrintPlugins(Int32 exampleNumber, List<Plugin> plugins)
        {
            Console.WriteLine("=== Example {0}\n", exampleNumber);
            Console.WriteLine("{0,17}{1,12}{2,22}{3,22}", "Name", "Type", "EntryPoint", "File.Name");
            Console.WriteLine(new String('-', 73));
            
            foreach (Plugin plugin in plugins)
            {
                Console.WriteLine("{0,17}{1,12}{2,22}", plugin.Name, plugin.Type, null == plugin.Implementation ? "" : plugin.Implementation.EntryPoint);
                if (plugin.Files != null)
                {
                    foreach (PluginFile pluginFile in plugin.Files)
                    {
                        Console.WriteLine("{0,73}", pluginFile.Name);
                    }
                }
            }
            
            Console.WriteLine(new String('=', 73));
            Console.WriteLine();
        }
    }
}
