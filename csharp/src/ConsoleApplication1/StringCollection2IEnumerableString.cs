namespace Vurdalakov
{
    using System;
    using System.Collections.Generic;
    using System.Collections.Specialized;
    using System.Linq;

    public class StringCollection2IEnumerableString
    {
        public static void StringCollection2List()
        {
            StringCollection stringCollection = new StringCollection();

            stringCollection.Add("String 1");
            stringCollection.Add("String 2");
            stringCollection.Add("String 3");

            Console.WriteLine("*** StringCollection:");
            foreach (String s in stringCollection)
            {
                Console.WriteLine(s);
            }

            List<String> stringList = stringCollection.Cast<String>().ToList();

            Console.WriteLine("*** List<String>:");
            foreach (String s in stringList)
            {
                Console.WriteLine(s);
            }
        }
    }
}
