/* ----------------------------------------------------------------
# This software is part of the FreeCodeCollection project
# http://code.google.com/p/freecodecollection/
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
    using System.Linq;
    using System.Xml.Linq;

    public class Plugin
    {
        public String Name { get; set; }
        public String Type { get; set; }
        public PluginImplementation Implementation { get; set; }
        public List<PluginFile> Files { get; set; }
    }

    public class PluginImplementation
    {
        public String EntryPoint { get; set; }
    }

    public class PluginFile
    {
        public String Name { get; set; }
    }

    static public class ParseXml
    {
        static public List<Plugin> Example1(String fileName)
        {
            XDocument document = XDocument.Load(fileName);
            List<Plugin> plugins = new List<Plugin>(from plugin in document.Descendants("Plugin")
                                                    select new Plugin
                                                    {
                                                        Name = (String)plugin.Attribute("Name")
                                                    });
            return plugins;
        }

        static public List<Plugin> Example2(String fileName)
        {
            XDocument document = XDocument.Load(fileName);
            XNamespace ns = document.Root.Name.Namespace;
            List<Plugin> plugins = new List<Plugin>(from plugin in document.Descendants(ns + "Plugin")
                                                    select new Plugin
                                                    {
                                                        Name = (String)plugin.Attribute("Name")
                                                    });
            return plugins;
        }

        static public List<Plugin> Example3(String fileName)
        {
            XDocument document = XDocument.Load(fileName);
            XNamespace ns = document.Root.Name.Namespace;
            List<Plugin> plugins = new List<Plugin>(from plugin in document.Descendants(ns + "Plugin")
                                                    select new Plugin
                                                    {
                                                        Name = (String)plugin.Attribute("Name"),
                                                        Type = (String)plugin.Attribute("Type"),
                                                        Implementation = new PluginImplementation()
                                                        {
                                                            EntryPoint = (String)plugin.Element(ns + "Runtime").Element(ns + "Implementation").Attribute("EntryPoint")
                                                        },
                                                        Files = new List<PluginFile>(from implementation in plugin.Descendants(ns + "File")
                                                                                     select new PluginFile
                                                                                     {
                                                                                         Name = (String)implementation.Attribute("Name")
                                                                                     })
                                                    });
            return plugins;
        }

        static public List<Plugin> Example4(String fileName, String type)
        {
            XDocument document = XDocument.Load(fileName);
            XNamespace ns = document.Root.Name.Namespace;
            List<Plugin> plugins = new List<Plugin>(from plugin in document.Descendants(ns + "Plugin")
                                                    where plugin.Attribute("Type").Value.Equals(type)
                                                    select new Plugin
                                                    {
                                                        Name = (String)plugin.Attribute("Name"),
                                                        Type = (String)plugin.Attribute("Type"),
                                                    });
            return plugins;
        }
    }
}
