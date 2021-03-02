using System;
namespace beautifulNumber_1
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            string input = Console.ReadLine();
            String[] data = input.Split();
            var leftBorder = Convert.ToUInt64(data[0]);
            var rightBorder = Convert.ToUInt64(data[1]);

            var maxSimple = Convert.ToUInt64(Math.Floor(Math.Sqrt(rightBorder)));
            var minSimple = Convert.ToUInt64(Math.Floor(Math.Sqrt(leftBorder)));
            //Console.WriteLine(maxSimple);
            for (UInt64 counter = minSimple; counter <= maxSimple; counter++)
            {
                if (isSimple(counter))
                {
                    Console.WriteLine(counter * counter);
                }
            }

            Console.ReadKey();
        }

        private static bool isSimple(UInt64 number)
        {
            for (UInt64 divider = 2; divider <= Convert.ToUInt64(Math.Floor(Math.Sqrt(number))); divider++)
            {
                if (number % divider == 0)
                    return false;
            }

            return true;
        }
    }
}