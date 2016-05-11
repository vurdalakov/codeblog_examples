/* ----------------------------------------------------------------
# This source code is an example from my CodeBlog:
# http://codeblog.vurdalakov.net
#
# Copyright (c) 2016 Vurdalakov
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
    using System.Collections.Generic;
    using System.Windows;
    using System.Windows.Media;

    // http://codeblog.vurdalakov.net/2016/05/wpf-find-child-or-parent-of-control-or-window-with-given-type.html
    public static class VisualTreeFinder
    {
        // Finds the first child of a DependencyObject with a given type.
        // Example:
        //      var textBlock = VisualTreeFinder.FindChild<TextBlock>(Application.Current.MainWindow);

        public static T FindChild<T>(DependencyObject dependencyObject) where T : DependencyObject
        {
            if (dependencyObject != null)
            {
                for (int i = 0; i < VisualTreeHelper.GetChildrenCount(dependencyObject); i++)
                {
                    var child = VisualTreeHelper.GetChild(dependencyObject, i);

                    if ((child != null) && (child is T))
                    {
                        return child as T;
                    }

                    child = FindChild<T>(child);
                    if (child != null)
                    {
                        return child as T;
                    }
                }
            }

            return null;
        }

        // Finds all children of a DependencyObject with a given type.
        // Example:
        //      foreach (var button in VisualTreeFinder.FindChildren<Button>(this))
        //      {
        //          button.IsEnabled = false;
        //      }

        public static IEnumerable<T> FindChildren<T>(DependencyObject dependencyObject) where T : DependencyObject
        {
            if (dependencyObject != null)
            {
                for (int i = 0; i < VisualTreeHelper.GetChildrenCount(dependencyObject); i++)
                {
                    var child = VisualTreeHelper.GetChild(dependencyObject, i);

                    if ((child != null) && (child is T))
                    {
                        yield return child as T;
                    }

                    foreach (T childOfChild in FindChildren<T>(child))
                    {
                        yield return childOfChild;
                    }
                }
            }
        }

        // Finds the first parent of a DependencyObject with a given type.
        // Example:
        //      var frame = VisualTreeFinder.FindChild<Frame>(this);

        public static T FindParent<T>(DependencyObject dependencyObject) where T : DependencyObject
        {
            if ((null == dependencyObject) || (dependencyObject is T))
            {
                return dependencyObject as T;
            }

            var parent = VisualTreeHelper.GetParent(dependencyObject);
            return FindParent<T>(parent);
        }
    }
}
