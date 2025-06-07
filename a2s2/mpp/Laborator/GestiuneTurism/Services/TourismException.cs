using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Services
{
    public class TourismException : Exception
    {
        public TourismException() : base() { }
        public TourismException(string message) : base(message) { }
        public TourismException(string? message, Exception? innerException) : base(message, innerException) { }
    }
}
