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
    using System;
    using System.Runtime.InteropServices;

    public static class Keyboard
    {
        public static Int32 GetKeyboardCount()
        {
            var keyboardCount = 0;

            var size = (Marshal.SizeOf(typeof(RAWINPUTDEVICELIST)));

            UInt32 devicesCount = 0;
            if (0 == GetRawInputDeviceList(IntPtr.Zero, ref devicesCount, (UInt32)size))
            {
                var pRawInputDeviceList = Marshal.AllocHGlobal((int)(size * devicesCount));
                GetRawInputDeviceList(pRawInputDeviceList, ref devicesCount, (UInt32)size);

                for (var i = 0; i < devicesCount; i++)
                {
                    var rawInputDeviceList = (RAWINPUTDEVICELIST)Marshal.PtrToStructure(new IntPtr((pRawInputDeviceList.ToInt64() + (size * i))), typeof(RAWINPUTDEVICELIST));

                    if (RIM_TYPEKEYBOARD == rawInputDeviceList.dwType)
                    {
                        keyboardCount++;
                    }
                }

                Marshal.FreeHGlobal(pRawInputDeviceList);
            }

            return keyboardCount;
        }

        #region Interop

        const UInt32 RIM_TYPEMOUSE = 0;
        const UInt32 RIM_TYPEKEYBOARD = 1;
        const UInt32 RIM_TYPEHID = 2;

        [StructLayout(LayoutKind.Sequential)]
        internal struct RAWINPUTDEVICELIST
        {
            public IntPtr hDevice;
            public UInt32 dwType;
        }

        [DllImport("User32.dll", SetLastError = true)]
        private static extern UInt32 GetRawInputDeviceList(IntPtr pRawInputDeviceList, ref UInt32 puiNumDevices, UInt32 cbSize);

        #endregion
    }
}
