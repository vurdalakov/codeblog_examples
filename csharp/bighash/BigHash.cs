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

using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace BigHash
{
    class BigHash
    {
        public void ShowExample()
        {
            const String hashAlgorithmName = "SHA1";
            String fileName = Environment.ExpandEnvironmentVariables(@"%windir%\explorer.exe");

            Console.WriteLine("{0}:", fileName);

            Byte[] hash1 = Method1_AllInOnce(hashAlgorithmName, fileName);
            Console.WriteLine("Method 1: {0}", BytesToString(hash1));

            Byte[] hash2 = Method2_PieceByPiece(hashAlgorithmName, fileName);
            Console.WriteLine("Method 2: {0}", BytesToString(hash2));
        }

        Byte[] Method1_AllInOnce(String hashAlgorithmName, String fileName)
        {
            HashAlgorithm hashAlgorithm = HashAlgorithm.Create(hashAlgorithmName);

            using (FileStream stream = File.Open(fileName, FileMode.Open, FileAccess.Read))
            {
                Byte[] bytes = new byte[stream.Length];
                stream.Read(bytes, 0, (int)stream.Length);

                return hashAlgorithm.ComputeHash(bytes);
            }
        }

        Byte[] Method2_PieceByPiece(String hashAlgorithmName, String fileName)
        {
            const int bufferSize = 65536;

            Byte[] bytes = new byte[bufferSize];

            HashAlgorithm hashAlgorithm = HashAlgorithm.Create(hashAlgorithmName);

            using (FileStream stream = File.Open(fileName, FileMode.Open, FileAccess.Read))
            {
                while (true)
                {
                    int bytesRead = stream.Read(bytes, 0, bufferSize);

                    if (0 == bytesRead)
                    {
                        break;
                    }

                    hashAlgorithm.TransformBlock(bytes, 0, bytesRead, bytes, 0); 
                }

                hashAlgorithm.TransformFinalBlock(bytes, 0, 0);

                return hashAlgorithm.Hash;
            }
        }

        String BytesToString(Byte[] bytes)
        {
            StringBuilder stringBuilder = new StringBuilder();

            for (int i = 0; i < bytes.Length; i++)
            {
                stringBuilder.AppendFormat("{0:X2}", bytes[i]);
            }

            return stringBuilder.ToString();
        }
    }
}
